#include <stdlib.h>

#include "mmloop.h"

using namespace mm::uvbase;

class MyAsync : public Async
{
public:
	MyAsync() {}
	~MyAsync() {}
	virtual void OnAsync()
	{
		printf("Async test\n");
		close();
	}
};

int asyncTest()
{
	Loop loop(true);

	MyAsync async;
	async.init(loop);
	async.send();
	loop.run(Loop::Default);
	return 0;
}