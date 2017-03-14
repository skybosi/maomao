#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include "mmloop_net.h"
//#include "Pointer.h"
using namespace mm::uvbase;


class tcpClient:public TCP
{
public:	
	//typedef ZQ::common::Pointer<tcpClient> Ptr;
public:
	tcpClient(){}
	~tcpClient(){}

	virtual void OnConnected(mmerrno status);
	virtual void OnRead(ssize_t nread, const char *buf);

};

#endif