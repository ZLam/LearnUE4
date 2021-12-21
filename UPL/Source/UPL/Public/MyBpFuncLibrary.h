// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBpFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UPL_API UMyBpFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * UE 调 Android
	 * 主要就是通过 JNI 和 UPL
	 * 第一步：在 java 上实现自己的方法，这个可以通过 UE 提供的插件 UPL 实现。UPL 是虚幻插件语言，它定义了一系列节点可以在 Android 端添加方法和权限等。可以在自己
	 * 模块的 Build.cs 同级目录下创建一个 moduleName_UPL.xml ，然后在该 xml 文件里利用提供的节点添加自己的 java 方法，它会在构建 Android 工程时复制这些方法
	 * 代码到 GameActivity.java 里，最后记得在模块的 Build.cs 里加上该 xml 文件的路径。如下。
	 * string ModulePath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
	 * AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModulePath, "moduleName_UPL.xml"));
	 * 第二步：确定在 java 上自己的方法的签名是什么
	 * 第三步：在 UE 端，通过 FJavaWrapper 类的接口取到 java 端的自己的方法，然后调用，最后可以用 FJavaHelper 类转换 java 的数据类型成 UE 的类型
	 * 第四步：打包尝试
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void CppCallJava(const UObject * WorldContextObject);

	/**
	 * 定位服务是否开启
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsLocationServiceEnable();

	/**
	 * 打开 app 设置页
	 */
	UFUNCTION(BlueprintCallable)
	static void OpenAppDetailSetting();

	/**
	 * 检查 app 某权限是否开启
	 */
	UFUNCTION(BlueprintCallable)
	static bool CheckPermission(const FString& InPermissionName);

	/**
	 * 检查 app 某权限是否开启
	 */
	UFUNCTION(BlueprintCallable)
	static bool CheckPermissionEX(const FString& InPermissionName);
    
    UFUNCTION(BlueprintCallable)
    static void BindIOSOnDidBecomeActive();
    
    static void _IOSOnDidBecomeActive();
    
    UFUNCTION(BlueprintCallable)
    static void Test();
};
