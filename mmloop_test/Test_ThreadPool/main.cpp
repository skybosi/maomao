#include "eloop_threadpool.h"
#include "eloop.h"
#include <SystemUtils.h>
#include <stdlib.h>
#include <time.h>

class MyThreadPool:public ZQ::eloop::ThreadPool
{
public:
	MyThreadPool(ZQ::eloop::Loop& loop):ZQ::eloop::ThreadPool(loop){}
	~MyThreadPool(){}
	virtual void doWork()
	{
		int size = *((int*)this->_data);
		int downloaded = 0;
		srand((unsigned)time(NULL));
		while (downloaded < size) {
			printf("download data %d total:%d\n",downloaded,size);
			SYS::sleep(1000);
			downloaded += rand()%1000; // can only download max 1000bytes/sec,
			}
	}
	virtual void OnAfterWork(int status)
	{
		printf("Download complete\n");
	}
};

int main()
{
	ZQ::eloop::Loop loop(true);

	MyThreadPool threadpool(loop);
	int data = 5000;
	threadpool.work(&data);

	printf("Is downloading!\n");
	loop.run(ZQ::eloop::Loop::Default);
	printf("loop end!\n");
	while(1);
	return 0;
}