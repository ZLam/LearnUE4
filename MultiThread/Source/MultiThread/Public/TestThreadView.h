// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestThreadView.generated.h"

class UButton;
class FTestThreadRunnable;
class FTestNonSyncThreadRunnableOne;
class FTestNonSyncThreadRunnableTwo;

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
	UButton* Btn_TestAsyncTask;

	UPROPERTY()
	UButton* Btn_TestNonSyncThread;

	UPROPERTY()
	UButton* Btn_GetNonSyncThreadResult;

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
	void Btn_TestAsyncTask_Callback();

	UFUNCTION()
	void Btn_TestNonSyncThread_Callback();

	UFUNCTION()
	void Btn_GetNonSyncThreadResult_Callback();

	void DeleteTestThread();
};
