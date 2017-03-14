#include "mmloop_files.h"
#include "mmloop_utils.h"
//#include <fcntl.h>


using namespace mm::uvbase;

class MyFileEvent : public FileEvent
{
public:
	MyFileEvent() {}
	~MyFileEvent() {}

	virtual void OnFileEvent(const char *filename, _Event events, mmerrno status)
	{
		if (status != Handle::mmSuccess)
		{
			printf("File detect errors!\n");
			return;
		}

		if(events == fseChanged)
			printf("the file %s has changed!\n",filename);
	}
};


class MyFile : public File
{
public:
	MyFile(Loop& loop):File(loop){}
	~MyFile() {}
	virtual void OnWrite(int result)
	{
		printf("OnWrite result = %d\n",result);
		this->close();
	}

	virtual void OnOpen(int result)
	{
		printf("open end! result = %d\n",result);
		
		char* buf = "1234";
		this->write(buf,4,-1);
//		this->read(2,-1);
	}

	virtual void OnClose(int result)
	{
		printf("OnClose!\n");
		this->clean();
	}

	virtual void OnRead(char* data,int len)
	{
		printf("OnRead data = %s,len = %d\n",data,len);
		this->close();
	}
};

class selfTimer : public Timer
{
public:
	selfTimer() {}
	~selfTimer() {}
	virtual void OnTimer()
	{
		printf("selfTimer test\n");
		MyFile* file = static_cast<MyFile *>(this->data);
		file->open("file.txt", File::CREAT_RDWR, File::RD_WR);
		close();
	}
};


int filesTest()
{
	Loop loop(true);
	MyFile* file = new MyFile(loop);


	MyFileEvent fileevent;
	fileevent.init(loop);
	fileevent.start("file.txt");

	selfTimer timer;
	timer.init(loop);
	timer.start(2000,2000);
	timer.data = file;

	loop.run(Loop::Default);
	delete file;
	return 0;
}
