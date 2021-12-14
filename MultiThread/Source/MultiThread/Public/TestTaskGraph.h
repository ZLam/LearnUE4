#pragma once

#include "Async/TaskGraphInterfaces.h"

DECLARE_DELEGATE_OneParam(FDelegateLoadFile2Str, const FString&);

class FTaskLoadFile2Str
{
private:
	FString FilePath;
	FString FileContent;
	FDelegateLoadFile2Str DelegateLoadFile2Str;

public:
	FORCEINLINE FTaskLoadFile2Str(FString InFilePath, FDelegateLoadFile2Str InDelegate) :
	FilePath(InFilePath),
	DelegateLoadFile2Str(InDelegate)
	{
		
	}

	static FORCEINLINE TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskLoadFile2Str, STATGROUP_TaskGraphTasks);
	}

	FORCEINLINE ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

	static FORCEINLINE ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);
};

class FTaskLoadFile2StrDone
{
private:
	FString FileContent;
	FDelegateLoadFile2Str DelegateLoadFile2Str;

public:
	FORCEINLINE FTaskLoadFile2StrDone(FString InFileContent, FDelegateLoadFile2Str InDelegate) :
	FileContent(MoveTemp(InFileContent)),
	DelegateLoadFile2Str(InDelegate)
	{
		
	}

	static FORCEINLINE TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskLoadFile2StrDone, STATGROUP_TaskGraphTasks);
	}

	FORCEINLINE ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::GameThread;
	}

	static FORCEINLINE ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);
};

class FTestTaskGraph
{
private:
	int32 Data;

public:
	FORCEINLINE FTestTaskGraph(const int32& InData) : Data(InData) {}

	static FORCEINLINE TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskLoadFile2Str, STATGROUP_TaskGraphTasks);
	}

	FORCEINLINE ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

	static FORCEINLINE ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("haha111 %d"), Data)
	}
};
