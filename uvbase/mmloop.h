#pragma once
#ifndef _MMLOOP_H_
#define _MMLOOP_H_

#include <stdarg.h>
#include "platform.h"
#include "uv.h"

namespace mm {
namespace uvbase {
	class MM_LOOP_API Loop;
	class MM_LOOP_API Handle;
	class MM_LOOP_API Idle;
	class MM_LOOP_API Timer;
	class MM_LOOP_API Async;
	class MM_LOOP_API Signal;
	class MM_LOOP_API CpuInfo;
	class Loop;
	// -----------------------------
	// class Handle
	// -----------------------------
	class Handle
	{
	public:
		typedef uv_os_fd_t fd_t;

		typedef enum _mmerrno
		{
			//errno.h error number
			mmSuccess           = 0,
			mmNotPermitted      = EPERM,	        // operation not permitted
			mmNoFile            = ENOENT,		    // no such file or directory
			mmNoProcess         = ESRCH,		    // no such process
			mmIntr              = EINTR,			// interrupted system call
			mmIO                = EIO,				// i/o error
			mmNotDevOrAddress   = ENXIO,		    // no such device or address
			mmArgTooLong        = E2BIG,			// argument list too long
			mmENOEXEC           = ENOEXEC,          // exec format error (POSIX.1)
			mmBadFd             = EBADF,			// bad file descriptor
			mmECHILD            = ECHILD,			// No child processes (POSIX.1)
			mmResUnavailable    = EAGAIN,		    // resource temporarily unavailable
			mmNotEnoughMemory   = ENOMEM,		    // not enough memory
			mmPermissionDenied  = EACCES,	        // permission denied
			mmBadAddress        = EFAULT,			// bad address in system call argument
			mmResBusy           = EBUSY,			// resource busy or locked
			mmFileAlreadyExists = EEXIST,	        // file already exists
			mmNotPermittedLink  = EXDEV,		    // cross-device link not permitted
			mmNotDevice         = ENODEV,			// no such device
			mmNotDirectory      = ENOTDIR,		    // not a directory
			mmEISDIR            = EISDIR,			// illegal operation on a directory
			mmENFILE            = ENFILE,			// file table overflow
			mmTooMany           = EMFILE,			// too many open files
			mmENOTTY            = ENOTTY,           // Inappropriate I/O control operation (POSIX.1)
			mmFileTooLarge      = EFBIG,			// file too large
			mmNoSpace           = ENOSPC,			// no space left on device
			mmInvalidSeek       = ESPIPE,			// invalid seek
			mmROFS              = EROFS,			// read-only file system
			mmTooManyLinks      = EMLINK,		    // too many links
			mmBorkenPipe        = EPIPE,			// broken pipe
			mmEDOM              = EDOM,             // Mathematics argument out of domain of function (POSIX.1, C99)
			mmEDEADLK           = EDEADLK,          // Resource deadlock avoided (POSIX.1)
			mmNameTooLong       = ENAMETOOLONG,     // name too long
			mmNOLCK             = ENOLCK,           // No locks available (POSIX.1)
			mmFunNotImpl        = ENOSYS,			// function not implemented
			mmDirNotEmpty       = ENOTEMPTY,		// directory not empty

			// uv error number
			mm_EOF              = UV__EOF,
			mm_UNKNOWN          = UV__UNKNOWN,
			mm_EAI_ADDRFAMILY   = UV__EAI_ADDRFAMILY,
			mm_EAI_AGAIN        = UV__EAI_AGAIN,
			mm_EAI_BADFLAGS     = UV__EAI_BADFLAGS,
			mm_EAI_CANCELED     = UV__EAI_CANCELED,
			mm_EAI_FAIL         = UV__EAI_FAIL,
			mm_EAI_FAMILY       = UV__EAI_FAMILY,
			mm_EAI_MEMORY       = UV__EAI_MEMORY,
			mm_EAI_NODATA       = UV__EAI_NODATA,
			mm_EAI_NONAME       = UV__EAI_NONAME,
			mm_EAI_OVERFLOW     = UV__EAI_OVERFLOW,
			mm_EAI_SERVICE      = UV__EAI_SERVICE,
			mm_EAI_SOCKTYPE     = UV__EAI_SOCKTYPE,
			mm_EAI_BADHINTS     = UV__EAI_BADHINTS,
			mm_EAI_PROTOCOL     = UV__EAI_PROTOCOL,
			mm_E2BIG            = UV__E2BIG,
			mm_EACCES           = UV__EACCES,
			mm_EADDRINUSE       = UV__EADDRINUSE,
			mm_EADDRNOTAVAIL    = UV__EADDRNOTAVAIL,
			mm_EAFNOSUPPORT     = UV__EAFNOSUPPORT,
			mm_EAGAIN           = UV__EAGAIN,
			mm_EALREADY         = UV__EALREADY,
			mm_EBADF            = UV__EBADF,
			mm_EBUSY            = UV__EBUSY,
			mm_ECANCELED        = UV__ECANCELED,
			mm_ECHARSET         = UV__ECHARSET,
			mm_ECONNABORTED     = UV__ECONNABORTED,
			mm_ECONNREFUSED     = UV__ECONNREFUSED,
			mm_ECONNRESET       = UV__ECONNRESET,
			mm_EDESTADDRREQ     = UV__EDESTADDRREQ,
			mm_EEXIST           = UV__EEXIST,
			mm_EFAULT           = UV__EFAULT,
			mm_EHOSTUNREACH     = UV__EHOSTUNREACH,
			mm_EINTR            = UV__EINTR,
			mm_EINVAL           = UV__EINVAL,
			mm_EIO              = UV__EIO,
			mm_EISCONN          = UV__EISCONN,
			mm_EISDIR           = UV__EISDIR,
			mm_ELOOP            = UV__ELOOP,
			mm_EMFILE           = UV__EMFILE,
			mm_EMSGSIZE         = UV__EMSGSIZE,
			mm_ENAMETOOLONG     = UV__ENAMETOOLONG,
			mm_ENETDOWN         = UV__ENETDOWN,
			mm_ENETUNREACH      = UV__ENETUNREACH,
			mm_ENFILE           = UV__ENFILE,
			mm_ENOBUFS          = UV__ENOBUFS,
			mm_ENODEV           = UV__ENODEV,
			mm_ENOENT           = UV__ENOENT,
			mm_ENOMEM           = UV__ENOMEM,
			mm_ENONET           = UV__ENONET,
			mm_ENOSPC           = UV__ENOSPC,
			mm_ENOSYS           = UV__ENOSYS,
			mm_ENOTCONN         = UV__ENOTCONN,
			mm_ENOTDIR          = UV__ENOTDIR,
			mm_ENOTEMPTY        = UV__ENOTEMPTY,
			mm_ENOTSOCK         = UV__ENOTSOCK,
			mm_ENOTSUP          = UV__ENOTSUP,
			mm_EPERM            = UV__EPERM,
			mm_EPIPE            = UV__EPIPE,
			mm_EPROTO           = UV__EPROTO,
			mm_EPROTONOSUPPORT  = UV__EPROTONOSUPPORT,
			mm_EPROTOTYPE       = UV__EPROTOTYPE,
			mm_EROFS            = UV__EROFS,
			mm_ESHUTDOWN        = UV__ESHUTDOWN,
			mm_ESPIPE           = UV__ESPIPE,
			mm_ESRCH            = UV__ESRCH,
			mm_ETIMEDOUT        = UV__ETIMEDOUT,
			mm_ETXTBSY          = UV__ETXTBSY,
			mm_EXDEV            = UV__EXDEV,
			mm_EFBIG            = UV__EFBIG,
			mm_ENOPROTOOPT      = UV__ENOPROTOOPT,
			mm_ERANGE           = UV__ERANGE,
			mm_ENXIO            = UV__ENXIO,
			mm_EMLINK           = UV__EMLINK,
			mm_EHOSTDOWN        = UV__EHOSTDOWN,
		} mmerrno;

