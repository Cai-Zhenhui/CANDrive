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
	/// ��һ���豸��
	/// </summary>
	/// <returns>�ɹ�����true��ʧ�ܷ���false</returns>
	virtual bool openDevice() = 0;

	/// <summary>
	/// �������豸��ָ��ͨ����
	/// </summary>
	/// <param name="channel">ͨ����</param>
	/// <param name="bitRate">�����ʣ��ο�CANDRIVE_BITRATE_*** �궨�� </param>
	/// <returns>�ɹ�����true��ʧ�ܷ���false</returns>
	virtual bool openChannel(int channel, int bitRate) = 0;

	/// <summary>
	/// �첽����һ֡���ġ�
	/// </summary>
	/// <param name="channel">ͨ����</param>
	/// <param name="message">����</param>
	virtual void transmit(int channel, Message& message) = 0;

	/// <summary>
	/// ͬ������һ֡���ġ�
	/// </summary>
	/// <param name="channel">ͨ����</param>
	/// <param name="message">����</param>
	virtual void transmitSync(int channel, Message& message) = 0;

	/// <summary>
	/// �첽����һ֡���ġ�
	/// </summary>
	/// <param name="channel">ͨ����</param>
	/// <param name="message">����</param>
	virtual int receive(int channel, Message& message) = 0;

	/// <summary>
	/// ͬ������һ֡���ġ�
	/// </summary>
	/// <param name="channel">ͨ����</param>
	/// <param name="message">����</param>
	virtual int receiveSync(int channel, Message& message) = 0;

	/// <summary>
	/// �ر�ָ��ͨ����
	/// </summary>
	/// <param name="channel">ͨ����</param>
	virtual void closeChannel(int channel) = 0;

	/// <summary>
	/// �رո��豸��
	/// </summary>
	virtual void closeDevice() = 0;
};

