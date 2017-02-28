#pragma once

#ifndef __MMLOOP_MT_H__
#define __MMLOOP_MT_H__
#include <stdlib.h>
#include "mmloop.h"
namespace mm {
	namespace Loop {
class ZQ_ELOOP_API ThreadPool;
	
		// ---------------------------------------
		// class ThreadPool
		// ---------------------------------------
		class ThreadPool
		{
		public:
			ThreadPool(Loop& loop);
			int work(void* data);

		protected:
			virtual void doWork() {}
			virtual void OnAfterWork(int status) {}
			void*	_data;

		private:
			static void _cbWork(uv_work_t *req);
			static void _cbAfterWrok(uv_work_t *req, int status);

		private:
			Loop& _loop;
		};

	}
} // namespace mm::Loop

#endif // mmloop_MT.h