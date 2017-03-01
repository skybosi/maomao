#include "tcpClient.h"



int main()
{
	Loop loop(false);

	tcpClient client;
	client.init(loop);
	//client.bind4("192.168.81.28",9979);
	client.connect4("192.168.81.71",9978);
	//client.connect4("10.15.10.50",9978);




	loop.run(Loop::Default);
	return 0;
}