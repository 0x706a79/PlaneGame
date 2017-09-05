#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"

CImageList CBomb::m_Images;
CImageList CBomb::m_Images1;
int CBomb::BombType = 0;
int CBomb::changeTime;

CBomb::CBomb(int x,int y):CGameObject(x,y)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	BombType = 0;
	CGameObject::LoadImage(m_Images, IDB_BOMB, RGB(0, 0, 0), 10, 20, 1);
	CGameObject::LoadImage(m_Images1, IDB_NEWBOMB, RGB(255, 255, 255), 25, 25, 1);
	return true;
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if (GetTickCount() - changeTime > 20000)//�����������ڵ�ʱ�䣬�������
	{
		BombType = 0;
	}
	if(!bPause)
	{
		switch (BombType)
		{
		case 0:
			m_ptPos.y -= 8;
			m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);//ָʾλ�ã��������ε�ͼ��͸����ͼ
			break;
		case 1:
			m_ptPos.y -= 11;
			m_ptPos.x += toward * 3;
			m_Images1.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
			break;
		}
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
void CBomb::ChangeType(int n, int Time)//PlaneGameView�б任�ӵ�
{
	changeTime = Time;
	BombType = n;
}