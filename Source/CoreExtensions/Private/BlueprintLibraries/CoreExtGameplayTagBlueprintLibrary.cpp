#include "BlueprintLibraries/CoreExtGameplayTagBlueprintLibrary.h"

FString UCoreExtGameplayTagBlueprintLibrary::RemoveGameplayTagParents( const FGameplayTag tag, const int number_parents_to_remove, bool tag_must_exist /*= true*/ )
{
    const auto tag_string = tag.ToString();

    TArray< FString > tag_parts;
    tag_string.ParseIntoArray( tag_parts, TEXT( "." ) );

    if ( tag_parts.Num() <= number_parents_to_remove )
    {
        return tag.ToString();
    }

    TStringBuilder< 64 > string_builder;
    auto first_tag = true;

    for ( auto index = number_parents_to_remove; index < tag_parts.Num(); ++index )
    {
        if ( !first_tag )
        {
            string_builder << TEXT( "." );
        }

        string_builder << tag_parts[ index ];
        first_tag = false;
    }

    return *string_builder;
}
