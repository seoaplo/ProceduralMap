// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralMap.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ProceduralMap, "ProceduralMap" );
 

void BSP_Tree::CreateBSP(const Math::Pos& _MaxSize, const Math::Pos& _MinimunSize, const int& _RatioStart, const int& _RatioEnd, const int& _CutNum)
{
	if (0 > _RatioStart ||
		_RatioStart > _RatioEnd ||
		0 > _CutNum)
	{
		return;
	}

	m_MaxSize = _MaxSize;
	m_MinimumSize = _MinimunSize;
	m_CutNum = _CutNum;
	m_RatioStart = _RatioStart;
	m_RatioEnd = _RatioEnd;

	Process();
}

void BSP_Tree::Process()
{

	m_Quantity = 0;

	BSP_Node Node;
	Node.m_Rect.resetZero();
	Node.m_Rect.AddSize(m_MaxSize);

	m_Map.insert(std::make_pair(m_Quantity, Node));

	if (true == CutNode(m_Quantity, 0))
	{
		m_Quantity = m_Map.size();
	}
	
}
bool BSP_Tree::CutNode(int ParentNum, int CutCount)
{
	std::map<int, BSP_Node>::iterator Iter = m_Map.find(ParentNum);
	if (m_Map.end() == Iter ||
		CutCount >= m_CutNum)
	{
		return false;
	}

	BSP_Node& Node = Iter->second;
	BSP_Node FirstChildNode;
	BSP_Node SecondChildNode;

	FirstChildNode.m_Rect = Node.m_Rect;
	SecondChildNode.m_Rect = Node.m_Rect;

	int Ratio = FMath::RandRange(m_RatioStart, m_RatioEnd);

	if (Node.m_Rect.m_Size.x < Node.m_Rect.m_Size.y)
	{
		int FirstNodeY = (Node.m_Rect.m_Size.y / 100.0f) *  Ratio;
		int SecondNodeY = Node.m_Rect.m_Size.y - FirstNodeY;

		FirstChildNode.m_Rect.AddSize(0, -FirstNodeY);
		SecondChildNode.m_Rect.AddSize(0, -SecondNodeY);

		SecondChildNode.m_Rect.AddPos(0, SecondNodeY);
	}
	else
	{
		int FirstNodeX = (Node.m_Rect.m_Size.x / 100.0f) * Ratio;
		int SecondNodeX = Node.m_Rect.m_Size.x - FirstNodeX;

		FirstChildNode.m_Rect.AddSize(-FirstNodeX, 0);
		SecondChildNode.m_Rect.AddSize(-SecondNodeX, 0);

		SecondChildNode.m_Rect.AddPos(SecondNodeX, 0);
	}

	++CutCount;
	bool bIsHaveChild = false;
	if (FirstChildNode.m_Rect.m_Size.x > m_MinimumSize.x &&
		FirstChildNode.m_Rect.m_Size.y > m_MinimumSize.y)
	{
		int iNum = (ParentNum * 2) + 1;
		m_Map.insert(std::make_pair(iNum, FirstChildNode));
		if (true == CutNode(iNum, CutCount))
		{
			bIsHaveChild = true;
		}
	}

	if (SecondChildNode.m_Rect.m_Size.x > m_MinimumSize.x &&
		SecondChildNode.m_Rect.m_Size.y > m_MinimumSize.y)
	{
		int iNum = (ParentNum * 2) + 2;
		m_Map.insert(std::make_pair(iNum, SecondChildNode));
		if (true == CutNode(iNum, CutCount))
		{
			bIsHaveChild = true;
		}
	}

	if (false == bIsHaveChild)
	{
		m_vecLeafNodeList.push_back(&Iter->second);
	}

	return true;
}

const BSP_Node* const BSP_Tree::getNode(int Num)
{
	std::map<int, BSP_Node>::iterator Iter = m_Map.find(Num);
	if (m_Map.end() == Iter)
	{
		return nullptr;
	}
	
	return &(Iter->second);
}

void BSP_Tree::reset()
{
	m_RatioStart = UINT_MAX;
	m_RatioEnd = UINT_MAX;
	m_CutNum = UINT_MAX;
	m_CutCount = UINT_MAX;

	m_Quantity = UINT_MAX;

	m_Map.clear();
	m_vecLeafNodeList.clear();
}
BSP_Tree::BSP_Tree()
{
	reset();
}

BSP_Tree::~BSP_Tree()
{
	reset();
}