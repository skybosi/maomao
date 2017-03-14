#include "mmloop_lock.h"

namespace mm {
	namespace uvbase {

		// -----------------------------
		// class Mutex
		// -----------------------------

		Mutex::Mutex()
		{
			uv_mutex_init(&_mutex);
		}

		Mutex::~Mutex()
		{
			uv_mutex_destroy(&_mutex);
		}

		void Mutex::lock() const
		{
			//uv_mutex_lock((LPCRITICAL_SECTION)&_mutex);
			uv_mutex_lock(const_cast<uv_mutex_t*>(&_mutex));
		}

		void Mutex::unlock() const
		{
			//	uv_mutex_unlock((LPCRITICAL_SECTION)&_mutex);
			uv_mutex_unlock(const_cast<uv_mutex_t*>(&_mutex));
		}

		//Try to lock the mutex, return True if the lock was acquired, False otherwise
		int Mutex::tryLock() const
		{
			//return uv_mutex_trylock((LPCRITICAL_SECTION)&_mutex);
			return uv_mutex_trylock(const_cast<uv_mutex_t*>(&_mutex));
		}


		// -----------------------------
		// class Condition
		// -----------------------------
		Condition::Condition()
		{
			uv_cond_init(&_cond);
		}


		Condition::~Condition()
		{
			uv_cond_destroy(&_cond);
		}

		//Unblock at least one of the threads that are blocked on this condition
		void Condition::signal()
		{
			uv_cond_signal(&_cond);
		}

		//Unblock all threads currently blocked on this condition
		void Condition::broadcast()
		{
			uv_cond_broadcast(&_cond);
		}

		//Block on this condition variable, mutex needs to be locked
		void Condition::wait(Mutex *mutex)
		{
			uv_cond_wait(&_cond, &(mutex->_mutex));
		}

		//Block on this condition variable for the given amount of time, mutex needs to be locked
		int Condition::timedwait(Mutex *mutex, uint64_t timeout)
		{
			return uv_cond_timedwait(&_cond, &(mutex->_mutex), timeout);
		}

	}
} // namespace mm::uvbase