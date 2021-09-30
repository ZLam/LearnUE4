#pragma once

#include "HAL/Runnable.h"

class MULTITHREAD_API FTestNonSyncThreadRunnableOne : public FRunnable
{
private:
	FThreadSafeCounter StopTaskCounter = 0;

	FRunnableThread* Thread = nullptr;

	int32 MaxWorkCount = 1000000;

public:
	FTestNonSyncThreadRunnableOne();
	virtual ~FTestNonSyncThreadRunnableOne() override;
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void EnsureCompletion();
};

class MULTITHREAD_API FTestNonSyncThreadRunnableTwo : public FRunnable
{
private:
	FThreadSafeCounter StopTaskCounter = 0;

	FRunnableThread* Thread = nullptr;

	int32 MaxWorkCount = 1000000;

public:
	FTestNonSyncThreadRunnableTwo();
	virtual ~FTestNonSyncThreadRunnableTwo() override;
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void EnsureCompletion();
};
