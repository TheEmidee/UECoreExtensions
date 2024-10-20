namespace UnrealBuildTool.Rules
{
	public class CoreExtensions : ModuleRules
	{
		public CoreExtensions(ReadOnlyTargetRules Target)
			: base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			PrivatePCHHeaderFile = "Private/CoreExtensionsPCH.h";

			PrivateIncludePaths.Add("CoreExtensions/Private");

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"GameplayTags",
					"UMG"
				}
			);
		}
	}
}