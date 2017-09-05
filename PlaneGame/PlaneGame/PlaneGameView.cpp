// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")//��������

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemyboss.h"
#include "Enemyboss1.h"
#include "Bomb.h"
#include "Ball.h"
#include "Setlvl.h"
#include "Ballboss.h"
#include "Bossball.h"
#include "Atom.h"
#include "Hp.h"
#include "Newbomb.h"
#include "Explosion.h"
#include "resource.h"
#include <atlimage.h>
#include "MainFrm.h"

#include "afxwin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static int init;
// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_COMMAND(ID_Start, &CPlaneGameView::OnStart)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_Restart, &CPlaneGameView::OnRestart)
	ON_COMMAND(ID_SETLVL, &CPlaneGameView::OnSetlvl)
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView() :m_pMe(NULL),  Score_Me(0), Lvl_Me(1), Nuke_Me(3)
{
	// TODO: �ڴ˴���ӹ������
}
CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* pMemDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC *m_pMemDC1;//Ϊ��ͼ�ṩ��Ա����
    m_pMemDC1 = new CDC;//Ϊ��ͼ�����ڴ�ռ�
	m_pMemDC1->CreateCompatibleDC(pMemDC);
	CBitmap bmp1;
	bmp1.LoadBitmapW(IDB_START); //����λͼ


	m_pMemDC1->SelectObject(&bmp1);
	pMemDC->BitBlt(0, 0, 550, 850, m_pMemDC1, 0, 0, SRCCOPY);//˫����
	DeleteObject(bmp1);
	delete m_pMemDC1;//�ͷ��ڴ�

	//�������
	CString str = _T("��ӭ�����ɻ���ս���س�����ʼ��Ϸ");
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);

	CString str1 = _T("�ո����ӵ���B�������У���Esc��ͣ/������Ϸ��������������");
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2+25, GAME_HEIGHT / 2+25, str1);

	PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
    // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	//InitGame();
	if (AfxMessageBox(_T("�޵�ģʽ"), MB_YESNO) == 6)
		GOD = 1;
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CEnemyboss::LoadImage();
	CEnemyboss1::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBallboss::LoadImage();
	CHp::LoadImage();
	CBossball::LoadImage();
	CAtom::LoadImage();
	CNewbomb::LoadImage();
	//��������(ս��)
	m_pMe = new CMyPlane;

	//������Ϸ
	SetTimer(1,30,NULL);
	pause = 0;
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{

	CDC mDC;//������ʾ�豸����
	mDC.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	CBitmap bmp;
	//�������
	if (Lvl_Me == 1)
		bmp.LoadBitmapW(IDB_BACKGROUND1);
	else
		bmp.LoadBitmapW(IDB_BACKGROUND2);

	mDC.SelectObject(&bmp);
	m_pMemDC->BitBlt(0, 0, 550, 850, &mDC, 0, speed, SRCCOPY);//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	m_pMemDC->BitBlt(0, 0, 550, 850, &mDC, 0, speed + 850, SRCCOPY);
	speed -= 1;
	if (speed <= -850)
		speed = 0;


	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);

	   pMemDC->SetBkMode(TRANSPARENT);//�������ֱ���͸��
	   wsprintf(lifeleft, L"����ֵ:%d   ʣ������:%d", m_pMe->HPNum_Me, m_pMe->lifeNum_Me);
	   pMemDC->SetTextColor(RGB(0, 108, 155));//����������ɫ
	   pMemDC->TextOutW(10, 10, lifeleft, _tcslen(lifeleft));
	   wsprintf(Score, L"�÷�:%d", Score_Me);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(10, 35, Score, _tcslen(Score));
	   wsprintf(Lvl, L"�ؿ�:%d", Lvl_Me);
	   pMemDC->SetTextColor(RGB(137, 50, 66));
	   pMemDC->TextOutW(10, 60, Lvl, _tcslen(Lvl));
	   wsprintf(Nuke, L"����:%d", Nuke_Me);
	   pMemDC->SetTextColor(RGB(137, 50, 66));
	   pMemDC->TextOutW(10, 85, Nuke, _tcslen(Nuke));
	}
	else
	{   
		CString str=_T("��Ϸ����");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
	}
	if (Lvl_Me == 3)
	{
		CString str = _T("��Ϸʤ������������");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	}
	
	//���� ��������ը���л����ӵ�
	for(int i=0;i<11;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %5+10;

	//��������л�
	if(nCreator<=0)
	{
		nCreator = rand()%5+10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
		
	}
	nCreator--;

	//����BOSS
	if (m_pMe != NULL)
	{
		if (Lvl_Me == 1)
		{
			if (Score_Me >= 200&&flag==0)
			{
				m_ObjList[enEnemyboss].AddTail(new CEnemyboss);
				PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				flag++;
			}
		}
		else if (Lvl_Me==2)
			{

			    if (Score_Me >= 1500&&flag1==0) 
			    {
				m_ObjList[enEnemyboss1].AddTail(new CEnemyboss1);
				PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				flag1++;
			    }
				
			}
	}
	
	if(m_pMe==NULL)
		return;

	//������Ʒ
	if (m_pMe->CD == 0)
	{
		int tpb = rand() % 3;
		if (tpb % 3 == 0)
			m_ObjList[enAtom].AddTail(new CAtom);
		else if (tpb % 3 == 1)
			m_ObjList[enNewbomb].AddTail(new CNewbomb);
		else 
			m_ObjList[enHp].AddTail(new CHp);
		m_pMe->CD = 200;
	}

	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(2);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-2);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(2);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-2);
	}
	
	//����ս������
	if(GetKey(32)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CBomb *bommb = NULL;
			CPoint pt = m_pMe->GetPoint();//��÷ɻ����Ͻ�����
			switch (CBomb::BombType)
			{
			case 0:
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10));
				break;
			case 1:
				bommb = new CBomb(pt.x + 10, pt.y);
				bommb->toward = -1;
				m_ObjList[enBomb].AddTail(bommb);
				bommb = new CBomb(pt.x + 20, pt.y);
				bommb->toward = 0;
				m_ObjList[enBomb].AddTail(bommb);
				bommb = new CBomb(pt.x + 30, pt.y);
				bommb->toward = 1;
				m_ObjList[enBomb].AddTail(bommb);
				break;
			}
		}
	}

	//�л������ӵ�
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));
		  }
	}

	//�л�BOSS�����ӵ�
	CPoint PlanePt1 = m_pMe->GetPoint();
	for (POSITION ePos1 = m_ObjList[enEnemyboss].GetHeadPosition(); ePos1 != NULL;)
	{
		CEnemyboss* pEnemyboss = (CEnemyboss*)m_ObjList[enEnemyboss].GetNext(ePos1);
		if (!pEnemyboss->Fired())
			continue;
		CPoint  ePt1 = pEnemyboss->GetPoint();

		if (ePt1.x +260>= PlanePt1.x && ePt1.x < PlanePt1.x + CMyPlane::PLANE_WIDTH)
		{
			PlaySound((LPCTSTR)IDR_WAVE5, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			m_ObjList[enBossball].AddTail(new CBossball(ePt1.x + 50, ePt1.y + 120, pEnemyboss->GetMontion()));
		    m_ObjList[enBossball].AddTail(new CBossball(ePt1.x + 80, ePt1.y + 120, pEnemyboss->GetMontion()));
			m_ObjList[enBossball].AddTail(new CBossball(ePt1.x + 150, ePt1.y + 120, pEnemyboss->GetMontion()));
			m_ObjList[enBossball].AddTail(new CBossball(ePt1.x + 180, ePt1.y + 120, pEnemyboss->GetMontion()));
		}
	}

	//�л�BOSS1�����ӵ�
	CPoint PlanePt2 = m_pMe->GetPoint();
	for (POSITION ePos2 = m_ObjList[enEnemyboss1].GetHeadPosition(); ePos2 != NULL;)
	{
		CEnemyboss1* pEnemyboss1 = (CEnemyboss1*)m_ObjList[enEnemyboss1].GetNext(ePos2);
		if (!pEnemyboss1->Fired())
			continue;
		CPoint  ePt2 = pEnemyboss1->GetPoint();

		if (ePt2.x + 190 >= PlanePt2.x && ePt2.x < PlanePt2.x + CMyPlane::PLANE_WIDTH)
		{
			PlaySound((LPCTSTR)IDR_WAVE5, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			m_ObjList[enBallboss].AddTail(new CBallboss(ePt2.x + 50, ePt2.y + 120, pEnemyboss1->GetMontion()));
			m_ObjList[enBallboss].AddTail(new CBallboss(ePt2.x + 50, ePt2.y + 120, pEnemyboss1->GetMontion()));
			m_ObjList[enBallboss].AddTail(new CBallboss(ePt2.x + 50, ePt2.y + 120, pEnemyboss1->GetMontion()));
			m_ObjList[enBallboss].AddTail(new CBallboss(ePt2.x + 50, ePt2.y + 120, pEnemyboss1->GetMontion()));
		}
	}
	
	//�л��ӵ�ը��ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);
			PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			if (GOD == 0)//�޵�ģʽ
			{
                m_pMe->HPNum_Me -= 5;//������Ѫ��-5
			    if (m_pMe->HPNum_Me <= 0)
			    {
				   --m_pMe->lifeNum_Me;
				   m_pMe->HPNum_Me = 70;
			     }
			     if (m_pMe->lifeNum_Me == 0 || m_pMe->HPNum_Me == 0)
			     {
				   delete m_pMe;
				   m_pMe = NULL;
			     }
			}
			break;
		}
	}
	
	//�л�BOSS�ӵ�ը��ս��
	POSITION bossPos1 = NULL, bossPos2 = NULL;
	CRect mRect3 = m_pMe->GetRect();
	for (bossPos1 = m_ObjList[enBossball].GetHeadPosition(); (bossPos2 = bossPos1) != NULL;)
	{
		CBossball* pBossball = (CBossball*)m_ObjList[enBossball].GetNext(bossPos1);
		CRect bossRect = pBossball->GetRect();
		CRect tmpRect1;
		if (tmpRect1.IntersectRect(&bossRect, mRect3))
		{
			PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect3.left, mRect3.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBossball].RemoveAt(bossPos2);
			delete pBossball;

			if (GOD == 0)//�޵�ģʽ
			{
				m_pMe->HPNum_Me -= 10;//������Ѫ��-5
				if (m_pMe->HPNum_Me <= 0)
				{
					--m_pMe->lifeNum_Me;
					m_pMe->HPNum_Me = 70;
				}
				if (m_pMe->lifeNum_Me == 0 || m_pMe->HPNum_Me == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
			}
			break;
		}
	}

	//�л�BOSS1�ӵ�ը��ս��
	for (bossPos1 = m_ObjList[enBallboss].GetHeadPosition(); (bossPos2 = bossPos1) != NULL;)
	{
		CBallboss* pBallboss = (CBallboss*)m_ObjList[enBallboss].GetNext(bossPos1);
		CRect bossRect = pBallboss->GetRect();
		CRect tmpRect1;
		if (tmpRect1.IntersectRect(&bossRect, mRect3))
		{
			PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect3.left, mRect3.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBallboss].RemoveAt(bossPos2);
			delete pBallboss;

			if (GOD == 0)//�޵�ģʽ
			{
				m_pMe->HPNum_Me -= 10;//������Ѫ��-10
				if (m_pMe->HPNum_Me <= 0)
				{
					--m_pMe->lifeNum_Me;
					m_pMe->HPNum_Me = 70;
				}
				if (m_pMe->lifeNum_Me == 0 || m_pMe->HPNum_Me == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
			}
			break;
		}
	}

	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				Score_Me += 5;
				break;
			}
		}
	}

	//ս�����������л�BOSS
	POSITION m1Pos1 = NULL, m1Pos2 = NULL;
	for (m1Pos1 = m_ObjList[enBomb].GetHeadPosition(); (m1Pos2 = m1Pos1) != NULL;)
	{
		CBomb* p1Bomb = (CBomb*)m_ObjList[enBomb].GetNext(m1Pos1);
		CRect b1Rect = p1Bomb->GetRect();

		POSITION e1Pos1 = NULL, e1Pos2 = NULL;
		for (e1Pos1 = m_ObjList[enEnemyboss].GetHeadPosition(); (e1Pos2 = e1Pos1) != NULL;)
		{
			CEnemyboss* p1Enemy = (CEnemyboss*)m_ObjList[enEnemyboss].GetNext(e1Pos1);
			CRect m1Rect = p1Enemy->GetRect();
			CRect tmp1Rect;
			if (tmp1Rect.IntersectRect(&b1Rect, m1Rect))
			{
				PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b1Rect.left, b1Rect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(m1Pos2);
				delete p1Bomb;

				//ɾ���л�BOSS
				p1Enemy->HPBOSS -= 2;
				if (p1Enemy->HPBOSS == 0)
				{
					m_ObjList[enEnemyboss].RemoveAt(e1Pos2);
					delete p1Enemy;
					Lvl_Me++;
				}
				Score_Me += 5;
				break;
			}
		}
	}

	//ս�����������л�BOSS1
	POSITION m2Pos1 = NULL, m2Pos2 = NULL;
	for (m2Pos1 = m_ObjList[enBomb].GetHeadPosition(); (m2Pos2 = m2Pos1) != NULL;)
	{
		CBomb* p2Bomb = (CBomb*)m_ObjList[enBomb].GetNext(m2Pos1);
		CRect b2Rect = p2Bomb->GetRect();

		POSITION e2Pos1 = NULL, e2Pos2 = NULL;
		for (e2Pos1 = m_ObjList[enEnemyboss1].GetHeadPosition(); (e2Pos2 = e2Pos1) != NULL;)
		{
			CEnemyboss1* p2Enemy = (CEnemyboss1*)m_ObjList[enEnemyboss1].GetNext(e2Pos1);
			CRect m2Rect = p2Enemy->GetRect();
			CRect tmp2Rect;
			if (tmp2Rect.IntersectRect(&b2Rect, m2Rect))
			{
				PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(m2Pos2);
				delete p2Bomb;

				//ɾ���л�BOSS1
				p2Enemy->HPBOSS1 -= 2;
				if (p2Enemy->HPBOSS1 == 0)
				{
					m_ObjList[enEnemyboss1].RemoveAt(e2Pos2);
					delete p2Enemy;
					Lvl_Me++;
				}
				Score_Me += 5;
				break;
			}
		}
	}

	//�������ӵ���ײ����
	POSITION bomPos1 = NULL, bomPos2 = NULL;
	for (bomPos1 = m_ObjList[enBomb].GetHeadPosition(); (bomPos2 = bomPos1) != NULL;)
	{
		CBomb* pbBomb = (CBomb*)m_ObjList[enBomb].GetNext(bomPos1);
		CRect bombRect = pbBomb->GetRect();

		POSITION balPos1 = NULL, balPos2 = NULL;
		for (balPos1 = m_ObjList[enBall].GetHeadPosition(); (balPos2 = balPos1) != NULL;)
		{
			CBall* pbBall = (CBall*)m_ObjList[enBall].GetNext(balPos1);
			CRect ballRect = pbBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bombRect, ballRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bombRect.left, bombRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(bomPos2);
				delete pbBomb;

				//ɾ���ӵ�
				m_ObjList[enBall].RemoveAt(balPos2);
				delete pbBall;
				break;
			}
		}
	}

	//����Ƿ��ͷ�ը��ը���л�1
	if (GetKey(66) == 1 && Nuke_Me > 0)//���ո��ͷŵ���
	{
		Nuke_Me -= 1;
		CRect bRect;
		bRect.top = 0;
		bRect.left = 0;
		bRect.right = GAME_WIDTH;
		bRect.bottom = GAME_HEIGHT;//����
		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				Score_Me += 5;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);//�첽����
				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
			}
		}
		Sleep(150);//��ִͣ��150����
	}

	//�ɻ���ײ
	POSITION sPos1 = NULL, sPos2 = NULL;
	if (m_pMe == NULL)
	{
		return;
	}
	CRect mRect1 = m_pMe->GetRect();
	for (sPos1 = m_ObjList[enEnemy].GetHeadPosition(); (sPos2 = sPos1) != NULL;)
	{
		CEnemy* sEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(sPos1);
		CRect sRect = sEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&sRect, mRect1))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect1.left, mRect1.top)
				);
			//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(sPos2);
				delete sEnemy;
			 
			Score_Me += 5;

			if (GOD == 0)//�޵�ģʽ
			{
				//ɾ��ս��
				m_pMe->HPNum_Me -= 5;
				if (m_pMe->HPNum_Me <= 0)
				{
					--m_pMe->lifeNum_Me;
					m_pMe->HPNum_Me = 70;
				}
				if (m_pMe->lifeNum_Me == 0 || m_pMe->HPNum_Me == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
			}
			break;
		}
	}

	//BOSS��ɻ���ײ
	POSITION s1Pos1 = NULL, s1Pos2 = NULL;
	if (m_pMe == NULL)
	{
		return;
	}
	CRect mRect4 = m_pMe->GetRect();
	for (s1Pos1 = m_ObjList[enEnemyboss].GetHeadPosition(); (s1Pos2 = s1Pos1) != NULL;)
	{
		CEnemyboss* sEnemyboss = (CEnemyboss*)m_ObjList[enEnemyboss].GetNext(s1Pos1);
		CRect sRect1 = sEnemyboss->GetRect();
		CRect tmpRect2;
		if (tmpRect2.IntersectRect(&sRect1, mRect4))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect4.left, mRect4.top)
				);

			//ɾ���л�BOSS
			sEnemyboss->HPBOSS -= 5;
			if (sEnemyboss->HPBOSS <= 0)
			{
				m_ObjList[enEnemyboss].RemoveAt(s1Pos2);
				delete sEnemyboss;
				Lvl_Me++;
			}
			Score_Me += 5;

			if (GOD == 0)//�޵�ģʽ
			{
				//ɾ��ս��
				m_pMe->lifeNum_Me -= 1;
				if (m_pMe->lifeNum_Me == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
			}
			break;
		}
	}

	//����ը��
	for (bPos1 = m_ObjList[enAtom].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CAtom* pNuke = (CAtom*)m_ObjList[enAtom].GetNext(bPos1);
		CRect bRect = pNuke->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ��
			m_ObjList[enAtom].RemoveAt(bPos2);
			delete pNuke;
			Nuke_Me += 1;
		}
	}

	//����Ѫ��
	for (bPos1 = m_ObjList[enHp].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CHp* pHp = ( CHp* )m_ObjList[enHp].GetNext(bPos1);
		CRect bRect = pHp->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ��
			m_ObjList[enHp].RemoveAt(bPos2);
			delete pHp;
			m_pMe->lifeNum_Me += 1;
		}
	}
	
	//�任�ӵ�
	for (bPos1 = m_ObjList[enNewbomb].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CNewbomb* pNewbomb = (CNewbomb*)m_ObjList[enNewbomb].GetNext(bPos1);
		CRect bRect = pNewbomb->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ��
			m_ObjList[enNewbomb].RemoveAt(bPos2);
			delete pNewbomb;
			CBomb::ChangeType(1, GetTickCount());//�����������ڵ�ʱ��
		}
	}
	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	if (m_pMe != NULL)
	{
    	if (m_pMe->CD > 0)
		{
			m_pMe->CD--;
		}
	}
	UpdateFrame(m_pMemDC);//ˢ�¾��
	AI();
	CView::OnTimer(nIDEvent);//���ദ��
}

