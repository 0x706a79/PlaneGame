#pragma once
#include "GameObject.h"
class CEnemyboss1 :
	public CGameObject
{
public:
	CEnemyboss1(void);
	~CEnemyboss1(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYBOSS1_WIDETH, m_ptPos.y + ENEMYBOSS1_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	BOOL Fired();
private:
	static const int ENEMYBOSS1_HEIGHT = 120;
	static const int ENEMYBOSS1_WIDETH = 190;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex1;
	//速度
	int m_V1;
	int    m_nWait1;//发射延时
	int x1;
public:
	int HPBOSS1;//BOSS血量
};

