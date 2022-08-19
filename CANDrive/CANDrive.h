#pragma once
#include "Message.h"
#define CANDRIVE_BITRATE_250K 1
#define CANDRIVE_BITRATE_500K 2
#define CANDRIVE_BITRATE_1M 3

#define CANDRIVE_STATE_OK 1
#define CANDRIVE_STATE_OTHERERROR 0
#define CANDRIVE_STATE_NOMSG -2

class CANDrive
{
public:
	CANDrive();
	~CANDrive();
	/// <summary>
	/// 打开一个设备。
	/// </summary>
	/// <returns>成功返回true，失败返回false</returns>
	virtual bool openDevice() = 0;

	/// <summary>
	/// 打开已有设备的指定通道。
	/// </summary>
	/// <param name="channel">通道号</param>
	/// <param name="bitRate">比特率，参考CANDRIVE_BITRATE_*** 宏定义 </param>
	/// <returns>成功返回true，失败返回false</returns>
	virtual bool openChannel(int channel, int bitRate) = 0;

	/// <summary>
	/// 异步发送一帧报文。
	/// </summary>
	/// <param name="channel">通道号</param>
	/// <param name="message">报文</param>
	virtual void transmit(int channel, Message& message) = 0;

	/// <summary>
	/// 同步发送一帧报文。
	/// </summary>
	/// <param name="channel">通道号</param>
	/// <param name="message">报文</param>
	virtual void transmitSync(int channel, Message& message) = 0;

	/// <summary>
	/// 异步接收一帧报文。
	/// </summary>
	/// <param name="channel">通道号</param>
	/// <param name="message">报文</param>
	virtual int receive(int channel, Message& message) = 0;

	/// <summary>
	/// 同步接收一帧报文。
	/// </summary>
	/// <param name="channel">通道号</param>
	/// <param name="message">报文</param>
	virtual int receiveSync(int channel, Message& message) = 0;

	/// <summary>
	/// 关闭指定通道。
	/// </summary>
	/// <param name="channel">通道号</param>
	virtual void closeChannel(int channel) = 0;

	/// <summary>
	/// 关闭该设备。
	/// </summary>
	virtual void closeDevice() = 0;
};

