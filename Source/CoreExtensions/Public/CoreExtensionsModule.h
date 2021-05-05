#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <Stats/Stats.h>

class COREEXTENSIONS_API ICoreExtensionsModule : public IModuleInterface
{

public:
    static ICoreExtensionsModule & Get()
    {
        static auto & singleton = FModuleManager::LoadModuleChecked< ICoreExtensionsModule >( "CoreExtensions" );
        return singleton;
    }

    static bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "CoreExtensions" );
    }
};
