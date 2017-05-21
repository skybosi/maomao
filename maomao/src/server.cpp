#include <stdio.h>
#include "transmitter\transmitter.h"
using namespace mm::Transmitter;

int server(int argc, char* argv[])
{
	tTM server;
	//uTM server;
	server.Relate("127.0.0.1", 9130);
	return 0;
}