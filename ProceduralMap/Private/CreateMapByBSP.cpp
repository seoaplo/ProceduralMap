// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateMapByBSP.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCreateMapByBSP::UCreateMapByBSP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...

	mRoot = CreateDefaultSubobject<USceneComponent>(FName("Root"));
}


// Called when the game starts
void UCreateMapByBSP::BeginPlay()
{
	Super::BeginPlay();
	reset();
}
void UCreateMapByBSP::process(int MaxSize, int MinimumSize, int RatioStart, int RatioEnd, int MaxCutNum)
{
	if (nullptr == mRoot)
	{
		return;
	}

	m_MaxSize = MaxSize;
	m_MinimumSize = MinimumSize;
	m_RatioStart = RatioStart;
	m_RatioEnd = RatioEnd;
	m_MaxCutNum = MaxCutNum;

	UWorld* World = GetWorld();
	if (nullptr == World)
	{
		return;
	}

	if (nullptr == mTileClass)
	{
		return;
	}

	ATile* SpawnBasicTile = GetWorld()->SpawnActor<ATile>(mTileClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr == SpawnBasicTile)
	{
		return;
	}
	mTileSize = SpawnBasicTile->getTileScale();
	SpawnBasicTile->Destroy();

	reset();
	CreateBSP();



	mFloorArray.resize(m_MaxSize * m_MaxSize);
	for (int RowIndex = 0; RowIndex < mBSP.getRowNum(); ++RowIndex)
	{
		for (int ColIndex = 0; ColIndex < mBSP.getColNum(); ++ColIndex)
		{
			FVector SpawnPos = FVector(ColIndex * mTileSize.X, RowIndex * mTileSize.Y, 0);
			int index = (RowIndex * m_MaxSize) + ColIndex;

			if (mFloorArray.size() <= index)
			{
				return;
			}

			mFloorArray[index].Init(SpawnPos, FVector(ColIndex, RowIndex, 0), mTileClass);
		}
	}




	std::vector<BSP_Node*>& NodeArray = mBSP.getLeafNodePtrArray();
	
	for (auto iter = NodeArray.begin(); iter != NodeArray.end(); ++iter)
	{
		if (nullptr == *iter)
		{
			break;
		}

		ASection* SpawnSection = GetWorld()->SpawnActor<ASection>(ASection::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

		if (nullptr == SpawnSection)
		{
			continue;
		}

		FVector StartTileNum = FVector((*iter)->mBox2D.Min.X, (*iter)->mBox2D.Min.Y, 0);
		FVector EndTileNum = FVector((*iter)->mBox2D.Max.X, (*iter)->mBox2D.Max.Y, 0);


		SpawnSection->CreateRoom(this, StartTileNum, EndTileNum, 70);

		(*iter)->mActorPtr = SpawnSection;
		const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		SpawnSection->AttachToComponent(mRoot, AttachmentTransformRules); 
		mLeafNodeSection.Add(SpawnSection);
	}

	for (int i = 0; i < mLeafNodeSection.Num(); i = ++i)
	{
		APath* SpawnPath = GetWorld()->SpawnActor<APath>(APath::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr == SpawnPath)
		{
			continue;
		}

		int FirstIndex = std::min(i, static_cast<int>(mLeafNodeSection.Num() - 1));
		int SecontIndex = std::min(i + 1, static_cast<int>(mLeafNodeSection.Num() - 1));

		if (nullptr != mLeafNodeSection[FirstIndex] && nullptr != mLeafNodeSection[SecontIndex])
		{
			SpawnPath->CreatePath(this, mLeafNodeSection[FirstIndex]->getRoom(), mLeafNodeSection[SecontIndex]->getRoom());
		}
	}
}

void UCreateMapByBSP::reset()
{
	mBSP.reset();
	for (auto iter = mLeafNodeSection.begin(); iter != mLeafNodeSection.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}

	for (auto iter = mPathActorArray.begin(); iter != mPathActorArray.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}
	mPathActorArray.Reset();

}

// Called every frame
void UCreateMapByBSP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCreateMapByBSP::CreateBSP()
{
	FVector2D maxSize;
	maxSize.X = m_MaxSize;
	maxSize.Y = m_MaxSize;

	FVector2D minimumSize;
	minimumSize.X = m_MinimumSize;
	minimumSize.Y = m_MinimumSize;

	mBSP.CreateBSP(maxSize, minimumSize, m_RatioStart, m_RatioEnd, m_MaxCutNum);
}