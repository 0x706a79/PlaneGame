#include "stdafx.h"
#include "Hp.h"
#include "resource.h"

CImageList CHp::m_Images;

CHp::CHp()
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - HP_HEIGHT) + 1;
	//���ȷ��ͼ������
	m_nImgIndex = 0;
	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -HP_HEIGHT;
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;
}

CHp::~CHp(void)
{
}
BOOL CHp::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_HP, RGB(255, 255, 255), 20, 20, 1);
}
BOOL CHp::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}
	if (m_ptPos.y > GAME_HEIGHT + HP_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -HP_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}