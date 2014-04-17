#include "asyncHandle.h"
//#include "async.h"

int main() 
{
	int i = 3000;
	Batonfactory(i);
	AsynHandle* asynHandle = new AsynHandle();
	asynHandle->do_async_thread_pool_while1();
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}