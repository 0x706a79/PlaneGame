#include "stdafx.h"
#include "Bossball.h"
#include "resource.h"

CImageList CBossball::m_Images;

CBossball::CBossball(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

CBossball::~CBossball(void)
{
}
BOOL CBossball::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BALLBOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALLBOSS_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBossball::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSBALL, RGB(255, 255, 255), 14, 28, 1);
}
