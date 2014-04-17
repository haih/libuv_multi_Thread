#ifndef ASYNVC_H
#define ASYNVC_H

#include "uv.h"
#include "stdlib.h"
#include "stdio.h"
using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include <Windows.h>


//uv_async_t async;
//void after(uv_work_t *req, int status);
//void fake_download(uv_work_t *a);
//void print_progress(uv_async_t *a,int state);
#pragma comment(lib, "IPHLPAPI.lib")  
#pragma comment(lib, "Psapi.lib")

typedef struct Baton
{
	/* data */
	int iData1;
	int iData2;
	string strData;
}Data;

static vector<Baton*> _vBatons;
static vector<Baton*>::iterator iter;

void sendBaton(uv_async_t* async)
{
	//std::vector<Baton*>::iterator iter;
	if(!_vBatons.empty())
	{
		iter = _vBatons.begin();
		if(*iter)
		{
			Baton baton = **iter;
			_vBatons.erase(iter);
			//*iter = NULL;
			async->data = (void*) (&baton);
			uv_async_send(async);
			cout<<"Send Baton to the thread!"<<"iData1 = "<<baton.iData1<<endl;
		}
	}
}

void async_thread_work(void* arg)
{
	uv_async_t* async = ((uv_async_t*)arg);
	//int iData = *(int *)async->data;

	//string strData = *(string *)async->data;
	//while(1)
	//int icount = 2;
	//for(;icount >= 0;icount--)
	while(1)
	{
		//cout<<"async_thread_work  while(1)"<<endl;
		//strData.append("a");
		//async->data = (void *)&strData;
		//cout<<"async_thread_work~ data = "<<strData<<endl;
		sendBaton(async);
		//Baton* baton = static_cast<Baton*>(async->data);
		
		//uv_async_send(async);
		Sleep(50);
	}
	cout<<"async_thread_work send already~"<<endl;
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

void progress_cb1(uv_async_t *a,int state)
{	
	Baton* baton = static_cast<Baton*>(a->data);
	

	cout<<"progress_cb1, the data baton->iData1 = "<<baton->iData1<<endl;
	float fibRet = fib(30);
//	cout<<"data baton->iData2= "<<baton->iData2<<" in progress_cb"<<endl;
//	cout<<"data strData->strData= "<<baton->strData<<" in progress_cb"<<endl;
}
void progress_cb2(uv_async_t *a,int state)
{	
	Baton* baton = static_cast<Baton*>(a->data);


	cout<<"progress_cb2, the data baton->iData1 = "<<baton->iData1<<endl;
//	float fibRet = fib(30);
	//	cout<<"data baton->iData2= "<<baton->iData2<<" in progress_cb"<<endl;
	//	cout<<"data strData->strData= "<<baton->strData<<" in progress_cb"<<endl;
}
void progress_cb3(uv_async_t *a,int state)
{	
	Baton* baton = static_cast<Baton*>(a->data);


	cout<<"progress_cb3, the data baton->iData1 = "<<baton->iData1<<endl;
//	float fibRet = fib(30);
	//	cout<<"data baton->iData2= "<<baton->iData2<<" in progress_cb"<<endl;
	//	cout<<"data strData->strData= "<<baton->strData<<" in progress_cb"<<endl;
}
void progress_cb4(uv_async_t *a,int state)
{	
	Baton* baton = static_cast<Baton*>(a->data);


	cout<<"progress_cb4, the data baton->iData1 = "<<baton->iData1<<endl;
//	float fibRet = fib(30);
	//	cout<<"data baton->iData2= "<<baton->iData2<<" in progress_cb"<<endl;
	//	cout<<"data strData->strData= "<<baton->strData<<" in progress_cb"<<endl;
}

void createBaton(int& count)
{
	for(int i = 0;i< count; i++)
	{
		Baton* baton = new Baton();
		baton->iData1 = i;
		baton->iData2 = 2;
		baton->strData = "haihu";
		_vBatons.push_back(baton);
	}	
	return;
}


#endif

