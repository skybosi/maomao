#include "mmloop_net.h"
#include "mmloop.h"
using namespace mm::uvbase;

class MyDNS : public DNS
{
public:
	MyDNS() {}
	~MyDNS() {}
	virtual void onResolved(Handle::mmerrno status,const char* ip)
	{
		if (status != 0) 
		{
			fprintf(stderr, "getAddrInfo error %s\n", Handle::errCode(status));
			return;
		}
		printf("ip:%s\n",ip);
	}
};


int dnsTest()
{
	Loop loop(true);

	struct addrinfo hints;
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = 0;

	MyDNS dns;
	dns.getAddrInfo(loop,"reqres.in", "80",&hints);

	loop.run(Loop::Default);
	return 0;
}
