// Setlvl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "Setlvl.h"
#include "afxdialogex.h"


// CSetlvl �Ի���

IMPLEMENT_DYNAMIC(CSetlvl, CDialog)

CSetlvl::CSetlvl(CWnd* pParent /*=NULL*/)
	: CDialog(CSetlvl::IDD, pParent)
	, setlvl(0)
{

}

CSetlvl::~CSetlvl()
{
}

void CSetlvl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, setlvl);
}


BEGIN_MESSAGE_MAP(CSetlvl, CDialog)
END_MESSAGE_MAP()


// CSetlvl ��Ϣ�������
