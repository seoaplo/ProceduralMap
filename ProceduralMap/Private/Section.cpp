// Fill out your copyright notice in the Description page of Project Settings.


#include "Section.h"
#include "CreateMapByBSP.h"

// Sets default values
ASection::ASection()
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
void ASection::CreateRoom(UCreateMapByBSP* BSPMap, FVector StartTile, FVector EndTile, int Percent)
{
	if (nullptr == BSPMap)
	{
		return;
	}

	reset();

	FVector StartPos = GetTransform().GetLocation();
	mRoom = GetWorld()->SpawnActor<ARoom>(ARoom::StaticClass(), StartPos, FRotator::ZeroRotator);

	if (nullptr == mRoom)
	{
		return;
	}
	
	FVector CorrectionTileNum = EndTile - StartTile;
	CorrectionTileNum.X = ceil(CorrectionTileNum.X * (100 - Percent) * 0.005);
	CorrectionTileNum.Y = ceil(CorrectionTileNum.Y * (100 - Percent) * 0.005);

	StartTile += CorrectionTileNum;
	EndTile -= CorrectionTileNum;

	mRoom->CreateRoom(BSPMap, StartTile, EndTile);
	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

	mRoom->AttachToActor(this, AttachmentTransformRules);
}
void ASection::reset()
{
	if (nullptr != mRoom)
	{
		mRoom->reset();
		mRoom->Destroy();
		mRoom = nullptr;
	}
}
// Called when the game starts or when spawned
void ASection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

