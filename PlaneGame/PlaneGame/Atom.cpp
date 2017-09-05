#include "stdafx.h"
#include "Atom.h"
#include "Bomb.h"
#include "resource.h"

CImageList CAtom::m_Images;

CAtom::CAtom()
{

	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - ATOM_HEIGHT) + 1;

	//���ȷ��ͼ������

	m_nImgIndex = 0;
	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -ATOM_HEIGHT;
	
	//���ȷ���ٶ�
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