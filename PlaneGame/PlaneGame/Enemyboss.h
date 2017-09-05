#pragma once
#include "GameObject.h"

class CEnemyboss :
	public CGameObject
{
public:
	CEnemyboss(void);
	~CEnemyboss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYBOSS_WIDETH, m_ptPos.y + ENEMYBOSS_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	BOOL Fired();
private:
	static const int ENEMYBOSS_HEIGHT = 197;
	static const int ENEMYBOSS_WIDETH = 260;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时
	int x;
public:
	int HPBOSS;//BOSS血量
};

