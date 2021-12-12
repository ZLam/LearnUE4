#include "TestInitThread.h"

FTestInitThreadRunnable::FTestInitThreadRunnable()
{
	Thread = FRunnableThread::Create(this, TEXT("TestInitThread"));
}

FTestInitThreadRunnable::~FTestInitThreadRunnable()
{
	if (Thread)
	{
		delete Thread;
		Thread = nullptr;
	}
}

bool FTestInitThreadRunnable::Init()
{
	/**
	 * 因为看源码，FRunnableThread的初始化流程里有个ThreadInitSyncEvent，
	 * 用来同步初始化流程，
	 * 所以写了这个例子测试下，
	 * 证明Init接口系会阻塞主线程的。
	 */
	for (int32 i = 0; i < INT32_MAX; i++)
	{
		int32 t = FMath::RandRange(0, 100);
	}

	return true;
}

uint32 FTestInitThreadRunnable::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestInitThreadRunnable::Run ==="))
	return 0;
}

void FTestInitThreadRunnable::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestInitThreadRunnable::Stop ==="))
}

void FTestInitThreadRunnable::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestInitThreadRunnable::Exit ==="))
}

void FTestInitThreadRunnable::EnsureCompletion()
{
	if (Thread)
	{
		Stop();
		Thread->WaitForCompletion();
	}
}
