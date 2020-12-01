#pragma once


// CItemTool ��ȭ �����Դϴ�.
#include "FileInfo.h"
class CGraphic_Device;
class CMFCToolView;
class CItem;
class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	map<CString, CImage*>  m_mapPngImage;
	CMFCToolView*		   m_pToolView;

public:
	void Release();
	virtual BOOL OnInitDialog();
};
