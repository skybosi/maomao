#include <stdio.h>
#include <assert.h>
#include "transmitter.h"

namespace mm {
	namespace Transmitter {
		tTM::tTM()
		{
		}

		tTM::~tTM()
		{
		}

		void* tTM::Packer(void * data, int* size)
		{
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				printf("Packer current is %s\n", user());
				return data;
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				printf("Packer current is %s\n", user());
				return data;
			}
		}

		void* tTM::Unpack(void * data, int* size)
		{
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				printf("Unpack current is %s\n", user());
				return data;
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				printf("Unpack current is %s\n", user());
				return data;
			}
		}

		int  tTM::Relate(const char* addr, const int port,Type type)
		{
			Loop loop(false);
			this->userType = type;
			this->init(loop);
			switch (type)
			{
			case mm::Transmitter::ITM::SERVER:
				this->bind(addr, port);
				this->wait();
				break;
			case mm::Transmitter::ITM::CLIENT:
				this->connect(addr, port);
				break;
			case mm::Transmitter::ITM::BOTH_SER:
				break;
			case mm::Transmitter::ITM::BOTH_CLI:
				break;
			default:
				break;
			}
			loop.run(Loop::Default);
			return 0;
		}

		int  tTM::Unlink()
		{
			this->close();
			return 0;
		}

		int  tTM::Sendto(void* buf, size_t count)
		{
			write((char*)buf,count);
			return count;
		}

		int  tTM::Recfrm(void* buf, size_t count)
		{
			printf("%s recv data:%s,len = %d\n", user(), (char*)buf, count);
			return count;
		}

		//client need implement
		void tTM::OnConnected(mmerrno status) {
			assert(this->userType & 1);
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "on_connect error %s\n", Handle::errCode(status));
				return;
			}
			read_start();
			Sendto("hello!",6);
		}

		//server need implement
		void tTM::doAccept(mmerrno status) {
			assert(!(this->userType & 1));
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "New connection error %s\n", Handle::errCode(status));
				return;
			}
			tTM* s2c = new tTM();
			s2c->init(loop());
			if (accept((Stream*)s2c) == 0) {
				char ip[17] = { 0 };
				int  port = 0;
				s2c->getpeerIpPort(ip, port);
				printf("client accept client ip = %s,port = %d\n", ip, port);
				s2c->read_start();
			}
			else {
				s2c->close();
				delete s2c;
			}
		}

		//client or server need implement
		void tTM::OnRead(ssize_t nread, const char *buf)
		{
			if (nread < 0) {
				fprintf(stderr, "%s Read error %s\n", user(),Handle::errType(nread));
				close();
				return;
			}
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				void* data = Unpack((void*)buf, &nread);
				Recfrm((void*)buf, nread);
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				void* data = Unpack((void*)buf, &nread);
				Recfrm(data, nread);
			}
		}

		//client or client need implement
		void tTM::OnWrote(mmerrno status) {
			if (this->userType & 1) { //Type::CLIENT ||  Type::BOTH_CLI
				char sendbuf[1024];
				memset(sendbuf, 0, 1024);
				scanf("%s", sendbuf);
				int size = strlen(sendbuf) + 1;
				void* data = Packer((void*)sendbuf, &size);
				Sendto(sendbuf,size);
			}
			else { //Type::SERVER ||  Type::BOTH_SER
				int size = strlen("ok") + 1;
				void* data = Packer((void*)"ok",&size);
				Sendto(data, size);
			}
		}
	
		//udp
		void uTM::Packer(void * data, int size)
		{
		}

		void uTM::Unpack(void * data, int size)
		{
		}

		int  uTM::Relate(const char* addr, const int port, Type type)
		{
			Loop loop(false);
			this->userType = type;
			this->_addr = addr;
			this->_port = port;
			this->init(loop);
			switch (type)
			{
			case mm::Transmitter::ITM::SERVER:
				this->bind(addr, port, UDP::Reuseaddr);
				this->recv_start();
				break;
			case mm::Transmitter::ITM::CLIENT:
				this->bind(addr, port,UDP::Reuseaddr);
				this->recv_start();
				this->Sendto("hello",6);
				break;
			case mm::Transmitter::ITM::BOTH_SER:
				break;
			case mm::Transmitter::ITM::BOTH_CLI:
				break;
			default:
				break;
			}
			loop.run(Loop::Default);
			return 0;
		}

		int  uTM::Unlink()
		{
			this->close();
			return 0;
		}

		int  uTM::Sendto(void* buf, size_t count)
		{
			send((char*)buf, count, _addr,_port);
			return count;
		}

		int  uTM::Recfrm(void* buf, size_t count)
		{
			printf("%s recv data:%s,len = %d\n", user(), (char*)buf, count);
			return count;
		}

		void uTM::OnSent(mmerrno status)
		{
			if (status != mmerrno::mmSuccess) {
				fprintf(stderr, "Send error %s\n", Handle::errCode(status));
				return;
			}
		}

		void uTM::OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags)
		{
			sockaddr_in* psin = (sockaddr_in*)addr;
			printf("Recv from ip:%s,port:%d\n", inet_ntoa(psin->sin_addr), ntohs(psin->sin_port));
			printf("recv data:%s,len = %d\n", buf, nread);
			Sendto((void*)buf, nread);
			//send4(buf,nread,"192.168.100.90",1800);
		}
	}
}