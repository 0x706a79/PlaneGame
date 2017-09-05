#pragma once
#include "GameObject.h"

class CBallboss :
	public CGameObject
{
public:
	CBallboss(int x, int y, int nMontion);
	~CBallboss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALLBOSS_HEIGHT, m_ptPos.y + BALLBOSS_HEIGHT));
	}
private:
	static const int BALLBOSS_HEIGHT = 112;
	static CImageList m_Images;
	int    m_nMotion;
};

