#include "udpClient.h"



int main()
{
	Loop loop(true);

	udpClient client;
	client.init(loop);
	client.bind4("127.0.0.1",9979,UDP::Reuseaddr);
	client.recv_start();

	char buf[1024];
	memset(buf,0,1024);
	scanf("%s",buf);

	client.send4(buf,strlen(buf),"127.0.0.1",1801);


	loop.run(Loop::Default);
	return 0;
}