		static const char* errCode(mmerrno err) { return errCode((int)err); }
		static const char* errCode(int err) { return uv_strerror(err); }
		static const char* errType(mmerrno err) { return errType((int)err); }
		static const char* errType(int err) { return uv_err_name(err); }

	protected:
		Handle();
		Handle(Handle &);
		Handle &operator=(Handle &);
		virtual ~Handle();

		void init(Loop &loop);

	public:
		void* data;
		void close();
		void ref();
		void unref();
		int has_ref();

		int is_active();
		int is_closing();
		int send_buffer_size(int *value);
		int recv_buffer_size(int *value);
		int fileno(fd_t* fd);
		void deleteContext();
		Loop& loop();

	protected:
		virtual void OnClose() {}
		uv_handle_t *context_ptr();


	private:
		static void _cbClose(uv_handle_t *uvhandle);

		uv_any_handle* context;
		Loop* _loop;
	};


	// -----------------------------
	// class Loop
	// -----------------------------
	class Loop
	{
	public:
		enum RunMode {
			Default = UV_RUN_DEFAULT,
			Once = UV_RUN_ONCE,
			NoWait = UV_RUN_NOWAIT
		};

		explicit Loop(bool defaultLoop = true);
		virtual ~Loop();
		int config(uv_loop_option option = UV_LOOP_BLOCK_SIGNAL,...);
		static uv_loop_t* default_loop();
		bool run(RunMode mode);
		void stop();
		int close();
		int alive();
		size_t loop_size();
		int backend_fd();
		int backend_timeout();

		uint64_t now();
		void update_time();
		uv_loop_t *context_ptr();
		void walk(void* arg);

	protected:
		virtual void OnWalk(Handle *handle, void* arg) {}

	private:
		uv_loop_t* _uvLoop;

		static void _doWalk(uv_handle_t* uvhandle, void *arg);
	};

	// -----------------------------
	// class Request
	// -----------------------------
	class Request
	{
	protected:
		Request();
		virtual ~Request();
		void init();
		int cancel();

	private:
		Request(Request &) {}
		Request &operator=(Request &) {}
	protected:
		uv_req_t *context_ptr();

	private:
		uv_any_req* context;
	};


	// -----------------------------
	// class Idle
	// -----------------------------
	class Idle : public Handle
	{
	public:
		Idle();
		int init(Loop &loop);
		int start();
		int stop();

	protected:
		virtual void OnIdle() {}

	private:
		static void _cbOnIdle(uv_idle_t* uvhandle);
	};

	// -----------------------------
	// class Async
	// -----------------------------
	class Async : public Handle
	{
	public:
		Async();
		int init(Loop &loop);
		int send();

	protected:
		virtual void OnAsync() {}

	private:
		static void _cbAsync(uv_async_t *async);
	};

	// -----------------------------
	// class Signal
	// -----------------------------
	class Signal : public Handle
	{
	public:
		Signal();
		int init(Loop &loop);

#if UV_VERSION_HEX >= ( (1<<16) | (12<<8) | (0) ) //version 1.12.0
		enum SiGSHOTMODE
		{
			DEFAULT = 0,
			ONESHOT
		};
		int start(int signum, SiGSHOTMODE sigmode = DEFAULT);
#else
		int start(int signum);
#endif
		
		int stop();

	protected:
		virtual void OnSignal(int signum) {}

	private:
		static void _cbSignal(uv_signal_t *signal, int signum);
	};

	}
} // namespace mm::uvbase

#endif // mmloop.h
