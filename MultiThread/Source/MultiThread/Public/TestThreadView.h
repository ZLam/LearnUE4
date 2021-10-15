// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Async/AsyncWork.h"
#include "TestThreadView.generated.h"

class UButton;
class FTestThreadRunnable;
class FTestNonSyncThreadRunnableOne;
class FTestNonSyncThreadRunnableTwo;
class FTestInitThreadRunnable;
class FTestNormalAsyncTask;

class FTestStatic
{
public:
	void Run()
	{
		static bool b = false;		// 这种静态变量只会构造一个，就算构造多个FTestStatic
		if (!b)
		{
			UE_LOG(LogTemp, Warning, TEXT("=== FTestStatic::Run ==="));
			b = true;
		}
	}
};

/**
 * 
 */
UCLASS()
class MULTITHREAD_API UTestThreadView : public UUserWidget
{
	GENERATED_BODY()

private:
	FTestThreadRunnable* TestThreadRunnable;
	FTestNonSyncThreadRunnableOne* TestNonSyncThreadOne;
	FTestNonSyncThreadRunnableTwo* TestNonSyncThreadTwo;
	FTestInitThreadRunnable* TestInitThread;

	FAsyncTask<FTestNormalAsyncTask>* TestNormalAsyncWork;

protected:
	UPROPERTY()
	UButton* Btn_TestRunnable_Start;

	UPROPERTY()
	UButton* Btn_TestRunnable_Complete;

	UPROPERTY()
	UButton* Btn_TestRunnable_Kill;

	UPROPERTY()
	UButton* Btn_TestRunnable_GetPrimeNumber;

	UPROPERTY()
	UButton* Btn_TestRunnable_Pause;

	UPROPERTY()
	UButton* Btn_TestRunnable_Resume;

	UPROPERTY()
	UButton* Btn_TestNonSyncThread;

	UPROPERTY()
	UButton* Btn_GetNonSyncThreadResult;

	UPROPERTY()
	UButton* Btn_TestStatic;

	UPROPERTY()
	UButton* Btn_TestInitThread;

	UPROPERTY()
	UButton* Btn_TestNormalAsyncTask;

	UPROPERTY()
	UButton* Btn_TestAutoDelAsyncTask;

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void Btn_TestRunnable_Start_Callback();

	UFUNCTION()
	void Btn_TestRunnable_Complete_Callback();

	UFUNCTION()
	void Btn_TestRunnable_Kill_Callback();

	UFUNCTION()
	void Btn_TestRunnable_GetPrimeNumber_Callback();

	UFUNCTION()
	void Btn_TestRunnable_Pause_Callback();

	UFUNCTION()
	void Btn_TestRunnable_Resume_Callback();

	UFUNCTION()
	void Btn_TestNonSyncThread_Callback();

	UFUNCTION()
	void Btn_GetNonSyncThreadResult_Callback();

	UFUNCTION()
	void Btn_TestStatic_Callback();

	UFUNCTION()
	void Btn_TestInitThread_Callback();

	UFUNCTION()
	void Btn_TestNormalAsyncTask_Callback();

	UFUNCTION()
	void Btn_TestAutoDelAsyncTask_Callback();

	void CleanupTestThread();

	void CleanupTestAsyncTask();
};
