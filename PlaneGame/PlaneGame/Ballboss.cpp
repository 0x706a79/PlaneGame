#include "stdafx.h"
#include "Ballboss.h"
#include "resource.h"

CImageList CBallboss::m_Images;

CBallboss::CBallboss(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

CBallboss::~CBallboss(void)
{
}
BOOL CBallboss::Draw(CDC* pDC, BOOL bPause)
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

BOOL CBallboss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BALLBOSS, RGB(255, 255, 255), 45, 112, 1);
}