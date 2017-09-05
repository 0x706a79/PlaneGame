#pragma once
#include "GameObject.h"
class CAtom :
	public CGameObject
{
public:
	CAtom(void);
	~CAtom(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ATOM_HEIGHT, m_ptPos.y + ATOM_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int ATOM_HEIGHT = 40;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
};

