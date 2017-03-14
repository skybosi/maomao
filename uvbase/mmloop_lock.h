#pragma once
#ifndef __MMLOOP_LOCK_H__
#define __MMLOOP_LOCK_H__

#include "mmloop.h"

namespace mm {
	namespace uvbase {
class MM_LOOP_API Mutex;
class MM_LOOP_API Condition;
		// -----------------------------
		// class Mutex
		// -----------------------------
		class Mutex
		{
			friend class Condition;

		public:
			explicit Mutex();
			~Mutex();

			void lock() const;

			void unlock() const;

			int tryLock() const;

		private:
			uv_mutex_t _mutex;
			Mutex(const Mutex &);
			Mutex & operator=(const Mutex &);

		public:

			class Guard
			{
			public:
				explicit Guard(const Mutex& mutex) : _mutex(mutex) { _mutex.lock(); }
				~Guard() { _mutex.unlock(); }

			private:
				const Mutex& _mutex;
			};

		};

		// -----------------------------
		// class Condition
		// -----------------------------
		class Condition
		{
		public:
			explicit Condition();
			~Condition();

			//Unblock at least one of the threads that are blocked on this condition
			void signal();

			//Unblock all threads currently blocked on this condition
			void broadcast();

			//Block on this condition variable, mutex needs to be locked
			void wait(Mutex *mutex);

			//Block on this condition variable for the given amount of time, mutex needs to be locked
			int timedwait(Mutex *mutex, uint64_t timeout);

		private:
			uv_cond_t _cond;

		};

	}
} // namespace mm::uvbase

#endif // mmloop_lock.h
