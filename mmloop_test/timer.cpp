#include <stdio.h>
#include "mmloop_utils.h"

using namespace mm::uvbase;

class MyTimer : public Timer
{
public:
	MyTimer() {}
	~MyTimer() {}
	virtual void OnTimer()
	{
		printf("Timer test\n");
	}
};

int timerTest()
{
	Loop loop(true);

	MyTimer timer;
	timer.init(loop);
	timer.start(1000,1000);

	loop.run(Loop::Default);
	return 0;
}
