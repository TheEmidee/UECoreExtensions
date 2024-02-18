namespace UnrealBuildTool.Rules
{
	public class CoreExtensionsEditor : ModuleRules
	{
		public CoreExtensionsEditor(ReadOnlyTargetRules Target)
			: base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

			PrivateIncludePaths.Add("CoreExtensionsEditor/Private");

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"GameplayTags"
				}
			);
		}
	}
}