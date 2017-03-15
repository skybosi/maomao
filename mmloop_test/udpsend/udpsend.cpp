#include "udpsend.h"
#include <stdio.h>
#include <iostream>


udpsend::udpsend(const char* ip,int port):_destIp(ip),_destPort(port)
{
	
}

udpsend::~udpsend()
{

}

int udpsend::NativeSend4(const char *buf, size_t length)
{
	return send(buf,length,_destIp,_destPort);
}

void udpsend::OnSent(mmerrno status)
{
	if (status != mmerrno::mmSuccess) {
		fprintf(stderr, "Send error %s\n",Handle::errCode(status));
		FileHandle* file = static_cast<FileHandle *>(this->data);
		file->close();
		return;
	}
	std::cout << "send success" <<std::endl;
}

void udpsend::OnReceived(ssize_t nread,const char *buf, const struct sockaddr *addr, unsigned flags)
{
	sockaddr_in* psin = (sockaddr_in*)addr;

	printf("Recv from ip:%s,port:%d\n",inet_ntoa(psin->sin_addr),ntohs(psin->sin_port));

	printf("recv data:%s len = %d\n", buf,nread);
}


FileHandle::FileHandle(Loop& loop,udpsend* udp,size_t dataSize,int intervalTime,int startParket)
	:File(loop)
	,_udp(udp)
	,_dataSize(dataSize)
	,_intervalTime(intervalTime)
	,_offset(startParket)
{
	_timer.init(loop);
	_timer.data = this;
	_udp->data = this;
}

FileHandle::~FileHandle()
{

}

int FileHandle::FileRead()
{
	return this->read(_dataSize,_offset);
}

void FileHandle::OnWrite(int result)
{
	printf("OnWrite result = %d\n",result);
}

void FileHandle::OnOpen(int result)
{
	printf("open end! result = %d\n",result);
	_timer.start(1000,_intervalTime);
}

void FileHandle::OnClose(int result)
{
	printf("OnClose!\n");
}


void FileHandle::OnRead(char* data,int len)
{
	printf("OnRead data = %s,len = %d\n",data,len);
	_offset += len;
	_udp->NativeSend4(data,len);
}

void selfTimer2::OnTimer()
{
		FileHandle* file = static_cast<FileHandle *>(this->data);
		file->FileRead();

//		FileOperate* file = static_cast<FileOperate *>(this->data);
//		file->read();
}




FileOperate::FileOperate(Loop& loop,udpsend* udp,size_t dataSize,int intervalTime)
:_udp(udp)
,_dataSize(dataSize)
,_intervalTime(intervalTime)
,_fp(NULL)
{
	_timer.init(loop);
	_timer.data = this;
	_udp->data = this;
	_buf = (char*)malloc(_dataSize);
}

FileOperate::~FileOperate()
{
	free(_buf);
}

int FileOperate::open(const char* filename)
{
	_fp = fopen(filename,"rb");
	if (_fp != NULL)
	{
		_timer.start(0,_intervalTime);
		return 0;
	}
	return -1;
}

int FileOperate::read()
{
	memset(_buf,0,_dataSize);
	int ret = fread(_buf,1,_dataSize-1,_fp);
	if (ret > 0)
	{
		return _udp->NativeSend4(_buf,ret);
	}else
	{
		close();
	}
}

void FileOperate::close()
{
	fclose(_fp);
}