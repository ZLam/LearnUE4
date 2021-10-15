#pragma once

#include "Async/AsyncWork.h"

class MULTITHREAD_API FTestNormalAsyncTask : public FNonAbandonableTask
{
	friend class FAsyncTask<FTestNormalAsyncTask>;

	FTestNormalAsyncTask()
	{
		
	}

	void DoWork()
	{
		UE_LOG(LogTemp, Warning, TEXT("=== FTestNormalAsyncTask::DoWork ==="));
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTestNormalAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};

class MULTITHREAD_API FTestAutoDelAsyncTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FTestAutoDelAsyncTask>;

	FTestAutoDelAsyncTask()
	{
		
	}

	void DoWork()
	{
		UE_LOG(LogTemp, Warning, TEXT("=== FTestAutoDelAsyncTask::DoWork ==="));
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTestAutoDelAsyncTask, STATGROUP_ThreadPoolAsyncTasks)
	}
};
