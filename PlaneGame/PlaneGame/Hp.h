#pragma once
#include "GameObject.h"
class CHp :
	public CGameObject
{
public:
	CHp(void);
	~CHp(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + HP_HEIGHT, m_ptPos.y + HP_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int HP_HEIGHT = 20;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
};

