#include <string>
#include <iostream>
#include "mmloop.h"
/*
#include "async.cpp"
#include "dns.cpp"
#include "file.cpp"
#include "timer.cpp"
*/
extern int asyncTest();
extern int dnsTest();
extern int idleTest();
extern int filesTest();
extern int timerTest();
extern int pipeClientTest();
extern int pipeServerTest();
extern int tcpClientTest();
extern int tcpServerTest();
extern int udpClientTest();
extern int udpServerTest();
extern int udpsendTest(int argc, char* argv[]);

using namespace mm::Loop;

//for switch case use string
//http://blog.csdn.net/canguanxihu/article/details/45640999
typedef std::uint64_t hash_t;
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(const char* str)
{
	hash_t ret{ basis };
	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}
	return ret;
}

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return ((*str) ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : (last_value));
}

constexpr unsigned long long operator"" _hash(char const* p, size_t)
{
	return hash_compile_time(p);
}



int main(int argc,char* argv[])
{
	printf("--------------- mmloop-Test ---------------\n");
	char* str = "first";
	int i = 1;
	//when LONELY is true,it can be test with othre LONELY true Unit test
	//LONELY is false,just run it alone
	bool LONELY = true;
	while (LONELY && argc > 1) {
		str = argv[i++];
		std::cout << "---------------" << str << "---------------" << std::endl;
		switch (hash_(str)) {			
		case "async"_hash:			
			asyncTest();
			break;
		case "dns"_hash:
			dnsTest();
			break;
		case "idle"_hash:
			idleTest();
			break;
		case "files"_hash:
			filesTest();
			break;
		case "timer"_hash:
			timerTest();
			break;
		case "udpC"_hash:
			LONELY = false;
			udpClientTest();
			break;
		case "udpS"_hash:
			LONELY = false;
			udpServerTest();
			break;
		case "tcpC"_hash:
			LONELY = false;
			tcpClientTest();
			break;
		case "tcpS"_hash:
			LONELY = false;
			tcpServerTest();
			break;
		case "pipeC"_hash:
			LONELY = false;
			pipeClientTest();
			break;
		case "pipeS"_hash:
			LONELY = false;
			pipeServerTest();
			break;
		case "udpSend"_hash:
			LONELY = false;
			udpsendTest(argc,argv);
			break;
		default:
			std::cout << str << ": invalid option! You can chose: async, dns, idle, files, timer, pipeC, pipeS, tcpC, tcpS, udpC, udpS, udpsend.  \nNOTE: some C/S mode must match" << std::endl;
			break;
		}
		argc--;
	}	
	return 0;
}