// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class UCreateMapByBSP;

UCLASS()
class PROCEDURALMAP_API ARoom : public AActor
{
	GENERATED_BODY()
private:
	TSubclassOf<ATile> m_TileClass;
	std::vector<ATile*> m_vecTile;
	FVector m_RoomSize;
public:
	void CreateRoom(UCreateMapByBSP* BSPMap, FVector StartTile, FVector EndTile);
	void reset();
public:	
	// Sets default values for this actor's properties
	ARoom();

	const FVector& getRoomSize()
	{
		return m_RoomSize;
	}

	const ATile* const getCenterTile()const
	{
		if (m_vecTile.size() > 0)
		{
			int CenterIndex = m_vecTile.size() / 2;
			return m_vecTile[CenterIndex];
		}
		return nullptr;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
