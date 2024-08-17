// Copyright Stevan Kostic

#include "SpawnSubsystem_Scripted.h"

#include "SimpleActor.h"


TStatId USpawnSubsystemScripted::GetStatId() const
{
	return Super::GetStatID();
}

void USpawnSubsystemScripted::Tick(float DeltaTime)
{
	if (!bSubsystemEnabled)
	{
		return;
	}
	
	SpawnActors(DeltaTime);

	TickTime += DeltaTime;

	/** Draw Hi */
	if (TickTime > 6.f
		&& TickTime <= 10.f)
	{
		DrawHi(DeltaTime);
	}

	/** Remove Hi */
	if (TickTime > 10.f
		&& TickTime <= 10.5)
	{
		for (ASimpleActor* Actor : HiActors)
		{
			if (!Actor)
			{
				continue;
			}
			
			Actor->StaticMesh->SetVisibility(false);
		}

		HiActors.Empty();
	}

	if (TickTime > 11.f
		&& TickTime <= 16.f)
	{
		DrawReady(DeltaTime);
	}

	if (TickTime > 16.f)
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
}

void USpawnSubsystemScripted::SpawnActors(float DeltaTime)
{
	if (MaxCountActors <= 0)
	{
		return;
	}
	
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

		MaxCountActors--;

		if (MaxCountActors <= 0)
		{
			break;
		}
	}
}

void USpawnSubsystemScripted::DrawHi(float DeltaTime)
{
	SetupHi();
	
	if (HiActors.IsEmpty())
	{
		return;
	}
	
	for (ASimpleActor* Actor : HiActors)
	{
		if (!Actor)
		{
			continue;
		}
		
		Actor->ChangeColor();
	}
}

void USpawnSubsystemScripted::DrawReady(float DeltaTime)
{
	SetupReady();

	if (ReadyActors.IsEmpty())
	{
		return;
	}

	for (ASimpleActor* Actor : ReadyActors)
	{
		if (!Actor)
		{
			continue;
		}
		
		Actor->ChangeColor();
	}
}

void USpawnSubsystemScripted::SetupHi()
{
	if (bHiAlreadyDone)
	{
		return;
	}

	/** Get First line of letter H */
	for (int32 Index = 0; Index < 1100; Index++)
	{
		int32 ActualIndex = 1700 + Index;
		HiActors.Add(Actors[ActualIndex]);
	}

	/** Get Middle line of letter H */
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = 3700 + Index;
		HiActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = 5200 + Index;
		HiActors.Add(Actors[OtherIndex]);
	}

	/** Get the Other line of letter H */
	for (int32 Index = 0; Index < 1100; Index++)
	{
		int32 ActualIndex = 6200 + Index;
		HiActors.Add(Actors[ActualIndex]);
	}

	/** Get I */
	for (int32 Index = 0; Index < 900; Index++)
	{
		int32 ActualIndex = 9200 + Index;
		HiActors.Add(Actors[ActualIndex]);
	}

	/** Get Dot on I */
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = 10200 + Index;
		HiActors.Add(Actors[ActualIndex]);
	}

	bHiAlreadyDone = true;
}

void USpawnSubsystemScripted::SetupReady()
{
	if (bReadyAlreadyDone)
	{
		return;
	}

	/** Setup R */
	SetupR();

	/** Setup E */
	SetupE();

	/** Setup A */
	SetupA();

	/** Setup D */
	SetupD();
	
	/** Setup Y */
	SetupY();

	/** Setup Y */
	SetupQuestion();

	bReadyAlreadyDone = true;
}

void USpawnSubsystemScripted::SetupR()
{
	int32 Offset = 1 * 1500;
	for (int32 Index = 0; Index < 1100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 2 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 700 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[OtherIndex]);
	}

	Offset = 3 * 1500;
	for (int32 Index = 0; Index < 300; Index++)
	{
		int32 ActualIndex = Offset + 600 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 1100 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
	
	Offset = 4 * 1500;
	for (int32 Index = 0; Index < 400; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	for (int32 Index = 0; Index < 200; Index++)
	{
		int32 ActualIndex = Offset + 900 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
}

void USpawnSubsystemScripted::SetupE()
{
	int32 Offset = 6 * 1500;
	for (int32 Index = 0; Index < 1100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 7 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[OtherIndex]);

		int32 AnotherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[AnotherIndex]);
	}

	Offset = 8 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[OtherIndex]);

		int32 AnotherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[AnotherIndex]);
	}
}

void USpawnSubsystemScripted::SetupA()
{
	int32 Offset = 10 * 1500;
	for (int32 Index = 0; Index < 900; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 11 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1100 + Index;
		ReadyActors.Add(Actors[OtherIndex]);

		int32 AnotherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[AnotherIndex]);
	}

	Offset = 12 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[OtherIndex]);
	}

	Offset = 13 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1100 + Index;
		ReadyActors.Add(Actors[OtherIndex]);

		int32 AnotherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[AnotherIndex]);
	}

	Offset = 14 * 1500;
	for (int32 Index = 0; Index < 900; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
}

void USpawnSubsystemScripted::SetupD()
{
	int32 Offset = 16 * 1500;

	/** Setup D */
	for (int32 Index = 0; Index < 1000; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 17 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[OtherIndex]);
	}

	Offset = 18 * 1500;
	for (int32 Index = 0; Index < 200; Index++)
	{
		int32 ActualIndex = Offset + 300 + Index;
		ReadyActors.Add(Actors[ActualIndex]);

		int32 OtherIndex = Offset + 1000 + Index;
		ReadyActors.Add(Actors[OtherIndex]);
	}

	Offset = 19 * 1500;
	for (int32 Index = 0; Index < 500; Index++)
	{
		int32 ActualIndex = Offset + 500 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
}

void USpawnSubsystemScripted::SetupY()
{
	int32 Offset = 21 * 1500;
	for (int32 Index = 0; Index < 500; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 22 * 1500;
	for (int32 Index = 0; Index < 600; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 23 * 1500;
	for (int32 Index = 0; Index < 500; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
}

void USpawnSubsystemScripted::SetupQuestion()
{
	int32 Offset = 25 * 1500;
	for (int32 Index = 0; Index < 300; Index++)
	{
		int32 ActualIndex = Offset + 1000 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 26 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	for (int32 Index = 0; Index < 300; Index++)
	{
		int32 ActualIndex = Offset + 400 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
	
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 27 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 700 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 1200 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 28 * 1500;
	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 700 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	for (int32 Index = 0; Index < 100; Index++)
	{
		int32 ActualIndex = Offset + 1100 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}

	Offset = 29 * 1500;
	for (int32 Index = 0; Index < 300; Index++)
	{
		int32 ActualIndex = Offset + 800 + Index;
		ReadyActors.Add(Actors[ActualIndex]);
	}
}
