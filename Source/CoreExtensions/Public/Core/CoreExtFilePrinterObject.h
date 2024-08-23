#pragma once

#include <CoreMinimal.h>
#include <UObject/Object.h>

#include "CoreExtFilePrinterObject.generated.h"

UENUM( BlueprintType )
enum ECoreExtCreateFilePolicy
{
    Append,
    Clear,
    CreateNew
};

UCLASS( BlueprintType )
class COREEXTENSIONS_API UCoreExtFilePrinterObject : public UObject
{
    GENERATED_BODY()

public:
    UCoreExtFilePrinterObject();

    UFUNCTION( BlueprintCallable, meta = ( ReturnDisplayName = "Success" ) )
    static bool CreateFile( UCoreExtFilePrinterObject *& file_printer, FString file_name, const FString sub_directory, ECoreExtCreateFilePolicy creation_policy );

    UFUNCTION( BlueprintCallable )
    void CloseFile();

    UFUNCTION( BlueprintCallable )
    void AppendString( FString string_to_append ) const;

    UFUNCTION( BlueprintCallable )
    void AppendLine( FString string_to_append ) const;

private:
    bool bFileOpened;
    FString FilePath;
};
