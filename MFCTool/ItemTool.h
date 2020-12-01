#pragma once


// CItemTool 대화 상자입니다.
#include "FileInfo.h"
class CGraphic_Device;
class CMFCToolView;
class CItem;
class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CItemTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	map<CString, CImage*>  m_mapPngImage;
	CMFCToolView*		   m_pToolView;

public:
	void Release();
	virtual BOOL OnInitDialog();
};
