// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engineminimal.h"
#include "../ProceduralMap.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALMAP_API ATile : public AActor
{
	GENERATED_BODY()
public:
	FVector Pos;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_TileBox;

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

public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void WallOff();

};
