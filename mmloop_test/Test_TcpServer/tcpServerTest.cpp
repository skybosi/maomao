
#include "tcpServer.h"


int tcpServerTest()
{
	Loop loop(false);
	tcpServer server;


	server.init(loop);
	server.bind4("127.0.0.1", 9130);
	server.listen();	

	loop.run(Loop::Default);
	getchar();
	return 0;
}