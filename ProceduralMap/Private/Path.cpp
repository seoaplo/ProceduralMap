// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "CreateMapByBSP.h"

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

	StartPos = StartTile->getPos();
	EndPos = EndTile->getPos();

	FVector TileNum = EndPos - StartPos;

	TileNum.X = abs(TileNum.X);
	TileNum.Y = abs(TileNum.Y);

	int SpawnNumX = ceil(TileNum.X * 0.5f);
	int SpawnNumY = ceil(TileNum.Y * 0.5f);

	m_vecTile.resize(TileNum.X + (BSPMap->getColNum() * TileNum.Y));

	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	if (TileNum.X > TileNum.Y)
	{
		int CorrectionPosX = 0;

		for (int i = 0; i < SpawnNumX; ++i)
		{
			CorrectionPosX = StartPos.X < EndPos.X ? (i + 1) : -(i + 1);

			FVector FrontPos = StartPos + FVector(CorrectionPosX, 0, 0);
			FVector BackPos = EndPos - FVector(CorrectionPosX, 0, 0);

			ATile* FrontTile = BSPMap->getTile(FrontPos);
			if (nullptr == FrontTile)
			{
				continue;
			}

			FrontTile->WallOff();
			m_vecTile[i] = FrontTile;
			FrontTile->AttachToActor(this, AttachmentTransformRules);

			ATile* BackTile = BSPMap->getTile(BackPos);
			if (nullptr == BackTile)
			{
				continue;
			}
			BackTile->WallOff();
			m_vecTile[m_vecTile.size() - i - 1] = BackTile;
			BackTile->AttachToActor(this, AttachmentTransformRules);
		}

		int CorrectionPosY = 0;

		for (int i = 0; i < SpawnNumY; ++i)
		{
			CorrectionPosY = StartPos.Y < EndPos.Y ? (i + 1) : -(i + 1);

			FVector FrontPos = StartPos + FVector(CorrectionPosX, CorrectionPosY, 0);
			FVector BackPos = EndPos - FVector(CorrectionPosX, CorrectionPosY, 0);

			ATile* FrontTile = BSPMap->getTile(FrontPos);
			if (nullptr == FrontTile)
			{
				continue;
			}

			FrontTile->WallOff();
			m_vecTile[SpawnNumX + i] = FrontTile;
			FrontTile->AttachToActor(this, AttachmentTransformRules);

			ATile* BackTile = BSPMap->getTile(BackPos);
			if (nullptr == BackTile)
			{
				continue;
			}
			BackTile->WallOff();
			m_vecTile[m_vecTile.size() - SpawnNumX - i] = BackTile;
			BackTile->AttachToActor(this, AttachmentTransformRules);
		}
	}
	else
	{
		int CorrectionPosY = 0;

		for (int i = 0; i < SpawnNumY; ++i)
		{
			CorrectionPosY = StartPos.Y < EndPos.Y ? (i + 1) : -(i + 1);

			FVector FrontPos = StartPos + FVector(0, CorrectionPosY, 0);
			FVector BackPos = EndPos - FVector(0, CorrectionPosY, 0);

			ATile* FrontTile = BSPMap->getTile(FrontPos);
			if (nullptr == FrontTile)
			{
				continue;
			}

			FrontTile->WallOff();
			m_vecTile[i] = FrontTile;
			FrontTile->AttachToActor(this, AttachmentTransformRules);

			ATile* BackTile = BSPMap->getTile(BackPos);
			if (nullptr == BackTile)
			{
				continue;
			}
			BackTile->WallOff();
			m_vecTile[m_vecTile.size() - i - 1] = BackTile;
			BackTile->AttachToActor(this, AttachmentTransformRules);
		}

		int CorrectionPosX = 0;

		for (int i = 0; i < SpawnNumX; ++i)
		{
			CorrectionPosX = StartPos.X < EndPos.X ? (i + 1) : -(i + 1);

			FVector FrontPos = StartPos + FVector(CorrectionPosX, CorrectionPosY, 0);
			FVector BackPos = EndPos - FVector(CorrectionPosX, CorrectionPosY, 0);

			ATile* FrontTile = BSPMap->getTile(FrontPos);
			if (nullptr == FrontTile)
			{
				continue;
			}

			FrontTile->WallOff();
			m_vecTile[SpawnNumY + i] = FrontTile;
			FrontTile->AttachToActor(this, AttachmentTransformRules);

			ATile* BackTile = BSPMap->getTile(BackPos);
			if (nullptr == BackTile)
			{
				continue;
			}
			BackTile->WallOff();
			m_vecTile[m_vecTile.size() - SpawnNumY - i] = BackTile;
			BackTile->AttachToActor(this, AttachmentTransformRules);
		}
	}
}
void APath::CreatePath(UCreateMapByBSP* BSPMap, ARoom* Start, APath* End)
{

}
void APath::CreatePath(UCreateMapByBSP* BSPMap, APath* Start, APath* End)
{

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

