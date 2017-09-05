#include "stdafx.h"
#include "Atom.h"
#include "Bomb.h"
#include "resource.h"

CImageList CAtom::m_Images;

CAtom::CAtom()
{

	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ATOM_HEIGHT) + 1;

	//随机确定图像索引

	m_nImgIndex = 0;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -ATOM_HEIGHT;
	
	//随机确定速度
	m_V = rand() % 6 + 2;

}

CAtom::~CAtom(void)
{
}
BOOL CAtom::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ATOM, RGB(255, 255, 255), 40, 40, 1);
}
BOOL CAtom::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}
	if (m_ptPos.y > GAME_HEIGHT + ATOM_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -ATOM_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}