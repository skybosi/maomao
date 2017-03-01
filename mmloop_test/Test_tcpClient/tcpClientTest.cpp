#include "tcpClient.h"
int tcpClientTest()
{
	Loop loop(false);

	tcpClient client;
	client.init(loop);
	client.connect4("127.0.0.1",9130);
	loop.run(Loop::Default);
	return 0;
}