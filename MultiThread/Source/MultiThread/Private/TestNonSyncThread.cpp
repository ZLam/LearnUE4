#include "TestNonSyncThread.h"
#include "NormalSingleton.h"

FTestNonSyncThreadRunnableOne::FTestNonSyncThreadRunnableOne()
{
	Thread = FRunnableThread::Create(this, TEXT("TestNonSyncThreadRunnableOne"));
}

FTestNonSyncThreadRunnableOne::~FTestNonSyncThreadRunnableOne()
{
	
}

bool FTestNonSyncThreadRunnableOne::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestNonSyncThreadRunnableOne::Init ==="))
	return true;
}

uint32 FTestNonSyncThreadRunnableOne::Run()
{
	int32 CurCount = 0;
	while (StopTaskCounter.GetValue() == 0 && CurCount < MaxWorkCount)
	{
		FNormalSingleton::Get().IncreaseNonSyncCounter();
		CurCount++;
	}
	return 0;
}

void FTestNonSyncThreadRunnableOne::Stop()
{
	StopTaskCounter.Increment();
}

void FTestNonSyncThreadRunnableOne::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestNonSyncThreadRunnableOne::Exit ==="))
}

void FTestNonSyncThreadRunnableOne::EnsureCompletion()
{
	if (Thread)
	{
		Stop();
		Thread->WaitForCompletion();
	}
}

FTestNonSyncThreadRunnableTwo::FTestNonSyncThreadRunnableTwo()
{
	Thread = FRunnableThread::Create(this, TEXT("TestNonSyncThreadRunnableTwo"));
}

FTestNonSyncThreadRunnableTwo::~FTestNonSyncThreadRunnableTwo()
{
	
}

bool FTestNonSyncThreadRunnableTwo::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestNonSyncThreadRunnableTwo::Init ==="))
	return true;
}

uint32 FTestNonSyncThreadRunnableTwo::Run()
{
	int32 CurCount = 0;
	while (StopTaskCounter.GetValue() == 0 && CurCount < MaxWorkCount)
	{
		FNormalSingleton::Get().IncreaseNonSyncCounter();
		CurCount++;
	}
	return 0;
}

void FTestNonSyncThreadRunnableTwo::Stop()
{
	StopTaskCounter.Increment();
}

void FTestNonSyncThreadRunnableTwo::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestNonSyncThreadRunnableTwo::Exit ==="))
}

void FTestNonSyncThreadRunnableTwo::EnsureCompletion()
{
	if (Thread)
	{
		Stop();
		Thread->WaitForCompletion();
	}
}
