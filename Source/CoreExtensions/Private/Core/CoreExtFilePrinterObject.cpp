#include "Core/CoreExtFilePrinterObject.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

UCoreExtFilePrinterObject::UCoreExtFilePrinterObject() :
    bFileOpened( false ),
    FilePath( "" )
{
}

bool UCoreExtFilePrinterObject::CreateFile( UCoreExtFilePrinterObject *& file_printer, const FString file_name, const FString sub_directory, const ECoreExtCreateFilePolicy creation_policy )
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

    const auto test_path = path + file_name;
    const auto file_exists = platform_file.FileExists( *test_path );

    auto name = file_name;

    switch ( creation_policy )
    {
        case Append:
            break;
        case Clear:
        {
            if ( file_exists )
            {
                platform_file.DeleteFile( *test_path );
            }
        }
        break;
        case CreateNew:
        {
            if ( file_exists )
            {
                name = GetNewFileName( file_name, path );
            }
        }
        break;
        default:
        {
            checkNoEntry();
        }
        break;
    }

    file_printer->FilePath = path + name;

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

FString UCoreExtFilePrinterObject::GetNewFileName( const FString original_name, const FString path )
{
    auto & platform_file = FPlatformFileManager::Get().GetPlatformFile();

    auto name = original_name;

    auto postfix_index = 0;
    while ( platform_file.FileExists( *( path + name ) ) )
    {
        ++postfix_index;
        auto extension_index = 0;
        if ( original_name.FindLastChar( '.', extension_index ) )
        {
            name = original_name;
            name.InsertAt( extension_index, "_" + FString::FromInt( postfix_index ) );
            continue;
        }

        name = original_name + "_" + FString::FromInt( postfix_index );
    }

    return name;
}