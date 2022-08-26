// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <vector>

class BSP_Node
{
public:
	int		mIndex;
	FBox2D	mBox2D;
	BSP_Node* mParentNodePtr;
	AActor* mActorPtr;

public:
	BSP_Node()
	{
		mIndex = UINT_MAX;
		mActorPtr = nullptr;
		mParentNodePtr = nullptr;
	}
	BSP_Node(const FBox2D& box2D)
	{
		mBox2D = box2D;
	}
};

class BSP_Tree
{
private:
	std::map<int, BSP_Node>	mNodeMap;
	std::vector<BSP_Node*>	mLeafNodePtrArray;

	FVector2D	mMaxSize;
	FVector2D	mMinimumSize;

	int			mRatioStart;
	int			mRatioEnd;
	int			mCutNum;
	int			mCutCount;

	int			mQuantity;

public:
	void CreateBSP(const FVector2D& maxSize, const FVector2D& minimunSize, const int& ratioStart, const int& ratioEnd, const int& cutNum);
	void Process();
	bool CutNode(BSP_Node& parentNode, int CutCount);
	void reset();
public:
	const BSP_Node* const getNode(int Num);
	std::vector<BSP_Node*>& getLeafNodePtrArray()
	{
		return mLeafNodePtrArray;
	}

	int getQuantity() const
	{
		return mQuantity;
	}
	int getSize()
	{
		return mMaxSize.X * mMaxSize.Y;
	}
	int getColNum()
	{
		return mMaxSize.X;
	}
	int getRowNum()
	{
		return mMaxSize.Y;
	}
public:
	BSP_Tree();
	~BSP_Tree();
};