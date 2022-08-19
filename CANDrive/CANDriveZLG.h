#pragma once
#include "drive/zlg/INC/zlgcan.h"
#include "CANDrive.h"

class CANDriveZLG :public CANDrive
{
public:
	CANDriveZLG();
	~CANDriveZLG();

	bool openDevice();

	bool openChannel(int channel, int bitRate);

	void transmit(int channel, Message& message);

	void transmitSync(int channel, Message& message);

	int receive(int channel, Message& message);

	int receiveSync(int channel, Message& message);

	void closeChannel(int channel);

	void closeDevice();
private:
	CHANNEL_HANDLE hChannel[2];
	DEVICE_HANDLE hDevice;
};

