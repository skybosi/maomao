#include "udpServer.h"
#include "winsock.h"


udpServer::udpServer()
{

}

udpServer::~udpServer()
{

}

void udpServer::OnSent(ElpeError status)
{
	if (status != ElpeError::elpeSuccess) {
		fprintf(stderr, "Send error %s\n", Handle::errDesc(status));
		return;
	}
}

void udpServer::OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags)
{	
	sockaddr_in* psin = (sockaddr_in*)addr;

	printf("Recv from ip:%s,port:%d\n",inet_ntoa(psin->sin_addr),ntohs(psin->sin_port));

	printf("recv data:%s,len = %d\n", buf,nread);

	send(buf,nread,addr);

//	send4(buf,nread,"192.168.100.90",1800);
}