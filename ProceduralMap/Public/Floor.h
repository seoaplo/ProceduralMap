// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

class ATile;

class PROCEDURALMAP_API Floor
{
private:
	FVector mArrayPos;
	FVector mPos;

	TSubclassOf<ATile> mTileClass;
	ATile* mTile;
public:
	void Init(FVector WorldPos, FVector ArrayPos, TSubclassOf<ATile> TileClass);
	ATile* spwanTile(UWorld* World);

	ATile* getTile()
	{
		return mTile;
	}


public:
	Floor();
	~Floor();
};
