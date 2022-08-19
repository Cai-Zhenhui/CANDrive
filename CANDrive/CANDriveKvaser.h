#pragma once
#include "CANDrive.h"
class CANDriveKvaser : public CANDrive
{
public:
	CANDriveKvaser();
	~CANDriveKvaser();

	bool openDevice();

	bool openChannel(int channel, int bitRate);

	void transmit(int channel, Message& message);

	void transmitSync(int channel, Message& message);

	int receive(int channel, Message& message);

	int receiveSync(int channel, Message& message);

	void closeChannel(int channel);

	void closeDevice();
private:
	int hChannel[5];
};

