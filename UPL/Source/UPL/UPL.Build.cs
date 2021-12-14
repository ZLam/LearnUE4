// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UPL : ModuleRules
{
	public UPL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(EngineDirectory, "Plugins/Runtime/AndroidPermission/Source/AndroidPermission/Classes"),
			}
		);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"LocationServicesBPLibrary",
			}
		);

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Launch",
					"LocationServicesAndroidImpl",
					"AndroidPermission",
				}
			);

			string ModulePath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModulePath, "UPL_UPL.xml"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicFrameworks.AddRange(
				new string[] {
					"UIKit",
					"Foundation",
				}
			);
		}
	}
}
