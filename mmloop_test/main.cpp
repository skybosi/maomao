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
extern int filesTest();
extern int timerTest();

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
	while (argc > 1) {
		str = argv[i++];
		std::cout << "---------------" << str << "---------------" << std::endl;
		switch (hash_(str)) {			
		case "async"_hash:			
			asyncTest();
			break;
		case "dns"_hash:
			dnsTest();
			break;
		case "files"_hash:
			filesTest();
			break;
		case "timer"_hash:
			timerTest();
			break;
		default:
			break;
		}
		argc--;
	}	
	return 0;
}