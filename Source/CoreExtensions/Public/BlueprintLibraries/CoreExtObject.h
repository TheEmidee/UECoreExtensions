#pragma once

#include <CoreMinimal.h>

#include "CoreExtObject.generated.h"

UCLASS( Abstract, BlueprintType, Blueprintable )
class COREEXTENSIONS_API UCoreExtObject : public UObject
{
    GENERATED_BODY()

public:
    UWorld * GetWorld() const override;
};