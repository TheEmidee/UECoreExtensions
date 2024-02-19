#pragma once

#include <Commandlets/Commandlet.h>
#include <CoreMinimal.h>

#include "CheckNoRedirectorsCommandlet.generated.h"

UCLASS()
class COREEXTENSIONSEDITOR_API UCheckNoRedirectorsCommandlet final : public UCommandlet
{
    GENERATED_BODY()

public:
    int32 Main( const FString & params ) override;
};
