// MyFormView.cpp : 구현 파일입니다.
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


// CMyFormView 진단입니다.

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


// CMyFormView 메시지 처리기입니다.


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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyFormView::TileToolButton()
{
	m_tTileTool.ShowWindow(SW_SHOW);
}
