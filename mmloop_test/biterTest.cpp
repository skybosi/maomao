#include "biter.h"
#ifdef _WIN32
#include<winsock2.h>
#endif
using namespace mm::Utils;

int biterTest()
{
	int tmp = (1 << ((7 / 8 + 1) * 8)) - 1;
	int tmp1 = (1 << ((9 / 8 + 1) * 8)) - 1;
	int tmp2 = (1 << ((23 / 8 + 1) * 8)) - 1;
	printf("IS BIG ENDIAN: %d\n",bsIsBigEndian);
	std::cout << "\n***** Test constructor ***** " << std::endl;
	biter bit;	
	biter bit2(112350);	
	char c[4] = "fdj";
	biter bit3(c, strlen(c));
	biter bit4(10);
	biter bit5("fdj", strlen(c));
	std::cout << "\n***** Test op<< ***** " << std::endl;
	std::cout << "bit: null    : " << bit;
	std::cout << "bit2(112350) : " << bit2;
	std::cout << "bit3(fdj)    : " << bit3;
	std::cout << "bit4(10)     : " << bit4;
	std::cout << "bit5(fdj)    : " << bit5;
	std::cout << "bit(4)       : " << biter(4);
#ifdef  DEBUG  //test host and network endian
	std::cout << "\n***** Test hto*<< ***** " << std::endl;
	std::cout << "bit2(112350) : " << bit2;
	std::cout << "host: 112350 : " << 112350 << std::endl;
	std::cout << "hton: 112350 : " << htonl(112350) << std::endl;
	int newb = htonl(112350);
	biter cbit2(newb);
	std::cout << "bit2(112350) : " << cbit2;
#endif //  DEBUG
	std::cout << "\n***** Test op== ***** " << std::endl;
	printf("bit2 == bit4 : %d\n",(bit2 == bit4));
	printf("bit3 == bit5 : %d\n", (bit3 == bit5));
	std::cout << "\n***** Test get ***** " << std::endl;
	printf("bit2[0-5]    : %d\n", bit2.get(0, 5));
	printf("bit2[5-24]   : %d\n", bit2.get(5, 24));
	printf("bit2[0-24]   : %d\n", bit2.get(0, 24));
	std::cout << "\n***** Test get more ***** " << std::endl;
	printf("get bit2[-1,-2,-3] : %d\n", bit2.gets(-1, -2, -3, NULL));
	printf("set bit2[-1,-2,-3]");
	bit2.sets(1, -1, -2, -3, NULL);
	printf("get bit2[-1,-2,-3] : %d\n", bit2.gets(-1, -2, -3, NULL));
	std::cout << "\n***** Test getbit ***** " << std::endl;
	printf("bit2[ 7]: %d bit2[ 9]: %d bit2[13]: %d\n", bit2.getbit(7), bit2.getbit(9),bit2.getbit(13));
	printf("bit2[-5]: %d bit2[-6]: %d bit2[-7]: %d\n", bit2.getbit(-5), bit2.getbit(-6), bit2.getbit(-7));
	std::cout << "\n***** Test setbit ***** " << std::endl;
	std::cout << "Before set: bit2(112350) : " << bit2;
	bit2.setbit(-5, 0), bit2.setbit(-6, 1), bit2.setbit(-7, 0);
	printf("After  set: bit2[-5]: %d bit2[-6]: %d bit2[-7]: %d\n", bit2.getbit(-5), bit2.getbit(-6), bit2.getbit(-7));
	std::cout << "After  set: bit2(112350) : " << bit2;
	bit2.setbit(7, 1), bit2.setbit(9, 1), bit2.setbit(13, 0);
	printf("After  set: bit2[ 7]: %d bit2[ 9]: %d bit2[13]: %d\n", bit2.getbit(7), bit2.getbit(9), bit2.getbit(13));
	std::cout << "After  set: bit2(112350) : " << bit2;
	std::cout << "\n***** Test get more ***** " << std::endl;
	std::cout << "bit3 checksum: " << bit3.checksum() << std::endl;
	return 0;
}