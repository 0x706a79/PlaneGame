#pragma once
#include "GameObject.h"
class CNewbomb :
	public CGameObject
{
public:
	CNewbomb(void);
	~CNewbomb(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + NEWBOMB_HEIGHT, m_ptPos.y + NEWBOMB_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int NEWBOMB_HEIGHT = 25;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
};

