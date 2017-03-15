#include <stdio.h>
#include <string.h>
#include "mmloop_files.h"

using namespace mm::uvbase;

class pipeServer:public Pipe
{
public:
	pipeServer(){}
	~pipeServer(){}

	virtual void doAccept(mmerrno status)
	{
		if (status != mmerrno::mmSuccess) {
			fprintf(stderr, "New connection error %s\n", errType(status));
			return;
		}

		pipeServer *client = new pipeServer();
		client->init(loop());

		if (accept((Stream *)client) == 0) {

			client->read_start();
		}
		else {
			client->close();
		}
	}

	virtual void OnRead(size_t nread, const char *buf)
	{
		printf("recv data:%s,len = %d\n", buf,nread);
		write(buf,nread);
	}

};

# define TEST_PIPENAME "\\\\?\\pipe\\uv-test"

int pipeServerTest()
{
	Loop loop(true);
	pipeServer server;

	server.init(loop);

	int r = -1;
	r = server.bind(TEST_PIPENAME);
	if (r != 0)
	{
		fprintf(stderr, "Bind error %s\n", pipeServer::errType(r));
		return 1;
	}

	r = server.wait();
	if (r != 0)
	{
		fprintf(stderr, "Listen error %s\n", pipeServer::errType(r));
		return 1;
	}

	loop.run(Loop::Default);
	return 0;
}
