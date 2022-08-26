// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

class UCreateMapByBSP;

UCLASS()
class PROCEDURALMAP_API APath : public AActor
{
	GENERATED_BODY()
private:
	TSubclassOf<ATile> m_TileClass;
	std::vector<ATile*> m_vecTile;

	UCreateMapByBSP* mBSPMap;

	FVector mStartPos;
	FVector mEndPos;

public:
	void CreatePath(UCreateMapByBSP* BSPMap, const ARoom* const Start, const ARoom* const End);
	void CreatePath(UCreateMapByBSP* BSPMap, ARoom* Start, APath* End);
	void CreatePath(UCreateMapByBSP* BSPMap, APath* Start, APath* End);

	void reset();
private:
	void CreatePathDerectionX(int spawnNumX, int spawnNumY, int& correntPosX, int& correntPosY);
	void CreatePathDerectionY(int spawnNumX, int spawnNumY, int& correntPosX, int& correntPosY);
public:	
	// Sets default values for this actor's properties
	APath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
