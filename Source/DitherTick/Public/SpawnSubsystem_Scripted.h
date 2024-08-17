// Copyright Stevan Kostic

#pragma once

#include "SpawnSubsystem_Scripted.generated.h"

class ASimpleActor;

/* This Abomination was made for Presentation
 * Serves no other purpose except to Print "Hi" and "Ready?" in a Map_Level_Scripted
 * Better check SpawnSubsystem.h as it is proof of concept, and much easier to understand
 */
UCLASS()
class USpawnSubsystemScripted : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// Begin FTickableGameObject
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;
	// End FTickableGameObject

	/** Simple Handling if this Subsystem should Tick */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSubsystemEnabled = false;
	
	void SpawnActors(float DeltaTime);
	void DrawHi(float DeltaTime);
	void DrawReady(float DeltaTime);
	
	void SetupHi();
	void SetupReady();

	/** Good Luck! */
	void SetupR();
	void SetupE();
	void SetupA();
	void SetupD();
	void SetupY();
	void SetupQuestion();

	/** TickTime in Seconds */
	float TickTime = 0.f;

	/** TotalCount of all Spawned SimpleActors */
	UPROPERTY(BlueprintReadOnly)
	int32 TotalCount = 0;

	/** How many SimpleActors to Spawn per Frame */
	UPROPERTY(BlueprintReadOnly)
	int32 SpawnActorPerFrame = 30;

	/** How many SimpleActors to Update per Frame */
	UPROPERTY(BlueprintReadOnly)
	int32 UpdateActorPerFrame = 512;

private:
	/** Current Row and Column of a Group */
	int32 Row = 0;
	int32 Column = 0;

	/** Maximum Rows and Columns in a Group. This is GROUP of 10x10 Actors */
	int32 MaxRows = 10;
	int32 MaxColumns = 10;

	/** Current Group Column we are building. Each Group of 10x10 is 1 GroupColumn */
	int32 GroupColumns = 0;

	/** How many Group Columns we can have. 1 GroupColumn is 1000 actors. Forming 1 giant Column */
	int32 MaxGroupColumns = 15;

	/** Offset for each new Group. So there is little space between each Group */
	int32 OffsetX = 0;
	int32 OffsetY = 0;

	/** Index we Modified Last */
	int32 ModifyIndex = 0;

	/** Number of Frames we don't want to go Under */
	float MinFrames = 100;

	/** How Many Actors we want to have */
	int32 MaxCountActors = 100500;

	UPROPERTY()
	TArray<ASimpleActor*> Actors = TArray<ASimpleActor*>();

	UPROPERTY()
	TArray<ASimpleActor*> HiActors = TArray<ASimpleActor*>();
	bool bHiAlreadyDone = false;
	
	UPROPERTY()
	TArray<ASimpleActor*> ReadyActors = TArray<ASimpleActor*>();
	bool bReadyAlreadyDone = false;
};
