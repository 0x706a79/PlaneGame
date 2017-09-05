#include "stdafx.h"
#include "Background1.h"
#include "resource.h"

CBackground1::CBackground1()
:run(0)
{
}

CBackground1::~CBackground1()
{
}

void CBackground1::draw1(CDC* pDC)
{
	run += 1;
	if (run > 850)
		run = 0;
	CBitmap bmp1;
	bmp1.LoadBitmapW(IDB_BACKGROUND2);

	CDC mDC1;
	mDC1.CreateCompatibleDC(pDC);
	mDC1.SelectObject(bmp1);
	pDC->BitBlt(0, run, 550, 850 - run, &mDC1, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, 550, run, &mDC1, 0, 850 - run, SRCCOPY);
	mDC1.DeleteDC();

}