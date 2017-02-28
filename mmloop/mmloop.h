#pragma once
#ifndef _MMLOOP_H_
#define _MMLOOP_H_

#include "platform.h"
#include "uv.h"

namespace mm {
namespace Loop {
	class ZQ_ELOOP_API Loop;
	class ZQ_ELOOP_API Handle;
	class ZQ_ELOOP_API Idle;
	class ZQ_ELOOP_API Timer;
	class ZQ_ELOOP_API Async;
	class ZQ_ELOOP_API Signal;
	class ZQ_ELOOP_API CpuInfo;
	class Loop;
	// -----------------------------
	// class Handle
	// -----------------------------
	class Handle
	{
	public:
		typedef uv_os_fd_t fd_t;

		typedef enum _ElpeError
		{
			elpeSuccess = 0,
			elpeNotPermitted = EPERM,	   // operation not permitted
			elpeNoFile = ENOENT,		   //no such file or directory
			elpeNoProcess = ESRCH,		   //no such process
			elpeIntr = EINTR,			   //interrupted system call
			elpeIO = EIO,				   //i/o error
			elpeNotDevOrAddress = ENXIO,			//no such device or address
			elpeArgTooLong = E2BIG,			//argument list too long
			elpeENOEXEC = ENOEXEC,
			elpeBadFd = EBADF,				//bad file descriptor
			elpeECHILD = ECHILD,			//
			elpeResUnavailable = EAGAIN,			//resource temporarily unavailable
			elpeNotEnoughMemory = ENOMEM,			//not enough memory
			elpePermissionDenied = EACCES,			//permission denied
			elpeBadAddress = EFAULT,			//bad address in system call argument
			elpeResBusy = EBUSY,				//resource busy or locked
			elpeFileAlreadyExists = EEXIST,			//file already exists
			elpeNotPermittedLink = EXDEV,				//cross-device link not permitted
			elpeNotDevice = ENODEV,			//no such device
			elpeNotDirectory = ENOTDIR,		//not a directory
			elpeEISDIR = EISDIR,			//illegal operation on a directory
			elpeENFILE = ENFILE,			//file table overflow
			elpeTooMany = EMFILE,			//too many open files
			elpeENOTTY = ENOTTY,
			elpeFileTooLarge = EFBIG,				//file too large
			elpeNoSpace = ENOSPC,			//no space left on device
			elpeInvalidSeek = ESPIPE,			//invalid seek
			elpeROFS = EROFS,				//read-only file system
			elpeTooManyLinks = EMLINK,			//too many links
			elpeBorkenPipe = EPIPE,				//broken pipe
			elpeEDOM = EDOM,
			elpeEDEADLK = EDEADLK,
			elpeNameTooLong = ENAMETOOLONG, //name too long
			elpeNOLCK = ENOLCK,
			elpeFunNotImpl = ENOSYS,			//function not implemented
			elpeDirNotEmpty = ENOTEMPTY,		//directory not empty
			elpe__EOF = UV__EOF,
			elpe__UNKNOWN = UV__UNKNOWN,
			elpe__EAI_ADDRFAMILY = UV__EAI_ADDRFAMILY,
			elpe__EAI_AGAIN = UV__EAI_AGAIN,
			elpe__EAI_BADFLAGS = UV__EAI_BADFLAGS,
			elpe__EAI_CANCELED = UV__EAI_CANCELED,
			elpe__EAI_FAIL = UV__EAI_FAIL,
			elpe__EAI_FAMILY = UV__EAI_FAMILY,
			elpe__EAI_MEMORY = UV__EAI_MEMORY,
			elpe__EAI_NODATA = UV__EAI_NODATA,
			elpe__EAI_NONAME = UV__EAI_NONAME,
			elpe__EAI_OVERFLOW = UV__EAI_OVERFLOW,
			elpe__EAI_SERVICE = UV__EAI_SERVICE,
			elpe__EAI_SOCKTYPE = UV__EAI_SOCKTYPE,
			elpe__EAI_BADHINTS = UV__EAI_BADHINTS,
			elpe__EAI_PROTOCOL = UV__EAI_PROTOCOL,
			elpe__E2BIG = UV__E2BIG,
			elpe__EACCES = UV__EACCES,
			elpe__EADDRINUSE = UV__EADDRINUSE,
			elpe__EADDRNOTAVAIL = UV__EADDRNOTAVAIL,
			elpe__EAFNOSUPPORT = UV__EAFNOSUPPORT,
			elpe__EAGAIN = UV__EAGAIN,
			elpe__EALREADY = UV__EALREADY,
			elpe__EBADF = UV__EBADF,
			elpe__EBUSY = UV__EBUSY,
			elpe__ECANCELED = UV__ECANCELED,
			elpe__ECHARSET = UV__ECHARSET,
			elpe__ECONNABORTED = UV__ECONNABORTED,
			elpe__ECONNREFUSED = UV__ECONNREFUSED,
			elpe__ECONNRESET = UV__ECONNRESET,
			elpe__EDESTADDRREQ = UV__EDESTADDRREQ,
			elpe__EEXIST = UV__EEXIST,
			elpe__EFAULT = UV__EFAULT,
			elpe__EHOSTUNREACH = UV__EHOSTUNREACH,
			elpe__EINTR = UV__EINTR,
			elpe__EINVAL = UV__EINVAL,
			elpe__EIO = UV__EIO,
			elpe__EISCONN = UV__EISCONN,
			elpe__EISDIR = UV__EISDIR,
			elpe__ELOOP = UV__ELOOP,
			elpe__EMFILE = UV__EMFILE,
			elpe__EMSGSIZE = UV__EMSGSIZE,
			elpe__ENAMETOOLONG = UV__ENAMETOOLONG,
			elpe__ENETDOWN = UV__ENETDOWN,
			elpe__ENETUNREACH = UV__ENETUNREACH,
			elpe__ENFILE = UV__ENFILE,
			elpe__ENOBUFS = UV__ENOBUFS,
			elpe__ENODEV = UV__ENODEV,
			elpe__ENOENT = UV__ENOENT,
			elpe__ENOMEM = UV__ENOMEM,
			elpe__ENONET = UV__ENONET,
			elpe__ENOSPC = UV__ENOSPC,
			elpe__ENOSYS = UV__ENOSYS,
			elpe__ENOTCONN = UV__ENOTCONN,
			elpe__ENOTDIR = UV__ENOTDIR,
			elpe__ENOTEMPTY = UV__ENOTEMPTY,
			elpe__ENOTSOCK = UV__ENOTSOCK,
			elpe__ENOTSUP = UV__ENOTSUP,
			elpe__EPERM = UV__EPERM,
			elpe__EPIPE = UV__EPIPE,
			elpe__EPROTO = UV__EPROTO,
			elpe__EPROTONOSUPPORT = UV__EPROTONOSUPPORT,
			elpe__EPROTOTYPE = UV__EPROTOTYPE,
			elpe__EROFS = UV__EROFS,
			elpe__ESHUTDOWN = UV__ESHUTDOWN,
			elpe__ESPIPE = UV__ESPIPE,
			elpe__ESRCH = UV__ESRCH,
			elpe__ETIMEDOUT = UV__ETIMEDOUT,
			elpe__ETXTBSY = UV__ETXTBSY,
			elpe__EXDEV = UV__EXDEV,
			elpe__EFBIG = UV__EFBIG,
			elpe__ENOPROTOOPT = UV__ENOPROTOOPT,
			elpe__ERANGE = UV__ERANGE,
			elpe__ENXIO = UV__ENXIO,
			elpe__EMLINK = UV__EMLINK,
			elpe__EHOSTDOWN = UV__EHOSTDOWN,
		} ElpeError;

