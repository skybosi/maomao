#include "mmloop_MT.h"

namespace mm {
	namespace uvbase {

		ThreadPool::ThreadPool(Loop& loop)
			:_loop(loop),
			_data(NULL)
		{
		}

		int ThreadPool::work(void* data)
		{
			uv_work_t *req = new uv_work_t;
			this->_data = data;
			req->data = static_cast<void *>(this);
			return uv_queue_work(_loop.context_ptr(), req, _cbWork, _cbAfterWrok);
		}

		void ThreadPool::_cbWork(uv_work_t *req)
		{
			ThreadPool *h = static_cast<ThreadPool *>(req->data);
			if (NULL != h)
				h->doWork();
		}

		void ThreadPool::_cbAfterWrok(uv_work_t *req, int status)
		{
			ThreadPool *h = static_cast<ThreadPool *>(req->data);
			if (NULL != h)
				h->OnAfterWork(status);
			free(req);
			h->_data = NULL;
		}

	}
} // namespace mm::uvbase