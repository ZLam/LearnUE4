#include "TestThread.h"

FTestThreadRunnable::FTestThreadRunnable(const int32& InMaxAmount) :
MaxAmount(InMaxAmount)
{
	Thread = FRunnableThread::Create(this, TEXT("TestThreadRunnable"));
	EventPause = FGenericPlatformProcess::GetSynchEventFromPool();
}

FTestThreadRunnable::~FTestThreadRunnable()
{
	if (Thread)
	{
		delete Thread;
		Thread = nullptr;
	}
	if (EventPause)
	{
		FGenericPlatformProcess::ReturnSynchEventToPool(EventPause);
		EventPause = nullptr;
	}
}

bool FTestThreadRunnable::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestThreadRunnable::Init ==="));
	return true;
	// return false;	// only init , dont exec Run() or Exit()
}

uint32 FTestThreadRunnable::Run()
{
	// FScopeLock Lock(&LockPrimeNumber);			// 在这里lock的话，整个run没结束都get不到结果出来
	
	UE_LOG(LogTemp, Warning, TEXT("=== FTestThreadRunnable::Run Begin ==="));

	int32 CurAmount = 0;
	int32 CurNumber = 0;
	
	{
		FScopeLock Lock(&LockPrimeNumber);
		PrimeNumbers.Add(2);
		PrimeNumbers.Add(3);
		CurAmount = PrimeNumbers.Num();
		CurNumber = PrimeNumbers.Last();
	}
	
	while (StopTaskCounter.GetValue() == 0 && CurAmount < MaxAmount)
	{
		if (bPause)
		{
			EventPause->Wait();
		}
		
		bool bFound = false;

		while (!bFound)
		{
			bFound = true;
			CurNumber++;
			for (int32 i = 2; i < CurNumber; i++)
			{
				if (CurNumber % i == 0)
				{
					bFound = false;
					break;
				}
			}
		}
		
		if (bFound)
		{
			FScopeLock Lock(&LockPrimeNumber);
			PrimeNumbers.Add(CurNumber);
			CurAmount = PrimeNumbers.Num();

			UE_LOG(LogTemp, Warning, TEXT("no_%d : %d"), CurAmount, CurNumber);
		}
		
		// for (int32 i = 0; i < INT_MAX; i++)
		// {
		// 	int32 t = FMath::RandRange(0, 100);
		// }

		// FPlatformProcess::Sleep(2.0f);
	}

	UE_LOG(LogTemp, Warning, TEXT("last : %d"), PrimeNumbers.Last());

	UE_LOG(LogTemp, Warning, TEXT("=== FTestThreadRunnable::Run End ==="));
	
	return 0;
}

void FTestThreadRunnable::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestThreadRunnable::Stop ==="));
	StopTaskCounter.Increment();
}

void FTestThreadRunnable::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTestThreadRunnable::Exit ==="));
}

void FTestThreadRunnable::EnsureCompletion()
{
	Stop();
	if (Thread)
	{
		Thread->WaitForCompletion();
	}
}

void FTestThreadRunnable::WaitForCompletion()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
	}
}

int32 FTestThreadRunnable::GetLastPrimeNumber()
{
	FScopeLock Lock(&LockPrimeNumber);
	if (PrimeNumbers.Num() > 0)
	{
		return PrimeNumbers.Last();
	}
	return 0;
}

void FTestThreadRunnable::Pause()
{
	bPause = true;
}

void FTestThreadRunnable::Resume()
{
	if (bPause)
	{
		bPause = false;
		EventPause->Trigger();
	}
}
