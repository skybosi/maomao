#pragma once
/*
	biter:
	direction alway is 
	from Left to Right is
	0 - 7, 8 - 15, 16 - 23 ...
	even thought is big or little Endian
*/

#ifndef _BITER_H_
#define _BITER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

namespace mm {
	namespace Utils {

#define SIZE(V) (sizeof(V)/sizeof(char))
#define BITS(bitstr,bits)  do                    \
	{                                            \
		bitstr[7] = ((bits) & 0x1) ? '1' : '0';  \
		bitstr[6] = ((bits) & 0x2) ? '1' : '0';  \
		bitstr[5] = ((bits) & 0x4) ? '1' : '0';  \
		bitstr[4] = ((bits) & 0x8) ? '1' : '0';  \
		bitstr[3] = ((bits) & 0x10) ? '1' : '0'; \
		bitstr[2] = ((bits) & 0x20) ? '1' : '0'; \
		bitstr[1] = ((bits) & 0x40) ? '1' : '0'; \
		bitstr[0] = ((bits) & 0x80) ? '1' : '0'; \
		bitstr[8] = '\0';                        \
	}while(0);
#define bsIsBigEndian ((((const int*)"\0\x1\x2\x3\x4\x5\x6\x7")[0] & 255) != 0)
#define FLAG(_S,_L) (0xFF ^ (0xFF >> (8 -_L) << (_S)))
		
		// bit opeartor
		class biter
		{
		public:
			biter();
			biter(int len, char* data);
			biter(int data);
			biter(long data);
			~biter();
		public:
			friend std::ostream & operator <<(std::ostream &os, const biter& bit);
			bool   operator ==(const biter& rhs);
			int    get(int index, int len);
			int    getbit(int index);
			void   setbit(int index, char bit);
			static inline bool endian() { return bsIsBigEndian; }
		private:
//#define SETBIT(_V,_I)  ((_V) |= (1 << (7-_I)))  //set the _V at _I position is 1
			inline void SETBIT(char& val, int pos)
			{
				(val) |= (1 << (7-pos));  //7 is control the direction from left to right
			}
//#define CLRBIT(_V,_I)  ((_V) &= ~(1 << (7-_I))) //set the _V at _I position is 0,just clear this bit to 0
			inline void CLRBIT(char& val, int pos)
			{
				(val) &= ~(1 << (7-pos));
			}
//#define GETBIT(_V,_I)  ((_V) &= (1 << (7-_I)))  //error will modified the value,is danger
			inline void GETBIT(char& val, int pos)
			{
				(val) &= (1 << (7-pos));
			}
		private:
			int   lens;  //byte number
			char* bits;  //data bits
		};
	}
}//namspace mm::Utils
#endif // !_BITER_H_
