// Fill out your copyright notice in the Description page of Project Settings.

#include "TestThreadView.h"
#include "Components/Button.h"
#include "TestThread.h"
#include "TestNonSyncThread.h"
#include "NormalSingleton.h"
#include "TestInitThread.h"
#include "TestAsyncTask.h"

void UTestThreadView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_TestRunnable_Start = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_Start")));
	if (Btn_TestRunnable_Start)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_Start_Callback"));
		Btn_TestRunnable_Start->OnClicked.Add(BtnCallback);
	}

	Btn_TestRunnable_Complete = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_Complete")));
	if (Btn_TestRunnable_Complete)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_Complete_Callback"));
		Btn_TestRunnable_Complete->OnClicked.Add(BtnCallback);
	}

	Btn_TestRunnable_Kill = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_Kill")));
	if (Btn_TestRunnable_Kill)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_Kill_Callback"));
		Btn_TestRunnable_Kill->OnClicked.Add(BtnCallback);
	}

	Btn_TestRunnable_GetPrimeNumber = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_GetPrimeNumber")));
	if (Btn_TestRunnable_GetPrimeNumber)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_GetPrimeNumber_Callback"));
		Btn_TestRunnable_GetPrimeNumber->OnClicked.Add(BtnCallback);
	}

	Btn_TestRunnable_Pause = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_Pause")));
	if (Btn_TestRunnable_Pause)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_Pause_Callback"));
		Btn_TestRunnable_Pause->OnClicked.Add(BtnCallback);
	}

	Btn_TestRunnable_Resume = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestRunnable_Resume")));
	if (Btn_TestRunnable_Resume)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestRunnable_Resume_Callback"));
		Btn_TestRunnable_Resume->OnClicked.Add(BtnCallback);
	}

	Btn_TestNonSyncThread = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestNonSyncThread")));
	if (Btn_TestNonSyncThread)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestNonSyncThread_Callback"));
		Btn_TestNonSyncThread->OnClicked.Add(BtnCallback);
	}
	
	Btn_GetNonSyncThreadResult = Cast<UButton>(GetWidgetFromName(TEXT("Btn_GetNonSyncThreadResult")));
	if (Btn_GetNonSyncThreadResult)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_GetNonSyncThreadResult_Callback"));
		Btn_GetNonSyncThreadResult->OnClicked.Add(BtnCallback);
	}

	Btn_TestStatic = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestStatic")));
	if (Btn_TestStatic)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestStatic_Callback"));
		Btn_TestStatic->OnClicked.Add(BtnCallback);
	}

	Btn_TestInitThread = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestInitThread")));
	if (Btn_TestInitThread)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestInitThread_Callback"));
		Btn_TestInitThread->OnClicked.Add(BtnCallback);
	}

	Btn_TestNormalAsyncTask = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestNormalAsyncTask")));
	if (Btn_TestNormalAsyncTask)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestNormalAsyncTask_Callback"));
		Btn_TestNormalAsyncTask->OnClicked.Add(BtnCallback);
	}

	Btn_TestAutoDelAsyncTask = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestAutoDeleteAsyncTask")));
	if (Btn_TestAutoDelAsyncTask)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestAutoDelAsyncTask_Callback"));
		Btn_TestAutoDelAsyncTask->OnClicked.Add(BtnCallback);
	}

	Btn_TestTaskGraph = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestTaskGraph")));
	if (Btn_TestTaskGraph)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestTaskGraph_Callback"));
		Btn_TestTaskGraph->OnClicked.Add(BtnCallback);
	}
}

void UTestThreadView::NativeDestruct()
{
	CleanupTestThread();
	CleanupTestAsyncTask();
}

void UTestThreadView::Btn_TestRunnable_Start_Callback()
{
	TestThreadRunnable = new FTestThreadRunnable(50000);
}

void UTestThreadView::Btn_TestRunnable_Complete_Callback()
{
	TestThreadRunnable->WaitForCompletion();		// WaitForCompletion，顾名思义就是一直等到线程Run完（init -> run -> exit）
	// TestThreadRunnable->EnsureCompletion();
}

void UTestThreadView::Btn_TestRunnable_Kill_Callback()
{
	// Stop方法在FRunnableThread的kill方法中被调用（kill可以选择等待还是不等待线程结束，kill实际也是通过stop来停止线程，如果stop没有执行停止线程的操作，则kill如果是等待线程，则将一致阻塞），而kill方法也会被FRunnableThread::~FRunnableThread（）自动调用，这时kill是等待线程结束的
	// 里面会调一下 Stop() 尝试停止线程，bShouldWait==false的话直接清理线程，bShouldWait==true的话会阻塞等线程执行完再清理，注意避免泄漏或者死锁之类（init -> run -> stop -> exit）
	TestThreadRunnable->Kill();
}

void UTestThreadView::Btn_TestRunnable_GetPrimeNumber_Callback()
{
	if (TestThreadRunnable)
	{
		auto Value = TestThreadRunnable->GetLastPrimeNumber();
		UE_LOG(LogTemp, Warning, TEXT("got : %d"), Value);
	}
}

