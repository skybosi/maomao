#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include "mmloop_net.h"
using namespace mm::Loop;


class tcpServer:public TCP
{
public:
	tcpServer(){}
	~tcpServer(){}

	virtual void doAccept(ElpeError status);

	virtual void OnRead(ssize_t nread, const char *buf);

};

#endif