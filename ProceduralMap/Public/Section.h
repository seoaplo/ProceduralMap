// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Room.h"
#include "GameFramework/Actor.h"
#include "Section.generated.h"

class UCreateMapByBSP;

UCLASS()
class PROCEDURALMAP_API ASection : public AActor
{
	GENERATED_BODY()
private:
	ARoom* m_Room;

public:	
	// Sets default values for this actor's properties
	void CreateRoom(UCreateMapByBSP* BSPMap, FVector StartTile, FVector EndTile, int Percent);
	void reset();
	ASection();
	const ARoom* const getRoom()
	{
		return m_Room;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
