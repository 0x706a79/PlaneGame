#pragma once


// CSetlvl �Ի���

class CSetlvl : public CDialog
{
	DECLARE_DYNAMIC(CSetlvl)

public:
	CSetlvl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetlvl();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	int setlvl;
};
