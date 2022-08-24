// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <vector>


namespace Math
{
	struct Pos
	{
		int x;
		int y;
		Pos()
		{
			x = UINT_MAX;
			y = UINT_MAX;
		}
		Pos(const Pos& _Pos)
		{
			*this = _Pos;
		}

		void resetZero()
		{
			x = 0;
			y = 0;
		}
		const Pos& operator=(const Pos& _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;

			return *this;
		}
		const Pos operator+(const Pos& _Pos)
		{
			Pos Ret;
			Ret.x = x + _Pos.x;
			Ret.y = y + _Pos.y;

			return Ret;
		}

		const Pos& operator+=(const Pos& _Pos)
		{
			*this = *this + _Pos;

			return *this;
		}
	};

	struct Rect
	{
		Pos m_Pos;
		Pos m_EndPos;
		Pos m_Size;

		void AddPos(const Pos& _Pos)
		{
			m_Pos += _Pos;
			m_EndPos += _Pos;
		}

		void AddPos(const int& _x, const int& _y)
		{
			Pos pos;
			pos.resetZero();
			pos.x = _x;
			pos.y = _y;

			AddPos(pos);
		}


		void AddSize(const Pos& _Size)
		{
			m_EndPos += _Size;
			m_Size += _Size;
		}

		void AddSize(const int& _x, const int& _y)
		{
			Pos size;
			size.resetZero();
			size.x += _x;
			size.y += _y;

			AddSize(size);
		}

		void resetZero()
		{
			m_Pos.resetZero();
			m_EndPos.resetZero();
			m_Size.resetZero();
		}

		Rect()
		{

		}
		Rect(const Rect& _Rect)
		{
			*this = _Rect;
		}

		const Rect& operator=(const Rect& _Rect)
		{
			m_Pos = _Rect.m_Pos;
			m_Size = _Rect.m_Size;
			m_EndPos = _Rect.m_EndPos;

			return *this;
		}
	};
}

class BSP_Node
{
public:
	Math::Rect m_Rect;

public:
	BSP_Node()
	{
		return;
	}
	BSP_Node(const Math::Rect& _Rect)
	{
		m_Rect = _Rect;
	}
};

class BSP_Tree
{
private:
	std::map<int, BSP_Node> m_Map;
	std::vector<BSP_Node*> m_vecLeafNodeList;

	Math::Pos	m_MaxSize;
	Math::Pos	m_MinimumSize;

	int			m_RatioStart;
	int			m_RatioEnd;
	int			m_CutNum;
	int			m_CutCount;

	int			m_Quantity;

public:
	void CreateBSP(const Math::Pos& _MaxSize, const Math::Pos& _MinimunSize, const int& _RatioStart, const int& _RatioEnd, const int& _CutNum);
	void Process();
	bool CutNode(int ParentNum, int CutCount);
	void reset();
public:
	const BSP_Node* const getNode(int Num);
	int getQuantity() const
	{
		return m_Quantity;
	}
	const std::map<int, BSP_Node>& getMap() const
	{
		return m_Map;
	}
	const std::vector<BSP_Node*>& getLeafList() const
	{
		return m_vecLeafNodeList;
	}
	int getSize()
	{
		return m_MaxSize.x * m_MaxSize.y;
	}
	int getColNum()
	{
		return m_MaxSize.x;
	}
	int getRowNum()
	{
		return m_MaxSize.y;
	}
public:
	BSP_Tree();
	~BSP_Tree();
};