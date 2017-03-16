#include "mmloop_net.h"

namespace mm {
	namespace uvbase {

		// -----------------------------
		// class Stream
		// -----------------------------

		Stream::Stream() {
		}

		int Stream::shutdown() {
			uv_shutdown_t* req = new uv_shutdown_t;
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_shutdown(req, stream, _cbShutdown);
		}

		int Stream::wait() {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_listen(stream, SOMAXCONN, _cbConnection);
		}

		int Stream::accept(Stream* client) {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			uv_stream_t* streamclient = (uv_stream_t *)client->context_ptr();
			return uv_accept(stream, streamclient);
		}

		int Stream::read_start() {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_read_start(stream, _cbAlloc, _cbRead);
		}

		int Stream::read_stop() {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_read_stop(stream);
		}

		int Stream::write(const char *buf, size_t length) {

			uv_buf_t wbuf = uv_buf_init((char *)buf, length);
			uv_write_t*	req = new uv_write_t;
			uv_stream_t * stream = (uv_stream_t *)context_ptr();
			return uv_write(req, stream, &wbuf, 1, _cbWrote);
		}


		int Stream::write(const char *buf, size_t length, Stream *send_handle) {

			uv_buf_t wbuf = uv_buf_init((char *)buf, length);
			uv_write_t *req = new uv_write_t;
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_write2(req, stream, &wbuf, 1, (uv_stream_t *)send_handle->context_ptr(), _cbWrote);
		}

		int Stream::try_write(const char *buf, size_t length) {
			uv_buf_t wbuf = uv_buf_init((char *)buf, length);

			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_try_write(stream, &wbuf, 1);
		}


		int Stream::set_blocking(int blocking) {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_stream_set_blocking(stream, blocking);
		}

		int Stream::is_readable() {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_is_readable(stream);
		}

		int Stream::is_writeable() {
			uv_stream_t* stream = (uv_stream_t *)context_ptr();
			return uv_is_writable(stream);
		}

		void Stream::_cbShutdown(uv_shutdown_t *req, int status) {
			uv_stream_t *stream = req->handle;

			//			Handle* handle = static_cast<Handle *>(stream->data);
			//			Stream* self = static_cast<Stream *>(handle);
			Stream* self = static_cast<Stream *>(stream->data);
			if (self != NULL) {
				self->OnShutdown((mmerrno)status);
			}
			delete req;
		}

		void Stream::_cbConnection(uv_stream_t *stream, int status) {

			Stream* self = static_cast<Stream *>(stream->data);
			if (self != NULL) {
				self->doAccept((mmerrno)status);
			}
		}

		void Stream::_cbAlloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
			buf->base = NULL;
			buf->len = 0;
			Stream* self = static_cast<Stream *>(handle->data);
			if (self != NULL)
				buf->base = (char*)self->doAllocate(suggested_size);

			if (buf->base)
			{
				buf->len = suggested_size;
				memset(buf->base, 0, buf->len);
			}
		}

		void Stream::_cbRead(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {

			Stream* self = static_cast<Stream *>(stream->data);
			if (self != NULL) {
				/*
				if (nread < 0) {
				fprintf(stderr, "Read error %s\n",  Error(nread).err_name());
				self->close();
				free(buf->base);
				return;
				}
				*/
				self->OnRead(nread, buf->base);
				self->doFree((void*)buf->base);
			}
		}

		void Stream::_cbWrote(uv_write_t *req, int status) {
			uv_stream_t *stream = req->handle;
			Stream* self = static_cast<Stream *>(stream->data);
			if (self != NULL) {
				self->OnWrote((mmerrno)status);
			}
			delete req;
		}


		// -----------------------------
		// class TCP
		// -----------------------------
		TCP::TCP() {
		}

		int TCP::init(Loop &loop) {
			this->Handle::init(loop);
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_init(loop.context_ptr(), tcp);
		}

		int TCP::init_ex(Loop &loop, int flags) {
			this->Handle::init(loop);
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_init_ex(loop.context_ptr(), tcp, flags);
		}

		int TCP::open(sock_t sock) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_open(tcp, sock);
		}

