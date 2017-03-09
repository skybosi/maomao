#include "biter.h"

namespace mm {
	namespace Utils {

		biter::biter() :lens(1)
		{
			bits = (char*)malloc(lens * sizeof(char));
			memset(bits, 0, sizeof(char));
		}

		biter::biter(int len, char* data) : lens(len), bits(data)
		{
			bits = (char*)malloc(lens * sizeof(char));
			memcpy(bits, data, lens);
#ifndef DEBUG
			if (!bsIsBigEndian) INVERT(bits, lens);
#endif
		}

		biter::biter(int data) :lens(SIZE(data))
		{
			bits = (char*)malloc(sizeof(int));
			memcpy(bits, &data, sizeof(int));
#ifndef DEBUG
			if (!bsIsBigEndian) INVERT(bits, lens);
#endif
		}

		biter::biter(long data) :lens(SIZE(data))
		{
			bits = (char*)malloc(sizeof(long));
			memcpy(bits, &data, sizeof(long));
#ifndef DEBUG
			if (!bsIsBigEndian) INVERT(bits, lens);
#endif
		}

		biter::~biter()
		{
			if (bits) {
				free(bits);
				lens = 0;
				bits = NULL;
			}
		}

		std::ostream & operator <<(std::ostream &os, const biter& rhs)
		{
			/*
			do
			{
				char* base = rhs.bits;
				char* tail = rhs.bits + rhs.lens - 1;
				do {
					SWAP(*base, *tail);
					base++;
					tail--;
				} while (base < tail);
			}while (0);
			*/
			int cur = 0;
			char* base = rhs.bits;
			char  str[9] = { 0 };
			while (cur++ < rhs.lens)
			{
				/*
				char bits;
				char bitstr[9] = { 0 };
				bits = *base++;
				bitstr[7] = (bits & 0x1) ? '1' : '0';
				bitstr[6] = (bits & 0x2) ? '1' : '0';
				bitstr[5] = (bits & 0x4) ? '1' : '0';
				bitstr[4] = (bits & 0x8) ? '1' : '0';
				bitstr[3] = (bits & 0x10) ? '1' : '0';
				bitstr[2] = (bits & 0x20) ? '1' : '0';
				bitstr[1] = (bits & 0x40) ? '1' : '0';
				bitstr[0] = (bits & 0x80) ? '1' : '0';
				bitstr[8] = '\0';
				*/
				BITS(str, *base);
				base++;
				os << str << " ";
			}
			return os << std::endl;
		}

		bool biter::operator==(const biter& rhs)
		{
			if (lens == rhs.lens) {
				char* base = bits;
				char* rbase = rhs.bits;
				int cur = 0;
				while (*base++ == *rbase++ && rhs.lens != cur++);
				return (cur - 1 == lens);
			}
			return false;
		}

		int  biter::get(int index, int len)
		{			
			if (len > 7) {
				int bytes = len / 8;
				int shif = len % 8;
				int cur = 0;
				int rt = 0;
				char* base = bits;
				int flag = FLAG(8-shif, shif);
				while (cur++ < bytes)
				{
					rt <<= 8;
					rt |= (0xFF & *base);
					base++;
				}
				(rt <<= shif) |= (flag  & *base);
				return rt;
			}
			else {
				return(FLAG(index, len) & *bits);
			}
		}

		int  biter::gets(int base, ...)
		{
			va_list ap;
			int rt = 0;
			va_start(ap, base);
			do {
				printf("%d, ", base);
				rt |= getbit(base);
				rt <<= 1;
				base = va_arg(ap, int);
			} while (NULL != base);
			va_end(ap);
			return rt;
		}

		void biter::sets(int bit,int base, ...)
		{
			va_list ap;
			va_start(ap, base);
			do {
				printf("%d, ", base);
				setbit(base, bit);
				base = va_arg(ap, int);
			} while (NULL != base);
			va_end(ap);
		}

		inline int  biter::getbit(int index)
		{			
			char* base = bits;
			(index < 0) ? (index += lens * 8) : (index);
			return ( *( base + (index / 8) ) & ( 1 << ( 7 - (index % 8) ) ) ) ? 1 : 0 ;
			//return GETBIT(*(base + (index / 8)), 7 - (index % 8)) ? 1 : 0;  //error will modified the value,is danger
		}

		inline void biter::setbit(int index, char bit)
		{
			char* base = bits;
			(index < 0) ? (index += lens * 8) : (index);
			return (bit) ? ( SETBIT( *(base + index / 8), index % 8 ) ) : ( CLRBIT( *( base + index / 8 ), index % 8 ) );
		}

	}
}//namespace mm::Utils