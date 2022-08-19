#include <thread>
#include <iostream>
#include <Windows.h>

#include "CANDriveKvaser.h"
#include "CANDriveZLG.h"
using namespace std;

// Debug x86 ����ͨ��
// Debug x64 ����ͨ��
// Release x86 ����ͨ��
// Release x64 ����ͨ��
void testKvaser() {
	bool isExit = false;
	char ch;
	CANDriveKvaser _CAN;
	CANDrive* CAN = &_CAN;
	auto func = [&isExit, CAN]() {
		Message msg;
		while (!isExit) {
			auto ret = CAN->receive(0, msg);
			if (ret == CANDRIVE_STATE_OK) {
				printf("%X %d ", msg.id, msg.dlc);
				printf("%c ", msg.isExtendMessage ? 'E' : 'S');
				for (int i = 0; i < msg.dlc; ++i) {
					printf("%02X ", msg.data[i]);
				}
				printf("%d\n", msg.timestamp);
			}
			else {
				Sleep(20);
			}
		}
	};


	Message msg;
	cout << "��ʼ����Kvaser��\n";
	auto ret = CAN->openDevice();
	cout << "���豸��" << ret << endl;
	ret = CAN->openChannel(0, CANDRIVE_BITRATE_500K);
	cout << "��ͨ����" << ret << endl;

	thread th(func);
	while (!isExit) {
		cin >> ch;
		if ((ch | 32) == 'q') {
			isExit = true;
			th.join();
			break;
		}
		else if ((ch | 32) == 't') {
			cin >> msg.id >> msg.dlc >> msg.data[0];
			msg.isExtendMessage = (msg.data[0] & (-33)) == 'E';
			for (int i = 0; i < msg.dlc; ++i) {
				cin >> msg.data[i];
			}
			CAN->transmitSync(0, msg);
		}
	}
	CAN->closeChannel(0);
	CAN->closeDevice();
}

// Debug x86 ����ͨ��
// Debug x64 ����ͨ��
// Release x86 ����ͨ��
// Release x64 ����ͨ��
void testZLG() {
	bool isExit = false;
	char ch;
	CANDriveZLG _CAN;
	CANDrive* CAN = &_CAN;
	auto func = [&isExit, CAN]() {
		Message msg;
		while (!isExit) {
			auto ret = CAN->receive(0, msg);
			if (ret == CANDRIVE_STATE_OK) {
				printf("%X %d ", msg.id, msg.dlc);
				printf("%c ", msg.isExtendMessage ? 'E' : 'S');
				for (int i = 0; i < msg.dlc; ++i) {
					printf("%02X ", msg.data[i]);
				}
				printf("%d\n", msg.timestamp);
			}
			else {
				Sleep(20);
			}
		}
	};


	Message msg;
	cout << "��ʼ����ZLG��\n";
	auto ret = CAN->openDevice();
	cout << "���豸��" << ret << endl;
	ret = CAN->openChannel(0, CANDRIVE_BITRATE_500K);
	cout << "��ͨ����" << ret << endl;

	thread th(func);
	while (!isExit) {
		cin >> ch;
		if ((ch | 32) == 'q') {
			isExit = true;
			th.join();
			break;
		}
		else if ((ch | 32) == 't') {
			cin >> msg.id >> msg.dlc >> msg.data[0];
			msg.isExtendMessage = (msg.data[0] & (-33)) == 'E';
			for (int i = 0; i < msg.dlc; ++i) {
				cin >> msg.data[i];
			}
			CAN->transmitSync(0, msg);
		}
	}
	CAN->closeChannel(0);
	CAN->closeDevice();
}

int main() {
	//testZLG();
	testKvaser();
	return 0;
}