#pragma once
/*
	biter:
	bit stream direction alway is from Left to Right like:
	0 - 7, 8 - 15, 16 - 23 ...
	even thought is big or little Endian
*/

#ifndef _BITER_H_
#define _BITER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

namespace mm {
	namespace Utils {
//#define DEBUG
#define SIZE(V) (sizeof(V)/sizeof(char))
#define BITS(bitstr,bits)  do                        \
    {                                                \
        bitstr[7] = ((bits) & 0x1) ? '1' : '0';      \
        bitstr[6] = ((bits) & 0x2) ? '1' : '0';      \
        bitstr[5] = ((bits) & 0x4) ? '1' : '0';      \
        bitstr[4] = ((bits) & 0x8) ? '1' : '0';      \
        bitstr[3] = ((bits) & 0x10) ? '1' : '0';     \
        bitstr[2] = ((bits) & 0x20) ? '1' : '0';     \
        bitstr[1] = ((bits) & 0x40) ? '1' : '0';     \
        bitstr[0] = ((bits) & 0x80) ? '1' : '0';     \
        bitstr[8] = '\0';                            \
    }while(0);
#define bsIsBigEndian ((((const int*)"\0\x1\x2\x3\x4\x5\x6\x7")[0] & 255) != 0)
#define FLAG(_S,_L) ((0xFF >> (8 -_L) << (_S)))
#define SWAP(_A,_B)  {_A ^= _B; _B ^= _A; _A ^= _B;}
//inverted sequence  _D: data pointer  _L: length
#define INVERT(_D,_L) do                             \
    {                                                \
        char* base = _D;                             \
        char* tail = _D + _L - 1;                    \
        do {                                         \
            SWAP(*base, *tail);                      \
            base++;                                  \
            tail--;                                  \
        } while (base < tail);                       \
    }while(0);
#define LE2NE INVERT
#define NE2LE INVERT
#define HTONS(_S) (bsIsBigEndian)?(_S):(LE2NE(_S,2)) //htons
#define HTONL(_L) (bsIsBigEndian)?(_L):(LE2NE(_L,4)) //htonl
#define NTOHS(_S) (bsIsBigEndian)?(_S):(NE2LE(_S,2)) //ntohs
#define NTOHL(_L) (bsIsBigEndian)?(_L):(NE2LE(_L,4)) //ntotl
#define ODD   false
#define EVEN  true
		// bit opeartor
		class biter
		{
		public:
			biter();
			biter(char* data, int len);
			biter(int data);
			biter(long data);
			~biter();
		public:
			friend std::ostream & operator <<(std::ostream &os, const biter& bit);
			bool   operator ==(const biter& rhs);
		public:
			int    get(int index, int len);
			int    gets(int start, ...);
			void   sets(int bit,int start, ...);
			inline int  getbit(int index);
			inline void setbit(int index, char bit);
			inline bool parity() { return ( ( (*bits + lens) & 0x1 ) ? (ODD) : (EVEN) ); }
			static inline bool endian() { return bsIsBigEndian; }
			unsigned short checksum();
		private:
			//7 is control the direction from left to right
//#define SETBIT(_V,_I)  ((_V) |= (1 << (7-_I)))  //set the _V at _I position is 1
			inline void SETBIT(char& val, int pos) { (val) |= (1 << (7-pos)); }
//#define CLRBIT(_V,_I)  ((_V) &= ~(1 << (7-_I))) //set the _V at _I position is 0,just clear this bit to 0
			inline void CLRBIT(char& val, int pos) { (val) &= ~(1 << (7-pos));}
//#define GETBIT(_V,_I)  ((_V) &= (1 << (7-_I)))  //error will modified the value,is danger
			inline void GETBIT(char& val, int pos) { (val) &= (1 << (7-pos)); }
		private:
			int   lens;  //byte number
			char* bits;  //data bits
		};
	}
}//namspace mm::Utils
#endif // !_BITER_H_