void UTestThreadView::Btn_TestRunnable_Pause_Callback()
{
	if (TestThreadRunnable)
	{
		TestThreadRunnable->Pause();
	}
}

void UTestThreadView::Btn_TestRunnable_Resume_Callback()
{
	if (TestThreadRunnable)
	{
		TestThreadRunnable->Resume();
	}
}

void UTestThreadView::Btn_TestNonSyncThread_Callback()
{
	/**
	 * 这里尝试了下没做同步处理，同时读写一个公共资源，正确结果应该是2000000，但实际结果不是，是无法估计的，
	 * 导致结果的不对，所以对于公共资源的处理时要做同步
	 */
	FNormalSingleton::Get().ResetNonSyncCounter();
	if (!TestNonSyncThreadOne)
	{
		TestNonSyncThreadOne = new FTestNonSyncThreadRunnableOne();
	}
	if (!TestNonSyncThreadTwo)
	{
		TestNonSyncThreadTwo = new FTestNonSyncThreadRunnableTwo();
	}
}

void UTestThreadView::Btn_GetNonSyncThreadResult_Callback()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), FNormalSingleton::Get().GetNonSyncCounter());
}

void UTestThreadView::Btn_TestStatic_Callback()
{
	// for (int32 i = 0; i < 3; i++)
	// {
	// 	FTestStatic t;
	// 	t.Run();
	// }

	// TArray<int32> tArr;
	// tArr.Empty(10);
	// UE_LOG(LogTemp, Warning, TEXT("111 %d"), tArr.Num());
	// for (int32 i = 0; i < 10; i++)
	// {
	// 	tArr.Add(i + 1);
	// }
	// UE_LOG(LogTemp, Warning, TEXT("222 %d"), tArr.Num());
	// tArr.RemoveAt(tArr.Num() - 1, 1, false);
	// UE_LOG(LogTemp, Warning, TEXT("333 %d"), tArr.Num());

	int32 n = int32(1) / int32(3);
	UE_LOG(LogTemp, Warning, TEXT("%d"), n);
	n = int32(4) / int32(3);
	UE_LOG(LogTemp, Warning, TEXT("%d"), n);
}

void UTestThreadView::Btn_TestInitThread_Callback()
{
	if (!TestInitThread)
	{
		TestInitThread = new FTestInitThreadRunnable();
	}
}

void UTestThreadView::Btn_TestNormalAsyncTask_Callback()
{
	TestNormalAsyncWork = new FAsyncTask<FTestNormalAsyncTask>();
	TestNormalAsyncWork->StartBackgroundTask();
	UE_LOG(LogTemp, Warning, TEXT("=== UTestThreadView::Btn_TestNormalAsyncTask_Callback ==="));
}

void UTestThreadView::Btn_TestAutoDelAsyncTask_Callback()
{
	(new FAutoDeleteAsyncTask<FTestAutoDelAsyncTask>())->StartBackgroundTask();
	UE_LOG(LogTemp, Warning, TEXT("=== UTestThreadView::Btn_TestAutoDelAsyncTask_Callback ==="));
}

void UTestThreadView::Btn_TestTaskGraph_Callback()
{
	// TGraphTask<FTaskLoadFile2Str>::CreateTask().ConstructAndDispatchWhenReady();
}

void UTestThreadView::TestAsyncLoadFile2Str(const FString& InFilePath)
{
	FDelegateLoadFile2Str TmpDelegate;
	TmpDelegate.BindUFunction(this, TEXT("AsyncLoadFile2Str_Callback"));
	TGraphTask<FTaskLoadFile2Str>::CreateTask().ConstructAndDispatchWhenReady(InFilePath, TmpDelegate);
}

void UTestThreadView::CleanupTestThread()
{
	if (TestThreadRunnable)
	{
		TestThreadRunnable->EnsureCompletion();
		delete TestThreadRunnable;			// 这样 delete 也会触发Stop()，因为看源码至少Windows平台这边析构Thread会调Kill()，里面会调Stop()
		TestThreadRunnable = nullptr;
	}
	if (TestNonSyncThreadOne)
	{
		TestNonSyncThreadOne->EnsureCompletion();
		delete TestNonSyncThreadOne;
		TestNonSyncThreadOne = nullptr;
	}
	if (TestNonSyncThreadTwo)
	{
		TestNonSyncThreadTwo->EnsureCompletion();
		delete TestNonSyncThreadTwo;
		TestNonSyncThreadTwo = nullptr;
	}
	if (TestInitThread)
	{
		TestInitThread->EnsureCompletion();
		delete TestInitThread;
		TestInitThread = nullptr;
	}
}

void UTestThreadView::CleanupTestAsyncTask()
{
	if (TestNormalAsyncWork)
	{
		TestNormalAsyncWork->EnsureCompletion();
		delete TestNormalAsyncWork;
		TestNormalAsyncWork = nullptr;
	}
}
