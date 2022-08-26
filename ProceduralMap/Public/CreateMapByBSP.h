// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Section.h"
#include "Path.h"
#include "Components/ActorComponent.h"
#include "Floor.h"
#include "CreateMapByBSP.generated.h"

UCLASS( ClassGroup=(Custom), Blueprintable,  meta=(BlueprintSpawnableComponent) )
class PROCEDURALMAP_API UCreateMapByBSP : public UActorComponent
{
	GENERATED_BODY()
private:
	BSP_Tree	mBSP;

	USceneComponent* mRoot;
	std::vector<Floor>	mFloorArray;
	TArray<ASection*> mLeafNodeSection;
	TArray<APath*> mPathActorArray;
	FVector mTileSize;

	int m_MaxSize;
	int m_MinimumSize;
	int m_RatioStart;
	int m_RatioEnd;
	int m_MaxCutNum;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ATile> mTileClass;
public:
	void reset();

	Floor* getFloor(int Index)
	{
		if (Index < mFloorArray.size())
		{
			return &mFloorArray[Index];
		}
		return nullptr;
	}

	Floor* getFloor(FVector Pos)
	{
		int Index = Pos.X + (getColNum() * Pos.Y);
		if (Index < mFloorArray.size())
		{
			return &mFloorArray[Index];
		}
		return nullptr;
	}

	TSubclassOf<ATile> gerTileClass()
	{
		return mTileClass;
	}

	const FVector& getTileSize()
	{
		return mTileSize;
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
