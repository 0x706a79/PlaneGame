#include "stdafx.h"
#include "Newbomb.h"
#include "resource.h"

CImageList CNewbomb::m_Images;

CNewbomb::CNewbomb()
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - NEWBOMB_HEIGHT) + 1;
	//���ȷ��ͼ������
	m_nImgIndex = 0;
	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -NEWBOMB_HEIGHT;
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;
}

CNewbomb::~CNewbomb(void)
{
}
BOOL CNewbomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_NEWBOMB, RGB(255, 255, 255), 25, 25, 1);
}
BOOL CNewbomb::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}
	if (m_ptPos.y > GAME_HEIGHT + NEWBOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -NEWBOMB_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}