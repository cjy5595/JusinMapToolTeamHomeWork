// MyFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyFormView.h"


// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView(IDD_MYFORMVIEW)
{

}

CMyFormView::~CMyFormView()
{

}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyFormView::MonsterToolButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyFormView::TileToolButton)
END_MESSAGE_MAP()


// CMyFormView �����Դϴ�.

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFormView �޽��� ó�����Դϴ�.


void CMyFormView::MonsterToolButton()
{
	m_tMonsterTool.ShowWindow(SW_SHOW);
}


void CMyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if (nullptr == m_tMonsterTool.GetSafeHwnd())
		m_tMonsterTool.Create(IDD_MONSTERTOOL);
	if (nullptr == m_tTileTool.GetSafeHwnd())
		m_tTileTool.Create(IDD_TILETOOL);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CMyFormView::TileToolButton()
{
	m_tTileTool.ShowWindow(SW_SHOW);
}
