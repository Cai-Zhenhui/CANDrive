#include "CANDriveZLG.h"
#include <memory.h>

#ifdef _M_IX86
#pragma comment(lib,"./drive/zlg/LIB/zlgcan.lib")
#endif // _M_IX86

#ifdef _M_X64
#pragma comment(lib,"./drive/zlg/LIB/x64/zlgcan.lib")
#endif // _M_X64

CANDriveZLG::CANDriveZLG()
{
}

CANDriveZLG::~CANDriveZLG()
{
}

bool CANDriveZLG::openDevice()
{
	hDevice = ZCAN_OpenDevice(ZCAN_USBCAN_2E_U, 0, 0);
	return hDevice != INVALID_DEVICE_HANDLE;
}

bool CANDriveZLG::openChannel(int channel, int bitRate)
{
	char buffer[20]="0/baud_rate";
	buffer[0] = '0' + channel;
	switch (bitRate)
	{
	case CANDRIVE_BITRATE_250K: {
		if (ZCAN_SetValue(hDevice, buffer, "250000") != STATUS_OK) {
			return false;
		}
		break;
	}
	case CANDRIVE_BITRATE_500K: {
		if (ZCAN_SetValue(hDevice, buffer, "500000") != STATUS_OK) {
			return false;
		}
		break;
	}
	case CANDRIVE_BITRATE_1M: {
		if (ZCAN_SetValue(hDevice, buffer, "1000000") != STATUS_OK) {
			return false;
		}
		break;
	}
	default:
		return false;
	}
	
	ZCAN_CHANNEL_INIT_CONFIG cfg{ 0 };
	cfg.can_type = TYPE_CAN;
	cfg.can.filter = 0;
	cfg.can.mode = 0;
	cfg.can.acc_code = 0;
	cfg.can.acc_mask = 0xffffffff;
	hChannel[channel] = ZCAN_InitCAN(hDevice, 0, &cfg);
	if (hChannel[channel] == INVALID_CHANNEL_HANDLE) {
		return false;
	}
	if (ZCAN_StartCAN(hChannel[channel]) != STATUS_OK) {
		return false;
	}
	return true;
}

//ZLG 发送不支持异步，使用同步代替
void CANDriveZLG::transmit(int channel, Message& message)
{
	transmitSync(channel, message);
}


void CANDriveZLG::transmitSync(int channel, Message& message)
{
	ZCAN_Transmit_Data msg;
	memset(&msg, 0, sizeof(msg));

	msg.frame.can_dlc = message.dlc;
	msg.frame.can_id = message.id | message.isExtendMessage << 31;
	msg.transmit_type = 0;
	memcpy(msg.frame.data, message.data, 8);

	ZCAN_Transmit(hChannel[channel], &msg, 1);
}

int CANDriveZLG::receive(int channel, Message& message)
{
	ZCAN_Receive_Data buffer;
	unsigned int ret = ZCAN_Receive(hChannel[channel], &buffer, 1, 0);
	if (ret == 0) {
		return CANDRIVE_STATE_NOMSG;
	}
	message.id = buffer.frame.can_id & 0x1FFFFFFF;
	message.dlc = buffer.frame.can_dlc;
	message.isExtendMessage = buffer.frame.can_id & 0x80000000;
	message.timestamp = buffer.timestamp;
	memcpy(message.data, buffer.frame.data, message.dlc);
	return CANDRIVE_STATE_OK;
}

int CANDriveZLG::receiveSync(int channel, Message& message)
{
	ZCAN_Receive_Data buffer;
	unsigned int ret = ZCAN_Receive(hChannel[channel], &buffer, 1, -1);
	if (ret == 0) {
		//这里也没有意义receive会无限期等待。
		return CANDRIVE_STATE_NOMSG;
	}
	message.id = buffer.frame.can_id & 0x1FFFFFFF;
	message.dlc = buffer.frame.can_dlc;
	message.isExtendMessage = buffer.frame.can_id & 0x80000000;
	message.timestamp = buffer.timestamp;
	memcpy(message.data, buffer.frame.data, message.dlc);
	return CANDRIVE_STATE_OK;
}

void CANDriveZLG::closeChannel(int channel)
{
	ZCAN_ResetCAN(hChannel[channel]);
}

void CANDriveZLG::closeDevice()
{
	ZCAN_CloseDevice(hDevice);
}
