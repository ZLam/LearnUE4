#include "TestTaskGraph.h"

void FTaskLoadFile2Str::DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTaskLoadFile2Str::DoTask | CurrentThread : %d ==="), CurrentThread);

	auto FullFilePath = FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
	if (FPaths::FileExists(FullFilePath))
	{
		FileContent.Reset();
		FFileHelper::LoadFileToString(FileContent, *FullFilePath);

		TGraphTask<FTaskLoadFile2StrDone>::CreateTask(nullptr, CurrentThread).ConstructAndDispatchWhenReady(FileContent, DelegateLoadFile2Str);
	}
}

void FTaskLoadFile2StrDone::DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("=== FTaskLoadFile2StrDone::DoTask | CurrentThread : %d ==="), CurrentThread);

	DelegateLoadFile2Str.ExecuteIfBound(FileContent);
}
