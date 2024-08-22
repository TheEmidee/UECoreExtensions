#include "Core/CoreExtFilePrinterObject.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

UCoreExtFilePrinterObject::UCoreExtFilePrinterObject() :
    bFileOpened( false ),
    FilePath( "" )
{
}

bool UCoreExtFilePrinterObject::CreateFile( const FString file_name )
{
    if ( bFileOpened )
    {
        return false;
    }

    bFileOpened = true;

    FilePath = FPaths::ConvertRelativePathToFull( FPaths::ProjectSavedDir() ) + file_name;
    /*IPlatformFile & platformFile = FPlatformFileManager::Get().GetPlatformFile();
    platformFile.CreateDirectory( *FilePath );*/

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

    FFileHelper::SaveStringToFile( string_to_append, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append );
}

void UCoreExtFilePrinterObject::AppendLine( const FString string_to_append ) const
{
    if ( !bFileOpened )
    {
        return;
    }

    const auto result = "\n" + string_to_append;
    FFileHelper::SaveStringToFile( result, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append );
}