// Copyright Stevan Kostic

#pragma once

#include "SimpleActor.generated.h"


UCLASS()
class ASimpleActor : public AActor
{
	GENERATED_BODY()

	ASimpleActor();
	
public:
	void ChangeColor();
	
	UPROPERTY()
	UStaticMeshComponent* StaticMesh = nullptr;
};
