// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "CreateMapByBSP.h"
#include "Floor.h"

// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (nullptr == RootComponent)
	{
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
		if (nullptr != Box)
		{
			RootComponent = Box;
		}
	}

}

void APath::CreatePath(UCreateMapByBSP* BSPMap, const ARoom* const Start, const ARoom* const End)
{
	if (nullptr == RootComponent)
	{
		return;
	}
	if (nullptr == Start)
	{
		return;
	}
	if (nullptr == End)
	{
		return;
	}
	if (Start == End)
	{
		return;
	}
	if (nullptr == BSPMap)
	{
		return;
	}
	mBSPMap = BSPMap;

	reset();

	const ATile* const StartTile = Start->getCenterTile();
	if (nullptr == StartTile)
	{
		return;
	}

	const ATile* const EndTile = End->getCenterTile();
	if (nullptr == EndTile)
	{
		return;
	}

	mStartPos = StartTile->getPos();
	mEndPos = EndTile->getPos();

	FVector TileNum = mEndPos - mStartPos;

	TileNum.X = abs(TileNum.X);
	TileNum.Y = abs(TileNum.Y);

	int SpawnNumX = ceil(TileNum.X * 0.5f);
	int SpawnNumY = ceil(TileNum.Y * 0.5f);

	m_vecTile.resize(TileNum.X + (BSPMap->getColNum() * TileNum.Y));

	int CorrectionPosX = 0;
	int CorrectionPosY = 0;

	if (TileNum.X > TileNum.Y)
	{
		CreatePathDerectionX(SpawnNumX, 0, CorrectionPosX, CorrectionPosY);
		CreatePathDerectionY(SpawnNumX, SpawnNumY, CorrectionPosX, CorrectionPosY);
	}
	else
	{
		CreatePathDerectionY(0, SpawnNumY, CorrectionPosX, CorrectionPosY);
		CreatePathDerectionX(SpawnNumX, SpawnNumY, CorrectionPosX, CorrectionPosY);
	}
}
void APath::CreatePath(UCreateMapByBSP* BSPMap, ARoom* Start, APath* End)
{

}
void APath::CreatePath(UCreateMapByBSP* BSPMap, APath* Start, APath* End)
{

}

void APath::CreatePathDerectionX(int spawnNumX, int spawnNumY, int& correntPosX, int& correntPosY)
{
	if (nullptr == mBSPMap)
	{
		return;
	}

	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

	for (int i = 0; i < spawnNumX; ++i)
	{
		correntPosX = mStartPos.X < mEndPos.X ? (i + 1) : -(i + 1);

		FVector FrontPos = mStartPos + FVector(correntPosX, correntPosY, 0);
		FVector BackPos = mEndPos - FVector(correntPosX, correntPosY, 0);

		Floor* MainRoadFloor = mBSPMap->getFloor(FrontPos);
		if (nullptr == MainRoadFloor)
		{
			continue;
		}

		ATile* MainRoadTile = MainRoadFloor->spwanTile(GetWorld());
		if (nullptr == MainRoadTile)
		{
			continue;
		}

		MainRoadTile->WallOff();
		m_vecTile[spawnNumY + i] = MainRoadTile;
		MainRoadTile->AttachToActor(this, AttachmentTransformRules);


		MainRoadFloor = mBSPMap->getFloor(BackPos);
		if (nullptr == MainRoadFloor)
		{
			continue;
		}

		MainRoadTile = MainRoadFloor->spwanTile(GetWorld());
		if (nullptr == MainRoadTile)
		{
			continue;
		}

		MainRoadTile->WallOff();
		m_vecTile[m_vecTile.size() - spawnNumX - i] = MainRoadTile;
		MainRoadTile->AttachToActor(this, AttachmentTransformRules);
	}
}
void APath::CreatePathDerectionY(int spawnNumX, int spawnNumY, int& correntPosX, int& correntPosY)
{
	if (nullptr == mBSPMap)
	{
		return;
	}

	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

	for (int i = 0; i < spawnNumY; ++i)
	{
		correntPosY = mStartPos.Y < mEndPos.Y ? (i + 1) : -(i + 1);

		FVector FrontPos = mStartPos + FVector(correntPosX, correntPosY, 0);
		FVector BackPos = mEndPos - FVector(correntPosX, correntPosY, 0);

		Floor* MainRoadFloor = mBSPMap->getFloor(FrontPos);
		if (nullptr == MainRoadFloor)
		{
			continue;
		}

		ATile* MainRoadTile = MainRoadFloor->spwanTile(GetWorld());
		if (nullptr == MainRoadTile)
		{
			continue;
		}

		MainRoadTile->WallOff();
		m_vecTile[spawnNumX + i] = MainRoadTile;
		MainRoadTile->AttachToActor(this, AttachmentTransformRules);

		MainRoadFloor = mBSPMap->getFloor(BackPos);
		if (nullptr == MainRoadFloor)
		{
			continue;
		}

		MainRoadTile = MainRoadFloor->spwanTile(GetWorld());
		if (nullptr == MainRoadTile)
		{
			continue;
		}
		MainRoadTile->WallOff();
		m_vecTile[m_vecTile.size() - i - 1] = MainRoadTile;
		MainRoadTile->AttachToActor(this, AttachmentTransformRules);
	}
}

void APath::reset()
{
	for (auto iter = m_vecTile.begin(); iter != m_vecTile.end(); ++iter)
	{
		if (nullptr != (*iter))
		{
			(*iter)->Destroy();
		}
	}
}


// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

