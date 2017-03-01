#include "udpClient.h"



udpClient::udpClient()
{

}

udpClient::~udpClient()
{

}

void udpClient::OnSent(mmerrno status)
{
	if (status != mmerrno::mmSuccess) {
		fprintf(stderr, "Send error %s\n",Handle::errCode(status));
		return;
	}
}

void udpClient::OnReceived(ssize_t nread,const char *buf, const struct sockaddr *addr, unsigned flags)
{
	sockaddr_in* psin = (sockaddr_in*)addr;

	printf("Recv from ip:%s,port:%d\n",inet_ntoa(psin->sin_addr),ntohs(psin->sin_port));

	printf("recv data:%s len = %d\n", buf,nread);

	char sendbuf[1024];
	memset(sendbuf,0,1024);
	scanf("%s",sendbuf);

	send(sendbuf,strlen(sendbuf),addr);
}