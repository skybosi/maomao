#include "udpClient.h"

int udpClientTest()
{
	Loop loop(true);

	udpClient client;
	client.init(loop);
	client.bind("127.0.0.1",9979,UDP::Reuseaddr);
	client.recv_start();

	char buf[1024];
	memset(buf,0,1024);
	scanf("%s",buf);

	client.send(buf,strlen(buf),"127.0.0.1",1801);


	loop.run(Loop::Default);
	return 0;
}