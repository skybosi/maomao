#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include "mmloop_net.h"
using namespace mm::uvbase;


class udpServer:public UDP
{
public:
	udpServer();
	~udpServer();

	virtual void OnSent(mmerrno status);
	virtual void OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags);

};

#endif