#pragma once
#include "GameObject.h"
class CAtom :
	public CGameObject
{
public:
	CAtom(void);
	~CAtom(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ATOM_HEIGHT, m_ptPos.y + ATOM_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int ATOM_HEIGHT = 40;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
};

