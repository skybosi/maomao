#include <stdio.h>
#include <assert.h>
#include "transmitter.h"

namespace mm {
	namespace Transmitter {
		transmitter::transmitter(Type type) :userType(type)
		{
		}

		transmitter::~transmitter()
		{
		}

		char * transmitter::user()
		{
			switch (this->userType)
			{
			case SERVER:
				return "server";
				break;
			case CLIENT:
				return "client";
				break;
			case BOTH_SER:
				return "both_ser";
				break;
			case BOTH_CLI:
				return "both_cli";
				break;
			default:
				return "Unknowed";
				break;
			}
			return nullptr;
		}

		void transmitter::writer(void* buf, size_t count)
		{
			write((char*)buf,count);
		}

		void transmitter::reader(void* buf, size_t count)
		{
			printf("%s recv data:%s,len = %d\n", user(), (char*)buf, count);
		}

		//client need implement
		void transmitter::OnConnected(mmerrno status) {
			assert(this->userType & 1);
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "on_connect error %s\n", Handle::errCode(status));
				return;
			}
			read_start();
			writer("hello!",6);
		}

		//server need implement
		void transmitter::doAccept(mmerrno status) {
			assert(!(this->userType & 1));
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

		//client or server need implement
		void transmitter::OnRead(ssize_t nread, const char *buf)
		{
			if (nread < 0) {
				fprintf(stderr, "%s Read error %s\n", user(),Handle::errType(nread));
				close();
				return;
			}
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				printf("current is %s onread callback!\n",user());
				reader((void*)buf, nread);
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				printf("current is %s onread callback!\n",user());
				reader((void*)buf, nread);
			}
		}

		//client or client need implement
		void transmitter::OnWrote(mmerrno status) {
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				printf("current is %s onwrite callback!\n", user());
				char sendbuf[1024];
				memset(sendbuf, 0, 1024);
				scanf("%s", sendbuf);
				writer(sendbuf, strlen(sendbuf) + 1);
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				printf("current is %s onwrite callback!\n", user());
			}
		}
	}
}