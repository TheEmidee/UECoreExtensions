#include "CoreExtensionsModule.h"

class FCoreExtensionsModule final : public ICoreExtensionsModule
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

IMPLEMENT_MODULE( FCoreExtensionsModule, CoreExtensions )

void FCoreExtensionsModule::StartupModule()
{
}

void FCoreExtensionsModule::ShutdownModule()
{
}