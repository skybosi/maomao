#ifndef __UDP_CLIENT_H__
#define __UDP_CLIENT_H__

#include "mmloop_net.h"
using namespace mm::uvbase;


class udpClient:public UDP
{
public:
	udpClient();
	~udpClient();

	virtual void OnSent(mmerrno status);
	virtual void OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags);
};

#endif