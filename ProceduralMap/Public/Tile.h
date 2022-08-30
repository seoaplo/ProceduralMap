// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engineminimal.h"
#include "../ProceduralMap.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class TILE_WALL_STATE : uint8
{
	TW_NONE UMETA(DisplayName = "NONE"),
	TW_TOP UMETA(DisplayName = "TOP"),
	TW_BOTTOM UMETA(DisplayName = "BOTTOM"),
	TW_LEFT UMETA(DisplayName = "LEFT"),
	TW_RIGHT UMETA(DisplayName = "RIGHT"),
};


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALMAP_API ATile : public AActor
{
	GENERATED_BODY()
public:
	FVector Pos;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_TileBox;

	TILE_WALL_STATE mWallState;

public:
	FVector getTileScale() const
	{
		if (nullptr != m_TileBox)
		{
			return m_TileBox->GetScaledBoxExtent() * 2;
		}

		return FVector(0, 0, 0);
	}

	FVector getPos() const
	{
		return Pos;
	}

	int getIndex() const
	{
		return Pos.X * Pos.Y;
	}

	void SetPos(FVector _Pos)
	{
		Pos = _Pos;
	}

	TILE_WALL_STATE getState()
	{
		return mWallState;
	}

public:	
	// Sets default values for this actor's properties
	ATile();
	void ChangeWallState(TILE_WALL_STATE WallState);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void WallOff();

	UFUNCTION(BlueprintImplementableEvent)
	void _ChangeWallState(TILE_WALL_STATE WallState);

};
