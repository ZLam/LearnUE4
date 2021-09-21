// Fill out your copyright notice in the Description page of Project Settings.

#include "TestThreadView.h"
#include "Components/Button.h"
#include "TestThread.h"

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

	Btn_TestAsyncTask = Cast<UButton>(GetWidgetFromName(TEXT("Btn_TestAsyncTask")));
	if (Btn_TestAsyncTask)
	{
		FScriptDelegate BtnCallback;
		BtnCallback.BindUFunction(this, TEXT("Btn_TestAsyncTask_Callback"));
		Btn_TestAsyncTask->OnClicked.Add(BtnCallback);
	}
}

void UTestThreadView::NativeDestruct()
{
	DeleteTestThread();
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
	//Stop方法在FRunnableThread的kill方法中被调用（kill可以选择等待还是不等待线程结束，kill实际也是通过stop来停止线程，如果stop没有执行停止线程的操作，则kill如果是等待线程，则将一致阻塞），而kill方法也会被FRunnableThread::~FRunnableThread（）自动调用，这时kill是等待线程结束的
	DeleteTestThread();		// 里面会调一下 Stop() 尝试停止线程，bShouldWait==false的话直接清理线程，bShouldWait==true的话会阻塞等线程执行完再清理，注意避免泄漏或者死锁之类（init -> run -> stop -> exit）

	// delete TestThreadRunnable;		// 这样 delete 也会触发Stop()，因为看源码至少Windows平台这边析构Thread会调Kill()，里面会调Stop()
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

void UTestThreadView::Btn_TestAsyncTask_Callback()
{
	
}

void UTestThreadView::DeleteTestThread()
{
	if (TestThreadRunnable)
	{
		TestThreadRunnable->EnsureCompletion();
		delete TestThreadRunnable;
		TestThreadRunnable = nullptr;
	}
}
