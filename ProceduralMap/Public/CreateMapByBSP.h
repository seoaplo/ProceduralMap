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
	BSP_Tree	mBSP;
	
	USceneComponent* mRoot;
	TArray<ASection*> mLeafNodeSection;
	TArray<APath*> mPathActorArray;
	TArray<ATile*> mTileArray;

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
		if (Index < mTileArray.Num())
		{
			return mTileArray[Index];
		}
		return nullptr;
	}

	ATile* getTile(FVector Pos)
	{
		int Index = Pos.X + (getColNum() * Pos.Y);
		if (Index < mTileArray.Num())
		{
			return mTileArray[Index];
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
		return FVector(mBSP.getColNum(), mBSP.getRowNum(), 0);
	}

	int getColNum()
	{
		return mBSP.getColNum();
	}

	int getRowNum()
	{
		return mBSP.getRowNum();
	}

};
