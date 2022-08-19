#pragma once
class Message
{
public:
	unsigned char data[64];
	unsigned int dlc;
	unsigned int id;
	/// <summary>
	/// 报文时间戳(us)，自从设备启动后。
	/// </summary>
	unsigned long timestamp;
	bool isExtendMessage;

	Message();
	Message(unsigned int _id, unsigned int _dlc, bool _isExtendMessage);
};

