#include "mmloop_lock.h"
#include "NativeThread.h"

using namespace mm::Loop;
mm::Loop::Mutex m;
int num = 0;
class ReadThread:public ZQ::common::NativeThread
{
public:

	ReadThread(){}

	virtual int  run()
	{
		int j = 0;
		while(1)
		{
			m.lock();
			if (num != 0)
			{
				j = num;
				num = 0;
				printf("j = %d\n",j);
			}	
			m.unlock();
		}

		return 0;
	}
};

class WriteThread:public ZQ::common::NativeThread
{
public:

	WriteThread(){}

	virtual int  run()
	{
		int i = 1;
		while(1)
		{
			m.lock();
			if (num == 0)
			{
				num = i;
				i++;
			}
			m.unlock();
		}

		return 0;
	}
};



void main()
{
	WriteThread write;
	ReadThread read;

	write.start();
	read.start();

	while(1);
}