void CPlaneGameView::OnStart()
{
	// TODO:  �ڴ���������������
	if (!init)
	{
		InitGame();
		init = 1;
	}
}

void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_ESCAPE)//��ͣ��
	{
		if (!pause)
		{
			KillTimer(1);
			pause = 1;
		}
		else
		{
			SetTimer(1, 30, NULL);
			pause = 0;
		}
	}
	if (nChar == VK_RETURN)//��ʼ��
	{
		InitGame();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPlaneGameView::OnRestart()
{
	// TODO:  �ڴ���������������
	KillTimer(1);
	m_pMe = new CMyPlane;//���������ڴ�ռ�
	Score_Me = 0;
	m_pMe->lifeNum_Me = 6;
	m_pMe->HPNum_Me = 70;
	Lvl_Me = 1;
	Nuke_Me = 3;
	for (int i = 0; i < 10; i++)
		m_ObjList[i].RemoveAll();
	SetTimer(1, 30, NULL);//һ�ż�ʱ����30����ִ��һ�Σ�Ĭ��ִ��OnTimer
	
}

void CPlaneGameView::OnSetlvl()
{
	// TODO:  �ڴ���������������
	CSetlvl L1;
	if (L1.DoModal() == IDOK)
	{
		Lvl_Me = L1.setlvl;
		if (Lvl_Me==2)
			Score_Me = 1000;
	}
}