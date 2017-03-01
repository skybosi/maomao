#include "getopt.h"
#include "udpsend.h"
#include <stdio.h>
#include <iostream>


void usage() {

	std::cout << "Usage: udpsend [option] [arg]\n\n"
		<< "Options:\n"
		<< "  -f <file name>					    The file to send\n"
		<< "  -b <bit rate>							Transmitted bit rate\n"
		<< "  -s <data size>						Data size for each transmission\n"
		<< "  -B <start parket>						Start sending packets\n"
		<< "  -d <ip:port>							The server ip and port\n"
		<< "  -h									display this screen\n"
		<< std::endl;
}




int main(int argc,char* argv[])
{
	if (argc < 5)
	{
		usage();
		return -1;
	}
	std::string filename,endpoint;
	int bit,datasize,startParket;
	int ch = 0;
	while((ch = getopt(argc,argv,"f:b:s:B:d:h:")) != EOF)
	{
		switch(ch)
		{
		case 'f':
			filename = optarg;
			break;
		case 'b':
			bit = atoi(optarg);
			break;
		case 's':
			datasize = atoi(optarg);
			break;
		case 'B':
			startParket = atoi(optarg);
			break;
		case 'd':
			endpoint = optarg;
			break;
		case 'h':
			usage();
			return 0;
		default:
			break;
		}
	}
	printf("filename=%s,bit=%d,datasize=%d,startParket=%d,endpoint=%s\n",filename.c_str(),bit,datasize,startParket,endpoint.c_str());

	std::string ip = endpoint.substr(0,endpoint.find(":"));
	std::string strport = endpoint.substr(endpoint.find(":")+1);
	int port = atoi(strport.c_str());
	int intervalTime = 1000/((bit*1000)/(datasize*8));



	Loop loop(true);

	

	udpsend udp(ip.c_str(),port);
	udp.init(loop);
	udp.bind4("192.168.81.28",9979,UDP::Reuseaddr);

	FileHandle* file = new FileHandle(loop,&udp,datasize,intervalTime,startParket);
	file->open(filename.c_str(),File::FileFlags::RDONLY, File::FileMode::READ);

//	FileOperate* file = new FileOperate(loop,&udp,datasize+1,intervalTime);
//	file->open(filename.c_str());







	loop.run(Loop::Default);
	return 0;
}