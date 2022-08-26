// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Tile.h"

void Floor::Init(FVector WorldPos, FVector ArrayPos, TSubclassOf<ATile> TileClass)
{
	mArrayPos = ArrayPos;
	mPos = WorldPos;
	mTileClass = TileClass;
}

ATile* Floor::spwanTile(UWorld* World)
{
	if (nullptr == mTile)
	{
		if (nullptr == World)
		{
			return nullptr;
		}
		const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		mTile = World->SpawnActor<ATile>(mTileClass, mPos, FRotator::ZeroRotator);
		if (nullptr == mTile)
		{
			return nullptr;
		}
		mTile->SetPos(mArrayPos);
	}
	return mTile;
}

Floor::Floor()
{
	mTile = nullptr;
}

Floor::~Floor()
{
}
