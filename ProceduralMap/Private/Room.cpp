// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "CreateMapByBSP.h"

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

void ARoom::CreateRoom(UCreateMapByBSP* BSPMap, FVector StartTile, FVector EndTile)
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

	m_RoomSize = StartTile - EndTile;

	for (int Row = StartTile.Y; Row < EndTile.Y; ++Row)
	{
		for (int Col = StartTile.X; Col < EndTile.X; ++Col)
		{
			ATile* ConnectTile = BSPMap->getTile(FVector(Col, Row, 0));
			if (nullptr == ConnectTile)
			{
				continue;
			}
			ConnectTile->WallOff();
			m_vecTile.push_back(ConnectTile);
			const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
			ConnectTile->AttachToActor(this, AttachmentTransformRules);
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
 
