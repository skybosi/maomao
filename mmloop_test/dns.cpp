#include "mmloop_net.h"
#include "mmloop.h"
using namespace mm::Loop;

class MyDNS : public DNS
{
public:
	MyDNS() {}
	~MyDNS() {}
	virtual void onResolved(Handle::ElpeError status,const char* ip)
	{
		if (status != 0) 
		{
			fprintf(stderr, "getAddrInfo error %s\n", Handle::errDesc(status));
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

	getchar();
	return 0;
}