		int TCP::connected_open(sock_t sock) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_open(tcp, sock);
			//return uv_tcp_connected_open(tcp,sock);//version 1.9.1
			/*
			int r = uv_tcp_open(tcp, sock);
			if (r != 0)
			        return r;
			uv_connection_init((uv_stream_t*)tcp);
			// AcceptEx() implicitly binds the accepted socket.
			tcp->flags |= UV_HANDLE_BOUND | UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;
			return 0;
			*/
		}

		int TCP::nodelay(int enable) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_nodelay(tcp, enable);
		}

		int TCP::keepalive(int enable, unsigned int delay) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_keepalive(tcp, enable, delay);
		}

		int TCP::simultaneous_accepts(int enable) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_simultaneous_accepts(tcp, enable);
		}

		int TCP::bind(const sockaddr *addr, unsigned int flags) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_bind(tcp, addr, flags);
		}

		int TCP::bind(const char *ip, int port)	{
			if (isIPV4(ip)) {
				struct sockaddr_in addr;
				int r = uv_ip4_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return bind((const sockaddr *)&addr, 0);
			}
			else {
				struct sockaddr_in6 addr;
				int r = uv_ip6_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return bind((const sockaddr *)&addr, 0);
			}
		}

		int TCP::getsockname(struct sockaddr *name, int *namelen) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_getsockname(tcp, name, namelen);
		}

		void TCP::getlocaleIpPort(char* ip, int& port) {
			struct sockaddr localename;
			int namelen = sizeof localename;
			getsockname(&localename, &namelen);
			struct sockaddr_in* addr2 = (struct sockaddr_in*)&localename;
			uv_ip4_name(addr2, ip, 17);
			port = ntohs(addr2->sin_port);
		}

		int TCP::getpeername(struct sockaddr *name, int *namelen) {
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_getpeername(tcp, name, namelen);
		}

		void TCP::getpeerIpPort(char* ip, int& port) {
			struct sockaddr peername;
			int namelen = sizeof peername;
			getpeername(&peername, &namelen);
			struct sockaddr_in* addr2 = (struct sockaddr_in*)&peername;
			uv_ip4_name(addr2, ip, 17);
			port = ntohs(addr2->sin_port);
		}

		int TCP::connect(const struct sockaddr *addr) {
			uv_connect_t *req = new uv_connect_t;
			uv_tcp_t* tcp = (uv_tcp_t *)context_ptr();
			return uv_tcp_connect(req, tcp, addr, _cbConnect);
		}

		int TCP::connect(const char *ip, int port) {
			if (isIPV4(ip)) {
				struct sockaddr_in addr;
				int r = uv_ip4_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return connect((const struct sockaddr *)&addr);
			}
			else {
				struct sockaddr_in6 addr;
				int r = uv_ip6_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return connect((const struct sockaddr *)&addr);
			}
		}

		void TCP::_cbConnect(uv_connect_t *req, int status) {
			uv_stream_t *stream = req->handle;
			TCP* self = static_cast<TCP *>(stream->data);
			if (self != NULL) {
				self->OnConnected((mmerrno)status);
			}
			delete req;
		}

		// -----------------------------
		// class UDP
		// -----------------------------
		UDP::UDP()
		{
		}

		int UDP::init(Loop &loop) {
			this->Handle::init(loop);
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_init(loop.context_ptr(), udp);
		}

		int UDP::init_ex(Loop &loop, unsigned int flags) {
			this->Handle::init(loop);
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_init_ex(loop.context_ptr(), udp, flags);
		}

		int UDP::open(sock_t sock) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_open(udp, sock);
		}

		int UDP::bind(const struct sockaddr *addr, unsigned int flags) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_bind(udp, addr, flags);
		}

		int UDP::bind(const char *ip, int port, unsigned int flags) {
			if (isIPV4(ip)) {
				struct sockaddr_in addr;
				int r = uv_ip4_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return bind((const struct sockaddr *)&addr, flags);
			}
			else {
				struct sockaddr_in6 addr;
				int r = uv_ip6_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return bind((const struct sockaddr *)&addr, flags);
			}
		}

		int UDP::getsockname(struct sockaddr *name, int *namelen) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_getsockname(udp, name, namelen);
		}

		int UDP::set_membership(const char *multicast_addr, const char *interface_addr, membership_t membership) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_membership(udp, multicast_addr, interface_addr, membership);
		}

		int UDP::set_multicast_loop(int on) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_multicast_loop(udp, on);
		}

		int UDP::set_multicast_ttl(int ttl) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_multicast_ttl(udp, ttl);
		}

		int UDP::set_multicast_interface(const char *interface_addr) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_multicast_interface(udp, interface_addr);
		}

		int UDP::set_broadcast(int on) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_broadcast(udp, on);
		}

		int UDP::set_ttl(int ttl) {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_set_ttl(udp, ttl);
		}

		void UDP::get_ip4_name(const struct sockaddr_in* src, char* dst, size_t size) {
			uv_ip4_name(src, dst, size);
		}

		int UDP::send(const char *buf, size_t length, const struct sockaddr *addr) {
			uv_buf_t sendbuf = uv_buf_init((char *)buf, length);
			uv_udp_send_t* req = new uv_udp_send_t;
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_send(req, udp, &sendbuf, 1, addr, _cbSent);
		}

		int UDP::send(const char *buf, size_t length, const char *ip, int port) {
			if (isIPV4(ip)) {
				struct sockaddr_in send_addr;
				int r = uv_ip4_addr(ip, port, &send_addr);
				if (r < 0)
					return r;
				return send(buf, length, (const struct sockaddr *)&send_addr);
			}
			else {
				struct sockaddr_in6 addr;
				int r = uv_ip6_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return send(buf, length, (const struct sockaddr *)&addr);
			}
		}

		int UDP::try_send(const char *buf, size_t length, const struct sockaddr *addr) {
			uv_buf_t sendbuf = uv_buf_init((char *)buf, length);
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_try_send(udp, &sendbuf, 1, addr);
		}

		int UDP::try_send(const char *buf, size_t length, const char *ip, int port) {
			if (isIPV4(ip)) {
				struct sockaddr_in send_addr;
				int r = uv_ip4_addr(ip, port, &send_addr);
				if (r < 0)
					return r;
				return try_send(buf, length, (const struct sockaddr *)&send_addr);
			}
			else {
				struct sockaddr_in6 addr;
				int r = uv_ip6_addr(ip, port, &addr);
				if (r < 0)
					return r;
				return try_send(buf, length, (const struct sockaddr *)&addr);
			}
		}

		int UDP::recv_start() {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_recv_start(udp, _cbAlloc, _cbRecv);
		}

		int UDP::recv_stop() {
			uv_udp_t* udp = (uv_udp_t *)context_ptr();
			return uv_udp_recv_stop(udp);
		}

		void UDP::_cbSent(uv_udp_send_t *req, int status)
		{
			uv_udp_t* udp = req->handle;
			UDP* self = static_cast<UDP *>(udp->data);
			if (self != NULL) {
				self->OnSent((mmerrno)status);
			}
			delete req;
		}

		void UDP::_cbAlloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
			buf->base = (char*)malloc(suggested_size);
			buf->len = suggested_size;
			memset(buf->base, 0, buf->len);
		}

		void UDP::_cbRecv(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags) {
			UDP* self = static_cast<UDP *>(handle->data);
			if (self != NULL) {
				/*				if (nread < 0) {
				fprintf(stderr, "Read error %s\n", Error(nread).err_name());
				self->close();
				free(buf->base);
				return;
				}*/
				self->OnReceived(nread, buf->base, addr, flags);
				free(buf->base);
			}
		}

		// -----------------------------
		// class DNS
		// -----------------------------

		DNS::DNS()
		{
		}

		int DNS::getAddrInfo(Loop &loop, const char* node, const char* service, const struct addrinfo* hints) {
			uv_getaddrinfo_t *req = new uv_getaddrinfo_t;
			req->data = reinterpret_cast<void *>(this);
			return uv_getaddrinfo(loop.context_ptr(), req, _cbResolved, node, service, hints);
		}

		void DNS::_cbResolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res)	{
			DNS *h = static_cast<DNS *>(resolver->data);
			if (NULL != h)
			{
				char addr[17] = { '\0' };
				uv_ip4_name((struct sockaddr_in*) res->ai_addr, addr, 16);
				h->onResolved((Handle::mmerrno)status, addr);
				uv_freeaddrinfo(res);
			}
			resolver->data = NULL;
			delete resolver;
		}
	}
} //namespace mm::uvbase