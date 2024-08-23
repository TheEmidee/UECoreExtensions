#include "Core/CoreExtFilePrinterObject.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

UCoreExtFilePrinterObject::UCoreExtFilePrinterObject() :
    bFileOpened( false ),
    FilePath( "" )
{
}

bool UCoreExtFilePrinterObject::CreateFile( UCoreExtFilePrinterObject *& file_printer, const FString file_name, const FString sub_directory, ECoreExtCreateFilePolicy creation_policy )
{
    file_printer = NewObject< UCoreExtFilePrinterObject >();
    file_printer->bFileOpened = true;

    auto & platform_file = FPlatformFileManager::Get().GetPlatformFile();

    const auto saved_folder = FPaths::ConvertRelativePathToFull( FPaths::ProjectSavedDir() );
    auto path = saved_folder;

    if ( sub_directory != "" )
    {
        path += sub_directory + "/";
    }

    if ( !platform_file.DirectoryExists( *path ) )
    {
        platform_file.CreateDirectory( *path );
    }

    file_printer->FilePath = path + file_name;

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