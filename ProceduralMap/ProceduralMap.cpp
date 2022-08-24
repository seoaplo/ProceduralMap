// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralMap.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ProceduralMap, "ProceduralMap" );
 

void BSP_Tree::CreateBSP(const FVector2D& maxSize, const FVector2D& minimunSize, const int& ratioStart, const int& ratioEnd, const int& cutNum)
{
	if (0 > ratioStart ||
		ratioStart > ratioEnd ||
		0 >= cutNum)
	{
		return;
	}

	mMaxSize = maxSize;
	mMinimumSize = minimunSize;
	mCutNum = cutNum;
	mRatioStart = ratioStart;
	mRatioEnd = ratioEnd;

	Process();
}

void BSP_Tree::Process()
{

	mQuantity = 0;

	BSP_Node Node;
	Node.mBox2D.Min = FVector2D::ZeroVector;
	Node.mBox2D.Max = mMaxSize;
	Node.mIndex = 0;
	mNodeMap.insert(std::make_pair(Node.mIndex, Node));

	if (true == CutNode(mNodeMap.find(Node.mIndex)->second, 0))
	{
		mQuantity = mNodeMap.size();
	}
}
bool BSP_Tree::CutNode(BSP_Node& parentNode, int CutCount)
{
	if (CutCount >= mCutNum)
	{
		return false;
	}

	BSP_Node ChildNode[2];

	ChildNode[0].mBox2D = parentNode.mBox2D;
	ChildNode[1].mBox2D = parentNode.mBox2D;

	int Ratio = FMath::RandRange(mRatioStart, mRatioEnd);

	if (parentNode.mBox2D.GetSize().X < parentNode.mBox2D.GetSize().Y)
	{
		int FirstNodeY = (parentNode.mBox2D.GetSize().Y / 100.0f) *  Ratio;
		int SecondNodeY = parentNode.mBox2D.GetSize().Y - FirstNodeY;

		ChildNode[0].mBox2D.Max += FVector2D(0, -FirstNodeY);
		ChildNode[1].mBox2D.Min += FVector2D(0, SecondNodeY);
	}
	else
	{
		int FirstNodeX = (parentNode.mBox2D.GetSize().X / 100.0f) * Ratio;
		int SecondNodeX = parentNode.mBox2D.GetSize().X - FirstNodeX;

		ChildNode[0].mBox2D.Max += FVector2D(-FirstNodeX, 0);
		ChildNode[1].mBox2D.Min += FVector2D(SecondNodeX, 0);
	}

	++CutCount;
	bool bHaveChild[2] = { false, false };

	for (int index = 0; index < 2; ++index)
	{
		if (ChildNode[index].mBox2D.GetSize().X > mMinimumSize.X &&
			ChildNode[index].mBox2D.GetSize().Y > mMinimumSize.Y)
		{
			ChildNode[index].mIndex = (parentNode.mIndex * 2) + index + 1;
			ChildNode[index].mParentNodePtr = &parentNode;

			mNodeMap.insert(std::make_pair(ChildNode[index].mIndex, ChildNode[index]));
			bHaveChild[index] = CutNode(mNodeMap.find(ChildNode[index].mIndex)->second, CutCount);
		}
	}

	if (false == bHaveChild[0] &&
		false == bHaveChild[1])
	{
		mLeafNodePtrArray.push_back(&parentNode);
	}

	return true;
}

const BSP_Node* const BSP_Tree::getNode(int Num)
{
	std::map<int, BSP_Node>::iterator Iter = mNodeMap.find(Num);
	if (mNodeMap.end() == Iter)
	{
		return nullptr;
	}
	return &(Iter->second);
}

void BSP_Tree::reset()
{
	mRatioStart = UINT_MAX;
	mRatioEnd = UINT_MAX;
	mCutNum = UINT_MAX;
	mCutCount = UINT_MAX;

	mQuantity = UINT_MAX;

	mNodeMap.clear();
	mLeafNodePtrArray.clear();
}
BSP_Tree::BSP_Tree()
{
	reset();
}

BSP_Tree::~BSP_Tree()
{
	reset();
}