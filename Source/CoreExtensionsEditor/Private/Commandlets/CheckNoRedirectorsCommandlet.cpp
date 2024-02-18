#include "Commandlets/CheckNoRedirectorsCommandlet.h"

#include <AssetRegistry/AssetRegistryModule.h>
#include <AssetRegistry/IAssetRegistry.h>

DEFINE_LOG_CATEGORY_STATIC( LogFindRedirectors, Log, All )

int32 UCheckNoRedirectorsCommandlet::Main( const FString & params )
{
    UE_LOG( LogFindRedirectors, Display, TEXT( "--------------------------------------------------------------------------------------------" ) );
    UE_LOG( LogFindRedirectors, Display, TEXT( "Running CheckNoRedirectors Commandlet" ) );

    const auto & asset_registry_module = FModuleManager::LoadModuleChecked< FAssetRegistryModule >( TEXT( "AssetRegistry" ) );
    const IAssetRegistry & asset_registry = asset_registry_module.Get();

    TArray< FAssetData > redirect_assets;
    TSet< FString > redirect_packages;
    TSet< FString > referencer_packages;

    asset_registry.GetAssetsByClass( UObjectRedirector::StaticClass()->GetClassPathName(), redirect_assets );

    for ( const auto & AssetData : redirect_assets )
    {
        auto is_already_in_set = false;
        FString redirect_file;
        const auto package_name = AssetData.PackageName.ToString();

        FPackageName::SearchForPackageOnDisk( *package_name, nullptr, &redirect_file );

        redirect_packages.Add( redirect_file, &is_already_in_set );

        if ( !is_already_in_set )
        {
            TArray< FName > referencers;
            asset_registry.GetReferencers( AssetData.PackageName, referencers );

            for ( auto referencer : referencers )
            {
                FString ReferencerFile;
                FPackageName::SearchForPackageOnDisk( *referencer.ToString(), nullptr, &ReferencerFile );

                referencer_packages.Add( ReferencerFile );
            }

            if ( !package_name.StartsWith( "/Game/Developers/" ) )
            {
                UE_LOG( LogFindRedirectors, Error, TEXT( "Found redirector : %s" ), *package_name );
                UE_LOG( LogFindRedirectors, Verbose, TEXT( "Referenced by:" ) );

                for ( const auto referencer : referencer_packages )
                {
                    UE_LOG( LogFindRedirectors, Verbose, TEXT( " - %s" ), *referencer );
                }
            }
        }
    }

    UE_LOG( LogFindRedirectors, Display, TEXT( "Successfully finished running CheckNoRedirectors Commandlet" ) );
    UE_LOG( LogFindRedirectors, Display, TEXT( "--------------------------------------------------------------------------------------------" ) );
    return 0;
}
