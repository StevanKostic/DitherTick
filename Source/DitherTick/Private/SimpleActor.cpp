// Copyright Stevan Kostic

#include "SimpleActor.h"


ASimpleActor::ASimpleActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

	/** Load StaticMesh */
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(Mesh.Object);
	}

	/** Load Material */
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/M_BaseMaterial.M_BaseMaterial'"));
	if (Material.Succeeded())
	{
		StaticMesh->SetMaterial(0, Material.Object);
		StaticMesh->SetCustomPrimitiveDataFloat(0, 0.f);
	}

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	StaticMesh->SetVisibility(false);
}

void ASimpleActor::ChangeColor()
{
	StaticMesh->SetVisibility(true);
	float Value = FMath::RandRange(0.f, 1.f);
	StaticMesh->SetCustomPrimitiveDataFloat(0, Value);
}
