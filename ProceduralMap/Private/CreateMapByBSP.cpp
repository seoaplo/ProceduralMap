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
}


// Called when the game starts
void UCreateMapByBSP::BeginPlay()
{
	Super::BeginPlay();
	reset();
}
void UCreateMapByBSP::process(int MaxSize, int MinimumSize, int RatioStart, int RatioEnd, int MaxCutNum)
{
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

	if (nullptr == Tile)
	{
		return;
	}

	ATile* SpawnBasicTile = GetWorld()->SpawnActor<ATile>(Tile, FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr == SpawnBasicTile)
	{
		return;
	}

	reset();
	CreateBSP();

	FVector TileSize = SpawnBasicTile->getTileScale();

	for (int RowIndex = 0; RowIndex < m_BSP.getRowNum(); ++RowIndex)
	{
		for (int ColIndex = 0; ColIndex < m_BSP.getColNum(); ++ColIndex)
		{
			FVector SpawnPos = FVector(ColIndex * TileSize.X, RowIndex * TileSize.Y, 0);
			ATile* SpawnTile = GetWorld()->SpawnActor<ATile>(Tile, SpawnPos, FRotator::ZeroRotator);

			if (nullptr == SpawnTile)
			{
				continue;
			}
			SpawnTile->SetPos(FVector(ColIndex, RowIndex, 0));
			m_vecTile.push_back(SpawnTile);
		}
	}

	auto& vecList = m_BSP.getLeafList();
	for (auto iter = vecList.begin(); iter != vecList.end(); ++iter)
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

		FVector StartTileNum = FVector((*iter)->m_Rect.m_Pos.x, (*iter)->m_Rect.m_Pos.y, 0);
		FVector EndTileNum = FVector((*iter)->m_Rect.m_EndPos.x, (*iter)->m_Rect.m_EndPos.y, 0);

		SpawnSection->CreateRoom(this, StartTileNum, EndTileNum, 90);
		m_vecSection.push_back(SpawnSection);
	}

	for (int i = 0; i < m_vecSection.size(); i = ++i)
	{
		APath* SpawnPath = GetWorld()->SpawnActor<APath>(APath::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr == SpawnPath)
		{
			continue;
		}

		int FirstIndex = std::min(i, static_cast<int>(m_vecSection.size() - 1));
		int SecontIndex = std::min(i + 1, static_cast<int>(m_vecSection.size() - 1));

		if (nullptr != m_vecSection[FirstIndex] && nullptr != m_vecSection[SecontIndex])
		{
			SpawnPath->CreatePath(this, m_vecSection[FirstIndex]->getRoom(), m_vecSection[SecontIndex]->getRoom());
		}
	}

	SpawnBasicTile->Destroy();
}

void UCreateMapByBSP::reset()
{
	m_BSP.reset();
	for (auto iter = m_vecSection.begin(); iter != m_vecSection.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}
	m_vecSection.clear();
	for (auto iter = m_vecTile.begin(); iter != m_vecTile.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}
	m_vecTile.clear();
	for (auto iter = m_vecPath.begin(); iter != m_vecPath.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}
	m_vecPath.clear();

}

// Called every frame
void UCreateMapByBSP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCreateMapByBSP::CreateBSP()
{
	Math::Pos MaxSize;
	MaxSize.x = m_MaxSize;
	MaxSize.y = m_MaxSize;

	Math::Pos MinimumSize;
	MinimumSize.x = m_MinimumSize;
	MinimumSize.y = m_MinimumSize;

	m_BSP.CreateBSP(MaxSize, MinimumSize, m_RatioStart, m_RatioEnd, m_MaxCutNum);
}