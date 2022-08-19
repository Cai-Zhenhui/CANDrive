#include "CANDriveKvaser.h"
#include "drive/kvaser/INC/canlib.h"
#ifdef _M_IX86
#pragma comment(lib,"drive/kvaser/LIB/canlib32.lib")
#endif // _M_IX86

#ifdef _M_X64
#pragma comment(lib,"drive/kvaser/LIB/canlib64.lib")
#endif // _M_X64

CANDriveKvaser::CANDriveKvaser()
{
	
}

CANDriveKvaser::~CANDriveKvaser()
{
	
}

bool CANDriveKvaser::openDevice()
{
	canInitializeLibrary();
	return true;
}

bool CANDriveKvaser::openChannel(int channel, int bitRate)
{
	hChannel[channel] = canOpenChannel(channel, canOPEN_EXCLUSIVE);
	if (hChannel[channel] < 0) {
		return false;
	}
	switch (bitRate){
	case CANDRIVE_BITRATE_250K: {
		canSetBusParams(hChannel[channel], canBITRATE_250K, 0, 0, 0, 0, 0);
		break;
	}
	case CANDRIVE_BITRATE_500K: {
		canSetBusParams(hChannel[channel], canBITRATE_500K, 0, 0, 0, 0, 0);
		break;
	}
	case CANDRIVE_BITRATE_1M: {
		canSetBusParams(hChannel[channel], canBITRATE_1M, 0, 0, 0, 0, 0);
		break;
	}
	default: {
		return false;
	}
	}
	DWORD buffer = 1;
	canIoCtl(hChannel[channel], canIOCTL_SET_TIMER_SCALE, &buffer, sizeof(buffer));
	canSetBusOutputControl(hChannel[channel], canDRIVER_NORMAL);
	canBusOn(hChannel[channel]);
	return true;
}

void CANDriveKvaser::transmit(int channel, Message& message)
{
	canWrite(hChannel[channel], message.id, message.data, 
		message.dlc, message.isExtendMessage ? canMSG_EXT : 0);
}

void CANDriveKvaser::transmitSync(int channel, Message& message)
{
	canWriteWait(hChannel[channel], message.id, message.data,
		message.dlc, message.isExtendMessage ? canMSG_EXT : 0, -1);
}

int CANDriveKvaser::receive(int channel, Message& message)
{
	unsigned int flag = 0;
	auto ret = canRead(hChannel[channel], (long*)&message.id, message.data, &message.dlc, &flag, &message.timestamp);
	message.isExtendMessage = flag == canMSG_EXT;
	switch (ret) {
	case canStatus::canERR_NOMSG: {
		return CANDRIVE_STATE_NOMSG;
	}
	case canStatus::canOK: {
		return CANDRIVE_STATE_OK;
	}
	}
	return CANDRIVE_STATE_OTHERERROR;
}

int CANDriveKvaser::receiveSync(int channel, Message& message)
{
	unsigned int flag = 0;
	auto ret=canReadWait(hChannel[channel], (long*)&message.id, message.data, &message.dlc, &flag, &message.timestamp, -1);
	message.isExtendMessage = flag == canMSG_EXT;
	switch (ret) {
	case canStatus::canERR_NOMSG: {
		return CANDRIVE_STATE_NOMSG;
	}
	case canStatus::canERR_TIMEOUT: {
		//目前认为超时和没有消息是等价的。
		return CANDRIVE_STATE_NOMSG;
	}
	case canStatus::canOK: {
		return CANDRIVE_STATE_OK;
	}
	}
	return CANDRIVE_STATE_OTHERERROR;
}

void CANDriveKvaser::closeChannel(int channel)
{
	canBusOff(hChannel[channel]);
	canClose(hChannel[channel]);
}

void CANDriveKvaser::closeDevice()
{
	canUnloadLibrary();
}
