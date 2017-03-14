#include "transmitter\transmitter.h"
using namespace mm::Transmitter;

int client(int argc,char* argv[]) 
{
	Loop loop(false);
	transmitter client(Tran::Type::CLIENT);
	client.init(loop);
	client.connect4("127.0.0.1", 9130);
	loop.run(Loop::Default);
	return 0;
}