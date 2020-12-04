#pragma once



// CMyFormView �� ���Դϴ�.
#include "MonsterTool.h"
#include "TileTool.h"
#include "ItemTool.h"
class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

protected:
	CMyFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


public:

	CMonsterTool m_tMonsterTool;
	CTileTool	 m_tTileTool;
	CItemTool	m_tItemTool;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MonsterToolButton();
	virtual void OnInitialUpdate();
	afx_msg void TileToolButton();
	afx_msg void ItemToolButton();
	afx_msg void InstanceItemDataSave();
	afx_msg void InstanceItemDataLoad();
};


