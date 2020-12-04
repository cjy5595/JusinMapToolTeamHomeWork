// MyFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyFormView.h"
#include "Item.h"
#include "MainFrm.h"

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
	ON_BN_CLICKED(IDC_BUTTON3, &CMyFormView::ItemToolButton)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyFormView::InstanceItemDataSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyFormView::InstanceItemDataLoad)
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
	if (nullptr == m_tItemTool.GetSafeHwnd())
		m_tItemTool.Create(IDD_ITEMTOOL);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyFormView::TileToolButton()
{
	m_tTileTool.ShowWindow(SW_SHOW);
}


void CMyFormView::ItemToolButton()
{
	
	m_tItemTool.ShowWindow(SW_SHOW);
}


void CMyFormView::InstanceItemDataSave()
{
	if (!m_tItemTool.m_pItemManager)
		return;
	UpdateData(TRUE);
	HANDLE hFile = CreateFile(L"../Data/InstanceItem.dat", 
		GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwByte = 0;
	auto & iter = m_tItemTool.m_pItemManager->GetItemVec()->begin();
	auto & iter_end = m_tItemTool.m_pItemManager->GetItemVec()->end();
	for (iter; iter != iter_end; ++iter)
	{
		WriteFile(hFile, *iter, sizeof(ITEMDATA), &dwByte, NULL);
	}
	CloseHandle(hFile);
	UpdateData(FALSE);

}


void CMyFormView::InstanceItemDataLoad()
{
	if (!m_tItemTool.m_pItemManager)
		return;


	
	HANDLE hFile = CreateFile(L"../Data/InstanceItem.dat",
		GENERIC_READ, 0, nullptr, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD		dwByte;
	while (true)
	{
		ITEMDATA* pItem = new ITEMDATA;
		ReadFile(hFile, pItem, sizeof(ITEMDATA), &dwByte, NULL);

		if (dwByte == 0)
		{
			Safe_Delete(pItem);
			break;
		}

		m_tItemTool.m_pItemManager->GetItemVec()->emplace_back(pItem);

	}

	CString strName;
	m_tItemTool.m_InstantList.ResetContent();
	for (size_t i = 0; i < m_tItemTool.m_pItemManager->GetItemVec()->size(); ++i)
	{
		strName.Format(_T("%d"), i);
		m_tItemTool.m_InstantList.AddString(strName);
	}

	((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::ITEM_RENDER;
	((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::RENDER_END;

	CloseHandle(hFile);
}
