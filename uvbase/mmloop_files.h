#pragma once
#ifndef _MMLOOP_FILES_H_
#define _MMLOOP_FILES_H_

#include <string.h>
#include "mmloop.h"
#include "mmloop_net.h"
#include <fcntl.h>


namespace mm {
	namespace uvbase {
class MM_LOOP_API FileEvent;
class MM_LOOP_API File;
class MM_LOOP_API Pipe;

#ifndef FLAG
#  define FLAG(_F)  (1<<_F)
#endif // FLAG

#ifdef OS_MSWIN

# ifndef S_IRUSR
#  define S_IRUSR _S_IREAD
# endif

# ifndef S_IWUSR
#  define S_IWUSR _S_IWRITE
# endif
#endif


// -----------------------------
// class FileEvent
// -----------------------------
// dup of uvpp_fs_event
class FileEvent : public Handle
{
public:
	typedef enum _Event {
		fseRenamed = UV_RENAME, // file event when a file or dir has been renamed
		fseChanged = UV_CHANGE  // file event when a file has been modified
	} Event;

	// flags to be passed to start() to watch a file
	typedef enum _StartFlags {
		fsfNone = 0, // 0 means none flag is turned on

		// fefWatchEntry  - instead of watching a directory and all its children file by default,
		//                  this flag specify to only watch the directly entry itself
		fsfWatchEntry = FLAG(0), // UV_FS_EVENT_WATCH_ENTRY,

		// fsfActiveStat  - for some file systems such as NFS mounts to remote storage, it is recommended
		//                  to actively call stat() on a regular interval for the file event
		fsfActiveStat = FLAG(1), // UV_FS_EVENT_STAT,

		// fsfRecursive   - to watching the sub-directories
		fsfRecursive = FLAG(2), // UV_FS_EVENT_RECURSIVE
	} StartFlags;

public:
	FileEvent();

	int init(Loop &loop);

	//@param flags - flag combination of StartFlags
	int start(const char *path, uint flags = fsfNone);
	int stop();
	int getpath(char *buffer, size_t *size);

protected:
	//@param events  - combination of flags of Event
	virtual void OnFileEvent(const char *filename, uint events, mmerrno status) {}

private:
	static void _cbFSevent(uv_fs_event_t *handle, const char *filename, int events, int status);
};

// -----------------------------
// class File
// -----------------------------
class File
{
public:
	enum FileFlags {
		RDONLY = O_RDONLY,
		WRONLY = O_WRONLY,
		RDWR = O_RDWR,
		CREAT = O_CREAT,
		APPEND = O_APPEND,
		CREAT_RDWR = O_CREAT | O_RDWR,
		CREAT_WRONLY = O_CREAT | O_WRONLY
	};

	enum FileMode {
		RD_WR = S_IRUSR | S_IWUSR,
		READ = S_IRUSR,
		WRITE = S_IWUSR
	};

public:
	File(Loop& loop);
	File();

	//@param flags - flag combination of FileFlags
	//@param mode  - flag combination of FileMode
	int open(const char* filename, uint flags, uint mode);
	int read(size_t len, int64_t offset);
	int write(const char* data, size_t len, int64_t offset);

	//@param mode  - flag combination of FileMode
	int mkdir(const char* dirname, uint mode);
	int close();
	void clean();
	char* _buf;


protected:
	virtual void OnOpen(int result) {}
	virtual void OnWrite(int result) {}
	virtual void OnRead(char* data, int len) {}
	virtual void OnClose(int result) {}
	virtual void OnMkdir(int result) {}

private:
	static void _cbFileOpen(uv_fs_t* req);
	static void _cbFileClose(uv_fs_t* req);
	static void _cbFileWrite(uv_fs_t* req);
	static void _cbFileRead(uv_fs_t* req);
	static void _cbMkdir(uv_fs_t* req);
	void setfb(int fb);

private:
	Loop& _loop;
	int _fb;
	bool _isAlloc;
	size_t _len;
};

// -----------------------------
// class Pipe
// -----------------------------
class Pipe : public Stream
{
public:
	Pipe();

	int  init(Loop &loop, int ipc = 0);
	int  open(uv_file file);
	int  bind(const char *name);
	void connect(const char *name);
	int  getsockname(char *buffer, size_t *size);
	int  getpeername(char *buffer, size_t *size);
	void pending_instances(int count);
	int  pending_count();

protected:
	//TODO: why wiped uv_connect_t here??
	virtual void OnConnected(mmerrno status) {}

private:
	static void _cbConnected(uv_connect_t *req, int status);

};

	}
} // namespace mm::uvbase

#endif // mmloop_files.h

