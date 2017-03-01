#ifndef __UDP_CLIENT_H__
#define __UDP_CLIENT_H__

#include "mmloop_net.h"
using namespace mm::Loop;


class udpClient:public UDP
{
public:
	udpClient();
	~udpClient();

	virtual void OnSent(ElpeError status);
	virtual void OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags);
};

#endif