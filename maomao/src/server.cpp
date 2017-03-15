#include <stdio.h>
#include "transmitter\transmitter.h"
using namespace mm::Transmitter;

int server(int argc, char* argv[])
{
	Loop loop(false);
	transmitter server(Tran::Type::SERVER);
	server.init(loop);
	server.bind("127.0.0.1", 9130);
	server.wait();
	loop.run(Loop::Default);
	return 0;
}