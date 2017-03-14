#include <stdio.h>
#include "transmitter.h"

namespace mm {
	namespace Transmitter {
		transmitter::transmitter(Type type) :userType(type)
		{
		}

		transmitter::~transmitter()
		{
		}

		void transmitter::OnConnected(mmerrno status) {
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "on_connect error %s\n", Handle::errCode(status));
				return;
			}
			read_start();

			char buf[1024];
			memset(buf, 0, 1024);
			scanf("%s", buf);

			write(buf, strlen(buf) + 1);
		}

		void transmitter::OnRead(ssize_t nread, const char *buf) 
		{
			if (nread < 0) {
				fprintf(stderr, "Read error %s\n", Handle::errType(nread));
				close();
				return;
			}
			printf("recv data:%s,len = %d\n", buf, nread);

			char sendbuf[1024];
			memset(sendbuf, 0, 1024);
			scanf("%s", sendbuf);

			write(sendbuf, strlen(sendbuf) + 1);
		}

		void transmitter::OnWrote(mmerrno status) {

		}

		void transmitter::doAccept(mmerrno status) {
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "New connection error %s\n", Handle::errCode(status));
				return;
			}

			transmitter* client = new transmitter();
			client->init(loop());

			if (accept((Stream*)client) == 0) {

				char ip[17] = { 0 };
				int  port = 0;
				client->getpeerIpPort(ip, port);
				printf("client accept client ip = %s,port = %d\n", ip, port);
				client->read_start();
			}
			else {
				client->close();
				delete client;
			}
		}
	}
}