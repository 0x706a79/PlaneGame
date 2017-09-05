#include "stdafx.h"
#include "Enemyboss1.h"
#include "resource.h"

CImageList CEnemyboss1::m_Images;

CEnemyboss1::CEnemyboss1(void)
: HPBOSS1(800)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMYBOSS1_WIDETH) + 1;

	//���ȷ��ͼ������
	m_nImgIndex1 = rand() % 1;

	//����ͼ������ȷ������
	m_nMotion = 1;

	//���ȷ���ٶ�
	m_V1 = 2;
	m_nWait1 = 0;
}


CEnemyboss1::~CEnemyboss1()
{

}

BOOL CEnemyboss1::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait1++;
	if (m_nWait1 > 10)
		m_nWait1 = 0;


	CBrush bru;
	bru.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(bru);
	pDC->Rectangle(m_ptPos.x + HPBOSS1 - 260, m_ptPos.y - 20, m_ptPos.x - 260, m_ptPos.y - 10);

	if (!bPause)
	{
		if (m_ptPos.y <= 120)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V1;
		m_ptPos.x = m_ptPos.x + x1;
	}

	if (m_ptPos.x <= 0)
	{
		m_ptPos.x = 0;
		x1 = 1;
	}

	if (m_ptPos.x >= GAME_WIDTH - ENEMYBOSS1_HEIGHT - 15)
	{
		m_ptPos.x = GAME_WIDTH - ENEMYBOSS1_HEIGHT - 15;
		x1 = -1;
	}

	m_Images.Draw(pDC, m_nImgIndex1, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL CEnemyboss1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMYBOSS1, RGB(0, 0, 0), 190, 120, 2);
}

BOOL CEnemyboss1::Fired()
{
	if (m_nWait1 == 0)
		return TRUE;
	else
		return FALSE;
}
