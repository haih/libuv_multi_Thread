#ifndef ASYNCHANDLE_H
#define ASYNCHANDLE_H

#include "uv.h"
#include "stdlib.h"
#include "stdio.h"
using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include <Windows.h>
#pragma comment(lib, "IPHLPAPI.lib")  
#pragma comment(lib, "Psapi.lib")

typedef struct Baton
{
	/* data */
	int iData1;
	int iData2;
	string strData;
}Data;

typedef vector<Baton*> BATON_VECTOR ;
typedef vector<Baton*>::iterator BATON_ITERATOR;

//static BATON_VECTOR _vBatons;
//static BATON_ITERATOR _iter;
void Batonfactory(int count);

class AsynHandle {

 public:
	AsynHandle(){};
  	virtual ~AsynHandle(){};

public:
	void do_async_thread();
	void do_async_thread_pool();
	void do_async_thread_pool_while1();
	
	static void async_thread_work(void* arg);
	static void asyn_thread_callback(uv_async_t* handle, int status);
	static void async_thread_pool_callback(uv_work_t* handle);

	static void async_after_thread_pool_callback(uv_work_t* handle, int status);
	static void uv_close_func(uv_handle_t* handle);
	//static void sendBaton(uv_async_t* async);
	Baton* createBaton();
	//void createBaton(int& count);
	static void sendBaton(uv_async_t* async);

public:
//	static BATON_VECTOR _vBatons;
//	static BATON_ITERATOR _iter;
	//void async_thread_work();
	
};


#endif