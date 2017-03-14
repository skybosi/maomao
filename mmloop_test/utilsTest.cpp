
#include "mmloop_utils.h"
#include "mmloop.h"
using namespace mm::uvbase;

int bufferTest()
{
	buffer buf;
	buffer buf2(100);
	buffer* buf3 = new buffer(200);
	delete buf3;
	return 0;
}

int rusageTest()
{
	rusage r;
	rusage* r2 = new rusage();
	delete r2;
	return 0;
}
