#include "stdafx.h"
#include "Background.h"
#include "resource.h"

CBackground::CBackground()
:run(0)
{
}

CBackground::~CBackground()
{
}

void CBackground::draw(CDC* pDC)
{
	run += 1;
	if (run > 850)
		run = 0;
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BACKGROUND1);

	CDC mDC;
	mDC.CreateCompatibleDC(pDC);
	mDC.SelectObject(bmp);
	pDC->BitBlt(0, run, 550, 850 - run, &mDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, 550, run, &mDC, 0, 850 - run, SRCCOPY);
	mDC.DeleteDC();

}
