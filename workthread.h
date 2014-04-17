#ifndef WORKTHREAD_H
#define WORKTHREAD_H


#include "asyncHandle.h"


class WorkThread
{
public:
	WorkThread(){}
	virtual ~WorkThread(){}

public:
	uv_thread_t worker_thread;
	uv_async_t main_async;

	uv_work_t work_pool;
	uv_loop_t* loop;

	Baton* baton;
};

#endif
