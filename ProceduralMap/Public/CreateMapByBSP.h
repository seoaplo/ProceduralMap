// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Section.h"
#include "Path.h"
#include "Components/ActorComponent.h"
#include "CreateMapByBSP.generated.h"

UCLASS( ClassGroup=(Custom), Blueprintable,  meta=(BlueprintSpawnableComponent) )
class PROCEDURALMAP_API UCreateMapByBSP : public UActorComponent
{
	GENERATED_BODY()
private:
	BSP_Tree	m_BSP;
	std::vector<ASection*> m_vecSection;
	std::vector<APath*> m_vecPath;
	std::vector<ATile*> m_vecTile;

	int m_MaxSize;
	int m_MinimumSize;
	int m_RatioStart;
	int m_RatioEnd;
	int m_MaxCutNum;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ATile> Tile;
public:
	void reset();
	ATile* getTile(int Index)
	{
		if (Index < m_vecTile.size())
		{
			return m_vecTile[Index];
		}
		return nullptr;
	}

	ATile* getTile(FVector Pos)
	{
		int Index = Pos.X + (getColNum() * Pos.Y);
		if (Index < m_vecTile.size())
		{
			return m_vecTile[Index];
		}
		return nullptr;
	}

public:	
	// Sets default values for this component's properties
	UCreateMapByBSP();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void process(int MaxSize, int MinimumSize, int RatioStart, int RatioEnd, int MaxCutNum);
public:
	void CreateBSP();
	FVector getTileNum()
	{
		return FVector(m_BSP.getColNum(), m_BSP.getRowNum(), 0);
	}

	int getColNum()
	{
		return m_BSP.getColNum();
	}

	int getRowNum()
	{
		return m_BSP.getRowNum();
	}

};
