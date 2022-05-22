#pragma once

#include <CoreMinimal.h>

#include "CoreExtObjectWithWorld.generated.h"

UCLASS( Abstract, BlueprintType, Blueprintable )
class COREEXTENSIONS_API UCoreExtObjectWithWorld : public UObject
{
    GENERATED_BODY()

public:
    UWorld * GetWorld() const override;
};