#include "asyncHandle.h"
#include "workthread.h"

int count = 0;

static BATON_VECTOR _vBatons;
static BATON_ITERATOR _iter;

void Batonfactory(int count)
{
	for(int i = 0; i < count; i++)
	{
		Baton* baton = new Baton();
		
		baton->iData1 = i;
		baton->iData2 = 2;
		baton->strData = "haihu";
	//	BATON_VECTOR _vBatons;
		_vBatons.push_back(baton);
	}
	//return baton;	
}

Baton* AsynHandle::createBaton()
{
	Baton* baton = new Baton();
	baton->iData1 = count;
	baton->iData2 = 2;
	baton->strData = "haihu";
//	BATON_VECTOR _vBatons;
//	_vBatons.push_back(baton);
	count++;
	return baton;
}

void AsynHandle::do_async_thread_pool()
{
	while(count<50)
	{
		//std::cout<<times<<std::endl;

		WorkThread* workthread = new WorkThread();

		workthread->baton = createBaton();
		workthread->work_pool.data = workthread;

		uv_queue_work(uv_default_loop(), &workthread->work_pool, async_thread_pool_callback, async_after_thread_pool_callback);
		//cout<<"Send Baton to the thread!"<<"iData1 = "<<((workthread->baton)->iData1)<<endl;
	}
	cout<<"do_async_thread_pool send already~"<<endl;
}

void AsynHandle::do_async_thread_pool_while1()
{
	cout<<"AsynHandle::do_async_thread_pool_while1() "<<_vBatons.size()<<endl;
	while(1)
	{
		if(!_vBatons.empty())
		{
			WorkThread* workthread = new WorkThread();

			_iter = _vBatons.begin();
			if(*_iter)
			{
				Baton baton = **_iter;
				_vBatons.erase(_iter);
				//*iter = NULL;
				workthread->baton = &baton;
			//workthread->baton = createBaton();
				workthread->work_pool.data = workthread;
			}
			uv_queue_work(uv_default_loop(), &workthread->work_pool, async_thread_pool_callback, async_after_thread_pool_callback);
		}
		//cout<<"Send Baton to the thread!"<<"iData1 = "<<((workthread->baton)->iData1)<<endl;
		Sleep(3);
	}
	cout<<"do_async_thread_pool send already~"<<endl;
}


float fib(int numb)
{ 
	if(numb<=2) 
	{
		return 1; 
	}
	else 
	{
		return fib(numb-1)+fib(numb-2); 
	}
}

void AsynHandle::async_thread_pool_callback(uv_work_t *handle)
{
	//cout<<"AsynHandle::asyn_thread_callback Begin~"<<endl;

	//float ret = fib(30);
	//	Baton* baton = static_cast<Baton*>(handle->data);
	WorkThread *thread_ptr = (WorkThread*)handle->data;
	Baton* baton = thread_ptr->baton;
	if(0 == baton->iData1)
	{
		float ret = fib(30);
	}

	//	uv_close((uv_handle_t*) &handle, uv_close_func);

	cout<<"AsynHandle::asyn_thread_callback,the data baton->iData1 = "<<baton->iData1<<endl;	
}

void AsynHandle::async_after_thread_pool_callback(uv_work_t *handle, int status)
{
	WorkThread *thread_ptr = (WorkThread*)handle->data;
	if(NULL != thread_ptr)
	{
		delete thread_ptr;
		thread_ptr = NULL;
	}
}

void AsynHandle::do_async_thread()
{
	//uv_async_t* async = ((uv_async_t*)arg);
	while(count<5)
	{
			WorkThread* workthread = new WorkThread();

			workthread->baton = createBaton();
			uv_async_init(uv_default_loop(), &(workthread->main_async), asyn_thread_callback);
	
		//create thread
			uv_thread_create(&workthread->worker_thread, async_thread_work,workthread);
			
		//Baton* baton = static_cast<Baton*>(async->data);
		
		//uv_async_send(async);
			//Sleep(5000);
	}
	cout<<"async_thread_work send already~"<<endl;
}


void AsynHandle::async_thread_work(void* arg)
{		
	WorkThread *thread_ptr = (WorkThread *) arg;
	
		//job_ptr->fibo_res = Job::fibo(job_ptr->fibo_num);
		
	thread_ptr->main_async.data = thread_ptr;

	uv_async_send(&(thread_ptr->main_async));
	cout<<"Send Baton to the thread!"<<"iData1 = "<<((thread_ptr->baton)->iData1)<<endl;
//	sendBaton(&thread_ptr->main_async);
	//	uv_async_send(&thread_ptr->main_async);
	
}
void AsynHandle::sendBaton(uv_async_t* async)
{
	//std::vector<Baton*>::iterator iter;
	if(!_vBatons.empty())
	{
		_iter = _vBatons.begin();
		if(*_iter)
		{
			Baton baton = **_iter;
			_vBatons.erase(_iter);
			//*iter = NULL;
			async->data = (void*) (&baton);
			uv_async_send(async);
			cout<<"Send Baton to the thread!"<<"iData1 = "<<((Baton*)(async->data))->iData1<<endl;
		}
	}
}


void AsynHandle::asyn_thread_callback(uv_async_t* handle, int status)
{
	cout<<"AsynHandle::asyn_thread_callback Begin~"<<endl;
	
	float ret = fib(40);
//	Baton* baton = static_cast<Baton*>(handle->data);
	WorkThread *thread_ptr = (WorkThread*)handle->data;
	Baton* baton = thread_ptr->baton;
	
//	uv_close((uv_handle_t*) &handle, uv_close_func);

	cout<<"AsynHandle::asyn_thread_callback,the data baton->iData1 = "<<baton->iData1<<endl;
}

void AsynHandle::uv_close_func(uv_handle_t* handle)
{

}



