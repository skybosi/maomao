#pragma once
#ifndef _MMLOOP_UTILS_H_
#define _MMLOOP_UTILS_H_
#include <stdlib.h>
#include <iostream>
#include "mmloop.h"


namespace mm {
	namespace uvbase {
		//uv_buf_t
		class buffer
		{
		public:
			buffer();
			buffer(size_t size);
			~buffer();
			static int allocator(uv_malloc_func malloc_func,uv_realloc_func realloc_func,uv_calloc_func calloc_func,uv_free_func free_func);
			void * operator new(size_t size) throw(std::bad_alloc);
			void operator delete(void* ptr);
		private:
			uv_buf_t _buffer;
		};

		class rusage
		{
		public:
			rusage();
			~rusage();
			void * operator new(size_t size) throw(std::bad_alloc);
			void operator delete(void* ptr);
		private:
			uv_rusage_t* _rusage;
		};

		// -----------------------------
		// class Timer
		// -----------------------------
		class Timer : public Handle
		{
		public:
			Timer();
			int init(Loop &loop);
			int start(uint64_t timeout, uint64_t repeat);
			int stop();
			int again();
			void set_repeat(uint64_t repeat);
			uint64_t get_repeat();

		protected:
			virtual void OnTimer() {}

		private:
			static void _cbOnTimer(uv_timer_t *timer);
		};


		// -----------------------------
		// class CpuInfo
		// -----------------------------
		class cpuInfo
		{
		public:
			cpuInfo();
			~cpuInfo();
			int cpu_count();

		private:
			uv_cpu_info_t*	_info;
			int				_count;
		};


	}
}//namespace mm::uvbase



#endif // !_MMLOOP_UTILS_H_
