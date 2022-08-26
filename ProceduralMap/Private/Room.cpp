// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "CreateMapByBSP.h"
#include "Floor.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (nullptr == RootComponent)
	{
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
		if (nullptr != Box)
		{
			SetRootComponent(Box);
		}
		else
		{
			USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
			SetRootComponent(Root);
		}
	}
	

}

void ARoom::CreateRoom(UCreateMapByBSP* BSPMap, FVector StartTilePos, FVector EndTilePos)
{
	if (nullptr == RootComponent)
	{
		return;
	}
	if (nullptr == BSPMap)
	{
		return;
	}

	reset();

	m_RoomSize = StartTilePos - EndTilePos;
	FBox2D WallPos;
	WallPos.Min = FVector2D(StartTilePos.X - 1, StartTilePos.Y - 1);
	WallPos.Max = FVector2D(EndTilePos.X, EndTilePos.Y);


	FVector TileSize = BSPMap->getTileSize();
	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

	for (int Col = WallPos.Min.X; Col <= WallPos.Max.X; ++Col)
	{
		for (int Switch = 0; Switch < 2; ++Switch)
		{
			int Row = (Switch == 0) ? WallPos.Min.Y : WallPos.Max.Y;

			Floor* TargetFloor = BSPMap->getFloor(FVector(Col, Row, 0));
			if (nullptr == TargetFloor)
			{
				continue;
			}

			ATile* SpawnTile = TargetFloor->spwanTile(GetWorld());

			if (nullptr == SpawnTile)
			{
				continue;
			}
			SpawnTile->AttachToActor(this, AttachmentTransformRules);
			m_vecTile.push_back(SpawnTile);
		}
	}

	for (int Row = WallPos.Min.Y; Row < WallPos.Max.Y; ++Row)
	{
		for (int Switch = 0; Switch < 2; ++Switch)
		{
			int Col = (Switch == 0) ? WallPos.Min.X : WallPos.Max.X;

			Floor* TargetFloor = BSPMap->getFloor(FVector(Col, Row, 0));
			if (nullptr == TargetFloor)
			{
				continue;
			}

			ATile* SpawnTile = TargetFloor->spwanTile(GetWorld());

			if (nullptr == SpawnTile)
			{
				continue;
			}
			SpawnTile->AttachToActor(this, AttachmentTransformRules);
			m_vecTile.push_back(SpawnTile);
		}
	}

	for (int Row = StartTilePos.Y ; Row < EndTilePos.Y; ++Row)
	{
		for (int Col = StartTilePos.X; Col < EndTilePos.X; ++Col)
		{
			Floor* TargetFloor = BSPMap->getFloor(FVector(Col, Row, 0));
			if (nullptr == TargetFloor)
			{
				continue;
			}

			ATile* SpawnTile = TargetFloor->spwanTile(GetWorld());

			if (nullptr == SpawnTile)
			{
				continue;
			}
			SpawnTile->WallOff();
			SpawnTile->AttachToActor(this, AttachmentTransformRules);
			m_vecTile.push_back(SpawnTile);
		}
	}
}

void ARoom::reset()
{

}
// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
 
