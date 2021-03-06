#pragma once
#include "GameObject.h"

class CMe :public CGameObject
{
public:
	CMe(void);
	~CMe(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + PLANE_WIDTH, m_ptPos.y + PLANE_HEIGHT));
	}

	//是否可以开火发射导弹
	BOOL Fired();

	//设置坐标
	void SetPoint(int,int);

	//无敌模式
	void WhosYourDaddy(BOOL);
	void WZH();
	BOOL IsNoEnemy();
	BOOL IsRealNoEnemy();
	//获取子弹类型
	int GetBullet()
	{
		return m_nBullet;
	}

	void SetBullet(int type)
	{
		m_nBullet = type;
	}

public:
	static const int PLANE_WIDTH = 50;
	static const int PLANE_HEIGHT = 60;
private:

	static CImageList m_Images;
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
	int    m_nWait;//发射延时
	BOOL   m_bNoEnemy;
	BOOL   m_bRealNoEnemy;
	int	   m_nCount;//无敌时间
	int    m_nBullet = 0;//子弹类型
};