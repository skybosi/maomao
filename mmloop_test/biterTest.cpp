#include "biter.h"
using namespace mm::Utils;

int biterTest()
{
	int tmp = (1 << ((7 / 8 + 1) * 8)) - 1;
	int tmp1 = (1 << ((9 / 8 + 1) * 8)) - 1;
	int tmp2 = (1 << ((23 / 8 + 1) * 8)) - 1;
	printf("%d\n",bsIsBigEndian);
	std::cout << " ===== Test constructor ===== " << std::endl;
	biter bit;	
	biter bit2(112350);	
	char c[4] = "fdj";
	biter bit3(strlen(c), c);	
	biter bit4(10);
	biter bit5(strlen(c),"fdj");
	std::cout << " ===== Test op<< ===== " << std::endl;
	std::cout << bit;
	std::cout << bit2;
	std::cout << bit3;
	std::cout << bit4;
	std::cout << bit5;
	std::cout << biter(4);
	std::cout << " ===== Test op== ===== " << std::endl;
	printf("%d\n",(bit2 == bit4));
	printf("%d\n", (bit3 == bit5));
	std::cout << " ===== Test get ===== " << std::endl;
	printf("%d\n", bit2.get(0, 5));
	printf("%d\n", bit2.get(0, 24));
	std::cout << biter(bit2.get(0, 5));
	std::cout << biter(bit2.get(0, 24));
	std::cout << " ===== Test getbit ===== " << std::endl;
	printf("%d %d %d\n", bit2.getbit(7), bit2.getbit(9),bit2.getbit(13));
	std::cout << " ===== Test getbit ===== " << std::endl;
	bit2.setbit(7, 1), bit2.setbit(9, 1), bit2.setbit(13, 0);
	printf("%d %d %d\n", bit2.getbit(7), bit2.getbit(9), bit2.getbit(13));
	return 0;

}