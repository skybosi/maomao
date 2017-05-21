#include "transmitter\transmitter.h"
using namespace mm::Transmitter;

int client(int argc,char* argv[]) 
{
	tTM client;
	//uTM client;
	client.Relate("127.0.0.1", 9130, ITM::CLIENT);
	//client.Sendto();
	return 0;
}