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

	mWallState = TILE_WALL_STATE::TW_BOTTOM | TILE_WALL_STATE::TW_LEFT | TILE_WALL_STATE::TW_RIGHT | TILE_WALL_STATE::TW_TOP;
	mWallStateint = uint32(mWallState);
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
void ATile::WallOff()
{
	_WallOff();
}

void ATile::ChangeWallState(TILE_WALL_STATE WallState)
{
	mWallState = WallState;
	mWallStateint = int32(mWallState);

	WallOff();

	if (TILE_WALL_STATE::TW_NONE != (TILE_WALL_STATE::TW_LEFT & mWallState))
	{
		_OnWallLeft();
	}
	if (TILE_WALL_STATE::TW_NONE != (TILE_WALL_STATE::TW_RIGHT & mWallState))
	{
		_OnWallRight();
	}
	if (TILE_WALL_STATE::TW_NONE != (TILE_WALL_STATE::TW_TOP & mWallState))
	{
		_OnWallTop();
	}
	if (TILE_WALL_STATE::TW_NONE != (TILE_WALL_STATE::TW_BOTTOM & mWallState))
	{
		_OnWallBottom();
	}
}