#pragma once


// CMonsterTool ��ȭ �����Դϴ�.

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonsterTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
