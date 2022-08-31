// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engineminimal.h"
#include "../ProceduralMap.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class TILE_WALL_STATE
{
	TW_NONE		= 0x00,
	TW_TOP		= 0x01,
	TW_BOTTOM	= 0x02,
	TW_LEFT		= 0x04,
	TW_RIGHT	= 0x08,
};

ENUM_CLASS_FLAGS(TILE_WALL_STATE);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALMAP_API ATile : public AActor
{
	GENERATED_BODY()
public:
	FVector Pos;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_TileBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = getStateInt, Meta = (Bitmask, BitmaskEnum = "TILE_WALL_STATE"))
	int32 mWallStateint;

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

	UFUNCTION(BlueprintGetter)
	int32 getStateInt()
	{
		return mWallStateint;
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

	UFUNCTION(BlueprintCallable)
	void WallOff();

	UFUNCTION(BlueprintImplementableEvent)
	void _WallOff();

	UFUNCTION(BlueprintImplementableEvent)
	void _OnWallLeft();

	UFUNCTION(BlueprintImplementableEvent)
		void _OnWallRight();

	UFUNCTION(BlueprintImplementableEvent)
		void _OnWallTop();

	UFUNCTION(BlueprintImplementableEvent)
		void _OnWallBottom();

};
