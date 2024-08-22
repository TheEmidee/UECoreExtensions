#pragma once

#include <CoreMinimal.h>
#include <UObject/Object.h>

#include "CoreExtFilePrinterObject.generated.h"

UCLASS( BlueprintType )
class COREEXTENSIONS_API UCoreExtFilePrinterObject : public UObject
{
    GENERATED_BODY()

public:
    UCoreExtFilePrinterObject();

    UFUNCTION( BlueprintCallable )
    bool OpenFile( FString file_name );

    UFUNCTION( BlueprintCallable )
    void CloseFile();

    UFUNCTION( BlueprintCallable )
    void AppendString( FString string_to_append ) const;

private:
    bool bFileOpened;
    FString FilePath;
};
