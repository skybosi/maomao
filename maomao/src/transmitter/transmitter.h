#pragma once
#include "mmloop_net.h"

using namespace mm::uvbase;
typedef  TCP  baseT;                       /*Provide a transport layer base class,Now(2017-3-14) is uv::base::TCP*/
namespace mm {
	namespace Transmitter {

		class transmitter : public baseT
		{
		public:			
			enum Type {
				SERVER = 0,                /* Just a server */
				CLIENT,                    /* Just a client */
				BOTH_SER,                  /* server or client,Tend to server */
				BOTH_CLI,                  /* server or client,Tend to client */
			};
			transmitter(Type type = SERVER);
			~transmitter();
		public:
			/* will be inpmliment a client */
			virtual void OnConnected(mmerrno status);
			/* will be inpmliment a server */
			virtual void doAccept(mmerrno status);
		public:
			/* I/O ,if read a data,will be save a buf*/
			virtual void OnRead(ssize_t nread, const char *buf);
			/* I/O ,if write a data*/
			virtual void OnWrote(mmerrno status);
		private:
			Type userType;
		};
		typedef transmitter Tran;
	}

}