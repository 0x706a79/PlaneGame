#pragma once
#include "GameObject.h"
class CNewbomb :
	public CGameObject
{
public:
	CNewbomb(void);
	~CNewbomb(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + NEWBOMB_HEIGHT, m_ptPos.y + NEWBOMB_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int NEWBOMB_HEIGHT = 25;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
};

