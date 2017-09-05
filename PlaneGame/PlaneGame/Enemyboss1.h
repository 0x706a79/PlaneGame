#pragma once
#include "GameObject.h"
class CEnemyboss1 :
	public CGameObject
{
public:
	CEnemyboss1(void);
	~CEnemyboss1(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYBOSS1_WIDETH, m_ptPos.y + ENEMYBOSS1_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	BOOL Fired();
private:
	static const int ENEMYBOSS1_HEIGHT = 120;
	static const int ENEMYBOSS1_WIDETH = 190;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex1;
	//�ٶ�
	int m_V1;
	int    m_nWait1;//������ʱ
	int x1;
public:
	int HPBOSS1;//BOSSѪ��
};

