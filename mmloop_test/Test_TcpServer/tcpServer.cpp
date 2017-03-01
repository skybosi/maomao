#include "tcpServer.h"



void tcpServer::doAccept(Handle::ElpeError status)
{
	if (status != ElpeError::elpeSuccess) {
		fprintf(stderr, "New connection error %s\n", Handle::errDesc(status));
		return;
	}

	tcpServer* client = new tcpServer();
	client->init(get_loop());

	if (accept((Stream*)client) == 0) {

		char ip[17] = { 0 };
		int  port = 0;
		client->getpeerIpPort(ip,port);
		printf("client accept client ip = %s,port = %d\n",ip,port);

		client->read_start();
	}
	else {
		client->close();
		delete client;
	}

}

void tcpServer::OnRead(ssize_t nread, const char *buf)
{
	printf("recv data:%s,len = %d\n", buf,nread);

	write(buf,nread);
}