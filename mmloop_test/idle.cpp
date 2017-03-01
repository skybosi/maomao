#include "mmloop.h"

using namespace mm::Loop;

class MyIdle : public Idle
{
public:
	MyIdle() {}
	~MyIdle() {}
	virtual void OnIdle()
	{
		printf("Idle test\n");
		Sleep(1000);
	}
};

int idleTest()
{
	Loop loop(true);

	MyIdle idle;
	idle.init(loop);
	idle.start();

	loop.run(Loop::Default);

	return 0;
}