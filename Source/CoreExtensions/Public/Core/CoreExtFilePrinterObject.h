#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "CoreExtFilePrinterObject.generated.h"

UENUM( BlueprintType )
enum class ECoreExtCreateFilePolicy : uint8
{
    Append,
    Clear,
    CreateNew
};

UCLASS( BlueprintType )
class COREEXTENSIONS_API UCoreExtFilePrinterObject final : public UObject
{
    GENERATED_BODY()

public:
    UCoreExtFilePrinterObject();

    UFUNCTION( BlueprintCallable, meta = ( ReturnDisplayName = "Success" ) )
    static bool CreateFile( UCoreExtFilePrinterObject *& file_printer, const FString & file_name, const FString & sub_directory, ECoreExtCreateFilePolicy creation_policy );

    UFUNCTION( BlueprintCallable )
    void CloseFile();

    UFUNCTION( BlueprintCallable )
    void AppendString( const FString & string_to_append );

    UFUNCTION( BlueprintCallable )
    void AppendLine( const FString & string_to_append );

private:
    static FString GetNewFileName( const FString & original_name, const FString & path );

    bool bFileOpened;
    FString FilePath;
    FStringBuilderBase TextToPrint;
};