#include "Core/CoreExtFilePrinterObject.h"

#include "Misc/FileHelper.h"

UCoreExtFilePrinterObject::UCoreExtFilePrinterObject() :
    bFileOpened( false ),
    FilePath( "" )
{
}

bool UCoreExtFilePrinterObject::OpenFile( const FString file_name )
{
    if ( bFileOpened )
    {
        return false;
    }

    bFileOpened = true;

    FilePath = FPaths::ConvertRelativePathToFull( FPaths::ProjectSavedDir() ) + file_name;

    return true;
}

void UCoreExtFilePrinterObject::CloseFile()
{
    bFileOpened = false;
}

void UCoreExtFilePrinterObject::AppendString( const FString string_to_append ) const
{
    if ( !bFileOpened )
    {
        return;
    }

    const auto result = string_to_append + "\n";

    FFileHelper::SaveStringToFile( result, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append );
}