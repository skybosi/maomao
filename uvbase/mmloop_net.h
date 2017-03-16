#pragma once
#ifndef __MMLOOP_NET_H__
#define __MMLOOP_NET_H__

#include "mmloop.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

namespace mm {
	namespace uvbase {
class MM_LOOP_API Stream;
class MM_LOOP_API TCP;
class MM_LOOP_API UDP;
class MM_LOOP_API DNS;
		// -----------------------------
		// class Stream
		// -----------------------------
#define isIPV4(ip) (strchr((ip), '.'))

		class Stream : public Handle
		{
		protected:
			Stream();

		public:
			int shutdown();
			int wait();
			int accept(Stream* client);
			int read_start();
			int read_stop();
			int write(const char *buf, size_t length);
			int write(const char *buf, size_t length, Stream *send_handle);
			int try_write(const char *buf, size_t length);

			int set_blocking(int blocking);
			int is_readable();
			int is_writeable();

		protected:
			// called when the stream is shutdown
			virtual void OnShutdown(mmerrno status) {}

			// tiggered when a new incomming connection is detected by listen()
			virtual void doAccept(mmerrno status) {}

			// called after buffer has been written into the stream
			virtual void OnWrote(mmerrno status) {}
			// called after buffer has been read from the stream
			virtual void OnRead(ssize_t nread, const char *buf) {} // TODO: uv_buf_t is unacceptable to appear here, must take a new manner known in this C++ wrapper level

			virtual void* doAllocate(size_t suggested_size) { return malloc(suggested_size); }
			virtual void doFree(void* buf) { free(buf); }

		private:
			static void _cbShutdown(uv_shutdown_t *req, int status);
			static void _cbConnection(uv_stream_t *stream, int status);
			static void _cbAlloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
			static void _cbRead(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
			static void _cbWrote(uv_write_t *req, int status);

		};

		// -----------------------------
		// class TCP
		// -----------------------------
		class TCP : public Stream
		{
		public:
			typedef uv_os_sock_t sock_t;

		public:
			TCP();
			int init(Loop &loop);
			int init_ex(Loop &loop, int flags);
			int open(sock_t sock);
			int connected_open(sock_t sock);
			int nodelay(int enable);
			int keepalive(int enable, unsigned int delay);
			int simultaneous_accepts(int enable);
			int bind(const char *ip, int port);
			int getsockname(struct sockaddr *name, int *namelen);
			int getpeername(struct sockaddr *name, int *namelen);
			void getlocaleIpPort(char* ip, int& port);
			void getpeerIpPort(char* ip, int& port);
			int  connect(const char *ip, int port);

		protected:
			// TODO: must enumerate all the status in the class
			virtual void OnConnected(mmerrno status) {}

		private:
			int connect(const struct sockaddr *addr);
			int bind(const sockaddr *addr, unsigned int flags);

		private:
			static void _cbConnect(uv_connect_t *req, int status);
		};


		// -----------------------------
		// class UDP
		// -----------------------------
		class UDP : public Handle
		{
		public:
			enum udp_flags {
				Ipv6Only = UV_UDP_IPV6ONLY,
				Partial = UV_UDP_PARTIAL,
				Reuseaddr = UV_UDP_REUSEADDR
			};

			typedef uv_os_sock_t sock_t;
			typedef uv_membership membership_t;

		public:
			UDP();
			int init(Loop &loop);
			int init_ex(Loop &loop, unsigned int flags);
			int open(sock_t sock);
			int getsockname(struct sockaddr *name, int *namelen);
			int set_membership(const char *multicast_addr, const char *interface_addr, membership_t membership);
			int set_multicast_loop(int on);
			int set_multicast_ttl(int ttl);
			int set_multicast_interface(const char *interface_addr);
			int set_broadcast(int on);
			int set_ttl(int ttl);
			void get_ip4_name(const struct sockaddr_in* src, char* dst, size_t size);
			int bind(const char *ip, int port, unsigned int flags);
			int send(const char *buf, size_t length, const char *ip, int port);
			int try_send(const char *buf, size_t length, const char *ip, int port);
			int bind(const struct sockaddr *addr, unsigned int flags);
			int recv_start();
			int recv_stop();

		protected:
			// 
			virtual void OnSent(mmerrno status) {}
			//	virtual void OnAllocate(UDP *self, size_t suggested_size, uv_buf_t *buf) {}
			virtual void OnReceived(ssize_t nread, const char *buf, const struct sockaddr *addr, unsigned flags) {}
			int send(const char *buf, size_t length, const struct sockaddr *addr);
			int try_send(const char *buf, size_t length, const struct sockaddr *addr);
		private:
			static void _cbSent(uv_udp_send_t *req, int status);
			static void _cbAlloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
			static void _cbRecv(uv_udp_t *udp, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags);
		};

		// -----------------------------
		// class DNS
		// -----------------------------
		class DNS
		{
		public:
			DNS();
			int getAddrInfo(Loop &loop, const char* node, const char* service, const struct addrinfo* hints);

		protected:
			virtual void onResolved(Handle::mmerrno status, const char* ip) {}

		private:
			static void _cbResolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res);

		};
	}
}//namespace mm::uvbase

#endif //mmloop_net.h