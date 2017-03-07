#include "mmloop_utils.h"

namespace mm {
	namespace Loop {

		// -----------------------------
		// class buffer
		// -----------------------------
		buffer::buffer()
		{
			//printf("this=%x  buff:%x\n", this, &_buffer);
			char* base = (char*)(::operator new((size_t)(1024 * sizeof(char))));
			_buffer = uv_buf_init(base, 1024);
		}

		buffer::buffer(size_t size)
		{
			//printf("this=%x  buff:%x\n", this,&_buffer);
			char* base = (char*)(::operator new((size_t)(size * sizeof(char))));
			_buffer = uv_buf_init(base, size);
		}

		void * buffer::operator new(size_t size) throw(std::bad_alloc) {
			if (size == 0)
				size = 1;
			void* p;
			while ((p = ::malloc(size)) == 0) {
				std::new_handler nh = std::get_new_handler();
				if (nh)
					nh();
				else
					throw std::bad_alloc();
			}
			printf("return=%x\n", p);
			return p;
		}

		void buffer::operator delete(void* ptr) {
			if (ptr) {
				buffer* buf = (buffer*)ptr;
				delete buf;
				//::free(ptr);
				ptr = NULL;
			}
		}

		buffer::~buffer()
		{
			if (_buffer.base != NULL)
			{
				_buffer.len = 0;
				delete (_buffer.base);
			}
		}


		int buffer::allocator(uv_malloc_func malloc_func, uv_realloc_func realloc_func, uv_calloc_func calloc_func, uv_free_func free_func)
		{
			return uv_replace_allocator(malloc, realloc, calloc, free);
		}

		// -----------------------------
		// class rusage
		// -----------------------------

		rusage::rusage()
		{
			_rusage = new uv_rusage_t;
		}

		rusage::~rusage()
		{
			if (!_rusage) {
				delete _rusage;
				_rusage = NULL;
			}
		}

		void * rusage::operator new(size_t size) throw(std::bad_alloc) {
			if (size == 0)
				size = 1;
			void* p;
			while ((p = ::malloc(size)) == 0) {
				std::new_handler nh = std::get_new_handler();
				if (nh)
					nh();
				else
					throw std::bad_alloc();
			}
			printf("return=%x\n", p);
			return p;
		}

		void rusage::operator delete(void* ptr) {
			if (ptr) {
				::free(ptr);
				ptr = NULL;
			}
		}
		// -----------------------------
		// class Timer
		// -----------------------------

		Timer::Timer()
		{
		}

		void Timer::_cbOnTimer(uv_timer_t *timer)
		{
			Timer *h = static_cast<Timer *>(timer->data);
			if (NULL != h)
				h->OnTimer();
		}

		int Timer::init(Loop &loop) {
			this->Handle::init(loop);
			uv_timer_t * timer = (uv_timer_t *)context_ptr();
			return uv_timer_init(loop.context_ptr(), timer);
		}

		int Timer::start(uint64_t timeout, uint64_t repeat) {
			uv_timer_t* timer = (uv_timer_t *)context_ptr();
			return uv_timer_start(timer, _cbOnTimer, timeout, repeat);
		}

		int Timer::stop() {
			uv_timer_t* timer = (uv_timer_t *)context_ptr();
			return uv_timer_stop(timer);
		}

		int Timer::again() {
			uv_timer_t* timer = (uv_timer_t *)context_ptr();
			return uv_timer_again(timer);
		}

		void Timer::set_repeat(uint64_t repeat) {
			uv_timer_t* timer = (uv_timer_t *)context_ptr();
			uv_timer_set_repeat(timer, repeat);
		}

		uint64_t Timer::get_repeat() {
			uv_timer_t* timer = (uv_timer_t *)context_ptr();
			return uv_timer_get_repeat(timer);
		}



		cpuInfo::cpuInfo()
		{
			uv_cpu_info(&_info, &_count);
		}
		cpuInfo::~cpuInfo()
		{
			uv_free_cpu_info(_info, _count);
		}
		int cpuInfo::cpu_count()
		{
			return _count;
		}
	}
}//namespace mm::Loop