		static const char* errDesc(ElpeError err) { return errDesc((int)err); }
		static const char* errDesc(int err) { return uv_strerror(err); }
		static const char* errName(ElpeError err) { return errName((int)err); }
		static const char* errName(int errNum) { return uv_err_name(errNum); }

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
		void _deleteContext();
		Loop& get_loop();

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

		bool run(RunMode mode);
		void stop();
		int close();
		int alive();
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
	// class Timer
	// -----------------------------
	class Timer : public Handle
	{
	public:
		Timer();
		int init(Loop &loop);
		int start(uint64_t timeout, uint64_t repeat);
		int stop();
		int again();
		void set_repeat(uint64_t repeat);
		uint64_t get_repeat();

	protected:
		virtual void OnTimer() {}

	private:
		static void _cbOnTimer(uv_timer_t *timer);
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
		int start(int signum);
		int stop();

	protected:
		virtual void OnSignal(int signum) {}

	private:
		static void _cbSignal(uv_signal_t *signal, int signum);
	};

	// -----------------------------
	// class CpuInfo
	// -----------------------------
	class CpuInfo
	{
	public:
		CpuInfo();
		~CpuInfo();
		int getCpuCount();

	private:
		uv_cpu_info_t*	_info;
		int				_count;
	};

	
	}
} // namespace mm::Loop

#endif // mmloop.h
