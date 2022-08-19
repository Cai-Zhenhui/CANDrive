#include "Message.h"

Message::Message()
{
	char* p = (char*)this;
	for (int i = 0; i < sizeof(*this); ++i) {
		p[i] = 0;
	}
}

Message::Message(unsigned int _id, unsigned int _dlc, bool _isExtendMessage)
{
	id = _id;
	dlc = _dlc;
	isExtendMessage = _isExtendMessage;
	timestamp = 0;
	data[0] = 0;
}
