#pragma once
#include "GameObject.h"

class CBossball :
	public CGameObject
{
public:
	CBossball(int x, int y, int nMontion);
	~CBossball(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALLBOSS_HEIGHT, m_ptPos.y + BALLBOSS_HEIGHT));
	}
private:
	static const int BALLBOSS_HEIGHT = 28;
	static CImageList m_Images;
	int    m_nMotion;
};

