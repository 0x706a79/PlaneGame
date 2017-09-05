#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+10,m_ptPos.y+BOMB_HEIGHT));
	}

	int toward;

	static int BombType;
	static void ChangeType(int n,int changeTime);

private:
	static const int BOMB_HEIGHT = 20;
	static const int m_nWait = 5000;
	static int changeTime;
	static CImageList m_Images, m_Images1;

};
