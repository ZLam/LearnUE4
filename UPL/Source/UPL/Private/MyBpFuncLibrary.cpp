// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBpFuncLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LocationServicesBPLibrary.h"
#include "Engine/World.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#include "AndroidPermissionFunctionLibrary.h"
#elif PLATFORM_IOS
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#include "IOS/IOSAppDelegate.h"
#endif

/**
* Android 调 UE
* 同样是通过 JNI 的
* 第一步，先在 java 端声明 native 方法（可以通过 UPL）
* 第二步，在 java 端，你想调用的地方像平时那样调用该方法
* 第三步，在 UE 端，实现该方法，注意函数签名，一般照着引擎源码来就ok了，另外自己定个 delegate 绑定回调也可以。具体有很多源码可以参考。
*/
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_ue4_GameActivity_nativeOnRestart(JNIEnv* jenv, jobject thiz, jobject activity)
{
	UE_LOG(LogTemp, Warning, TEXT("haha java call cpp"));
}
#endif

void UMyBpFuncLibrary::CppCallJava(const UObject* WorldContextObject)
{
	FString Result;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		jmethodID tMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Test", "()Ljava/lang/String;", false);
		jstring r = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, tMethodID);
		Result = FJavaHelper::FStringFromLocalRef(Env, r);
	}
#endif

	UKismetSystemLibrary::PrintString(WorldContextObject, *Result);
}

bool UMyBpFuncLibrary::IsLocationServiceEnable()
{
	return ULocationServices::AreLocationServicesEnabled();
}

void UMyBpFuncLibrary::OpenAppDetailSetting()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		jmethodID tMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_OpenAppDetailSetting", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, tMethodID);
	}
#elif PLATFORM_IOS
	[[UIApplication sharedApplication] openURL : [NSURL URLWithString : UIApplicationOpenSettingsURLString]];
#else
	UE_LOG(LogTemp, Warning, TEXT("UMyBpFuncLibrary::OpenAppDetailSetting, unsupport current platform"));
#endif
}

bool UMyBpFuncLibrary::CheckPermission(const FString& InPermissionName)
{
	bool Result = false;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		auto PermissionNameArg = FJavaHelper::ToJavaString(Env, InPermissionName);
		jmethodID tMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CheckPermission", "(Ljava/lang/String;)Z", false);
		Result = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, tMethodID, *PermissionNameArg);
	}
	return Result;
#endif

	return Result;
}

bool UMyBpFuncLibrary::CheckPermissionEX(const FString& InPermissionName)
{
	bool Result = false;

#if PLATFORM_ANDROID
	Result = UAndroidPermissionFunctionLibrary::CheckPermission(InPermissionName);
#endif

	return Result;
}

void UMyBpFuncLibrary::BindIOSOnDidBecomeActive()
{
#if PLATFORM_IOS
    FIOSCoreDelegates::OnDidBecomeActive.AddStatic(UMyBpFuncLibrary::_IOSOnDidBecomeActive);
#endif
}

void UMyBpFuncLibrary::_IOSOnDidBecomeActive()
{
    UKismetSystemLibrary::PrintString(GWorld, TEXT("haha UMyBpFuncLibrary::_IOSOnDidBecomeActive"));
}

void UMyBpFuncLibrary::Test()
{
    UKismetSystemLibrary::PrintString(GWorld, TEXT("lalala"));
}
