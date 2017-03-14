#include <stdio.h>
#include "transmitter\transmitter.h"
using namespace mm::Transmitter;
extern int client(int argc, char* argv[]);
extern int server(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	printf("--------------- maomao-Test ---------------\n");
	if (argc >= 2) {
		char* str = argv[1];
		if (!strcmp(str, "server")) {
			printf("--------------- maomao-Server ---------------\n");
			server(argc, argv);
		}
		else if (!strcmp(str, "client")) {
			printf("--------------- maomao-Client ---------------\n");
			client(argc, argv);
		}
		else {
			printf("--------------- maomao-Unkonw ---------------\n");
		}
	}
	else {
		printf("Usage: server/client\n");
	}
	return 0;
}