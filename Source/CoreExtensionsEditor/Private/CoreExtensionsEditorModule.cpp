#include "CoreExtensionsEditorModule.h"

class FCoreExtensionsEditorModule final : public ICoreExtensionsEditorModule
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

IMPLEMENT_MODULE( FCoreExtensionsEditorModule, CoreExtensionsEditor )

void FCoreExtensionsEditorModule::StartupModule()
{
}

void FCoreExtensionsEditorModule::ShutdownModule()
{
}