// Copyright Stevan Kostic

#include "SpawnSubsystem.h"

#include "SimpleActor.h"


TStatId USpawnSubsystem::GetStatId() const
{
	return Super::GetStatID();
}

void USpawnSubsystem::Tick(float DeltaTime)
{
	if (!bSubsystemEnabled)
	{
		return;
	}
	
	if (bSpawn)
	{
		SpawnActors(DeltaTime);
	}

	if (bUpdate)
	{
		UpdateActors(DeltaTime);
	}
}

void USpawnSubsystem::SpawnActors(float DeltaTime)
{
	float Frames = 1 / DeltaTime;
	if (Frames >= MinFrames)
	{
		SpawnActorPerFrame++;
	}

	if (Frames <= MinFrames)
	{
		SpawnActorPerFrame--;
		if (SpawnActorPerFrame <= 0)
		{
			SpawnActorPerFrame = 0;
			return;
		}
	}
	
	for (int32 Index = 0; Index < SpawnActorPerFrame; Index++)
	{
		if (Column >= MaxColumns)
		{
			Column = 0;
			Row++;

			if (Row >= MaxRows)
			{
				Row = 0;
				OffsetX += 1550;
				GroupColumns++;

				if (GroupColumns >= MaxGroupColumns)
				{
					OffsetY += 1550;
					OffsetX = 0;
					GroupColumns = 0;
				}
			}
		}

		FVector Location = FVector::ZeroVector;
		Location.X += 150 * Column + OffsetX;
		Location.Y += 150 * Row + OffsetY;

		Column++;
		
		if (!GetWorld())
		{
			return;
		}

		FActorSpawnParameters SpawnParams;
		ASimpleActor* Actor = GetWorld()->SpawnActor<ASimpleActor>(Location, FRotator::ZeroRotator, SpawnParams);
		if (!Actor)
		{
			return;
		}

		Actors.Add(Actor);
		TotalCount = Actors.Num();
	}
}

void USpawnSubsystem::UpdateActors(float DeltaTime)
{
	float Frames = 1 / DeltaTime;
	if (Frames >= MinFrames)
	{
		UpdateActorPerFrame += 50;
	}

	if (Frames <= MinFrames)
	{
		UpdateActorPerFrame -= 50;
	}

	if (!Actors.IsValidIndex(0))
	{
		return;
	}
	
	int32 UpdateCount = 0;

	bool bLoop = true;
	while (bLoop)
	{
		Actors[ModifyIndex]->ChangeColor();

		ModifyIndex++;
		UpdateCount++;

		/** Updated whole Array, then we start from 0 */
		if (ModifyIndex > TotalCount - 1)
		{
			ModifyIndex = 0;
		}

		/** Updated Target Number of Actors, we can leave this Tick */
		if (UpdateCount > UpdateActorPerFrame)
		{
			bLoop = false;
		}
	}
}
