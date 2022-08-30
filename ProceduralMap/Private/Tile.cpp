// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_TileBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TileBox"));

	if (nullptr != m_TileBox)
	{
		m_TileBox->SetupAttachment(GetRootComponent());
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::ChangeWallState(TILE_WALL_STATE WallState)
{
	mWallState = WallState;
	_ChangeWallState(mWallState);
}