// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBpFuncLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#endif

void UMyBpFuncLibrary::CppCallJava(const UObject* WorldContextObject)
{
	UE_LOG(LogTemp, Warning, TEXT("haha123"));

	UKismetSystemLibrary::PrintString(WorldContextObject, TEXT("haha345"));

	FString ResultTest;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		jmethodID methodID_Test = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Test", "()Ljava/lang/String;", false);
		jstring Result = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, methodID_Test);
		ResultTest = FJavaHelper::FStringFromLocalRef(Env, Result);
	}
#endif

	UKismetSystemLibrary::PrintString(WorldContextObject, *ResultTest);
}
