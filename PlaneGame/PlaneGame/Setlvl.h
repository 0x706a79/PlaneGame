#pragma once


// CSetlvl 对话框

class CSetlvl : public CDialog
{
	DECLARE_DYNAMIC(CSetlvl)

public:
	CSetlvl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetlvl();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int setlvl;
};
