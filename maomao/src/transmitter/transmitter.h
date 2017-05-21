#pragma once
#include "mmloop_net.h"

using namespace mm::uvbase;
typedef  TCP  baseT;                       /*Provide a transport layer base class,Now(2017-3-14) is uv::base::TCP*/
typedef  UDP  baseU;                       /*Provide a transport layer base class,Now(2017-3-14) is uv::base::UDP*/

namespace mm {
	namespace Transmitter {
		/*
			interface of Transmitter
		*/
		class ITM
		{
		/*
		protected:
			ITM();
			~ITM();
		*/
		public:
			enum Type {
				SERVER = 0,                /* Just a server */
				CLIENT,                    /* Just a client */
				BOTH_SER,                  /* server or client,Tend to server */
				BOTH_CLI,                  /* server or client,Tend to client */
			};
		public:
			/*
			- �������ӿ�
			0. ��ϵ Relate   : �ϲ��ȡһ��������
			1. ��� Packet   : ���ϲ��ԭ���ݴ����Ϊ����׼��(private)
			2. ���� Sendto   : ���Ͱ�װ�õ����ݰ�
			3. ���� Recfrm   : ���յ���ص����ݰ�
			4. ��� Unpack   : �⿪��װ��׼�����ϲ����ԭ����(private)
			5. ȡ�� Unlink   : ���ν�����ȡ���봫��������ϵ
			*/
			virtual int   Relate(const char* addr,const int port,Type type = SERVER) = 0;
			virtual int   Unlink() = 0;
			virtual void* Packer(void* data, int* size) = 0;
			virtual void* Unpack(void* data, int* size) = 0;
			virtual int   Sendto(void* buf, size_t count) = 0;
			virtual int   Recfrm(void* buf, size_t count) = 0;
		private:

		};
		
		class tTM :public ITM, public baseT
		{			
		
		public:	
			tTM();
			~tTM();
		public:
			const char* _type[5] = { "server","client","both_ser","both_cli","unknow" };
			inline const char* user() { return _type[userType]; }

		public:
			virtual int  Relate(const char* addr, const int port, Type type = Type::SERVER);
			virtual int  Unlink();
			/* post */
			virtual int  Sendto(void* buf, size_t count);
			/* get */
			virtual int  Recfrm(void* buf, size_t count);
		private:
			virtual void* Packer(void* data, int* size);
			virtual void* Unpack(void* data, int* size);
		private:
			/* will be inpmliment a client */
			virtual void OnConnected(mmerrno status);
			/* will be inpmliment a server */
			virtual void doAccept(mmerrno status);
			/* I/O ,if read a data,will be save a buf*/
			virtual void OnRead(ssize_t nread, const char *buf);
			/* I/O ,if write a data*/
			virtual void OnWrote(mmerrno status);
		private:
			Type userType;
		};
		typedef tTM TTM;

		class uTM :public ITM, public baseU
		{
		/*
		public:
			uTM();
			~uTM();
		*/
		public:
			const char* _type[5] = { "server","client","both_ser","both_cli","unknow" };
			inline const char* user() { return _type[userType]; }

		public:
			virtual int  Relate(const char* addr, const int port, Type type = Type::SERVER);
			virtual int  Unlink();
			/* post */
			virtual int  Sendto(void* buf, size_t count);
			/* get */
			virtual int  Recfrm(void* buf, size_t count);
		private:
			virtual void Packer(void* data, int size);
			virtual void Unpack(void* data, int size);
		private:
			virtual void OnSent(mmerrno status);
			//	virtual void OnAllocate(UDP *self, size_t suggested_size, uv_buf_t *buf) {}
			virtual void OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags);
		private:
			Type userType;
			const char* _addr;
			int  _port;
		};
		typedef uTM UTM;
	}

}