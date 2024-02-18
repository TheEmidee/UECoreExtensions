#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <Stats/Stats.h>

class COREEXTENSIONSEDITOR_API ICoreExtensionsEditorModule : public IModuleInterface
{

public:
    static ICoreExtensionsEditorModule & Get()
    {
        static auto & singleton = FModuleManager::LoadModuleChecked< ICoreExtensionsEditorModule >( "CoreExtensionsEditor" );
        return singleton;
    }

    static bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "CoreExtensionsEditor" );
    }
};
