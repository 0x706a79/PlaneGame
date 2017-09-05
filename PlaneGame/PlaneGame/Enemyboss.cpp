#include "stdafx.h"
#include "Enemyboss.h"
#include "resource.h"

CImageList CEnemyboss::m_Images;

CEnemyboss::CEnemyboss(void)
: HPBOSS(300)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMYBOSS_WIDETH) + 1;
	
	//随机确定图像索引
	m_nImgIndex =rand()%1;
	
	//根据图像索引确定方向
	m_nMotion = 1;
	
	//随机确定速度
	m_V = 2;
	m_nWait = 0;
}


CEnemyboss::~CEnemyboss()
{
}


BOOL CEnemyboss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 10)
		m_nWait = 0;


	CBrush bru;
	bru.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(bru);
	pDC->Rectangle(m_ptPos.x + HPBOSS, m_ptPos.y - 20, m_ptPos.x - 20, m_ptPos.y - 10);

	if (!bPause)
	{
		if (m_ptPos.y<=120)
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		m_ptPos.x = m_ptPos.x + x;
	}

	if (m_ptPos.x <= 0)
	{
		m_ptPos.x = 0;
		x = 1;
	}

	if (m_ptPos.x >= GAME_WIDTH - ENEMYBOSS_HEIGHT - 15)
	{
		m_ptPos.x = GAME_WIDTH - ENEMYBOSS_HEIGHT - 15;
		x = -1;
	}

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL CEnemyboss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMYBOSS, RGB(255, 255, 255), 260, 197, 2);
}

BOOL CEnemyboss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
