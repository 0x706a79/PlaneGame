// PlaneGameView.h : CPlaneGameView 类的接口
//

#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{ enEnemy, enBomb, enBall, enExplosion, enEnemyboss, enBossball, enBallboss, enAtom, enNewbomb, enHp, enEnemyboss1};

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;
	int Score_Me;//分数
	int Lvl_Me;//关卡
	int Nuke_Me;//导弹
// 操作
public:
	wchar_t lifeleft[20];//存储剩余生命
	wchar_t Score[20];//存储分数
	wchar_t Lvl[20];//存储关卡
	wchar_t Nuke[20];//存储导弹

	int pause;
	int GOD=0;
	int flag=0, flag1=0;
	int speed=0;


// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);

	void AI();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[12];

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRestart();
	afx_msg void OnSetlvl();
//	afx_msg void OnAppExit();
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

