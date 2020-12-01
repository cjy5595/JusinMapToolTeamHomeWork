
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "MyFormView.h"
#include "Graphic_Device.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "Terrain.h" 
#include "Item.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWND;
// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()

{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCToolView::~CMFCToolView()
{
	if (m_pFormView->m_tTileTool.m_pTerrain)
		SAFE_DELETE(m_pFormView->m_tTileTool.m_pTerrain);

	CTextureMgr::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pFormView = dynamic_cast<CMyFormView*>(pMain->m_SecondSplitter.GetPane(1, 0));

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CGraphic_Device::Get_Instance()->Render_Begin();
	//this;
	if(m_pFormView->m_tTileTool.m_pTerrain)
		m_pFormView->m_tTileTool.m_pTerrain->Render_Terrain();
	//InvalidateRect(nullptr, FALSE);
	
	CGraphic_Device::Get_Instance()->Render_End();
	
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILECX, TILECY * TILEY));

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMainRect = {};
	pMain->GetWindowRect(&rcMainRect);

	RECT rcView = {};
	GetClientRect(&rcView);
	int iGapX = rcMainRect.right - rcView.right;
	int iGapY = rcMainRect.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + iGapX, WINCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	g_hWND = m_hWnd;
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Ready Graphic Device failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture_Manager(CTextureMgr::MULTI_TEX, 
		L"../Texture/Images/Tile/Tile%d.png", L"Terrain", L"Tile",
		123)))
	{
		ERR_MSG(L"Insert Tile Texture failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture_Manager(CTextureMgr::MULTI_TEX,
		L"../Texture/Item/MfcItem/Item%d.png", L"Item", L"Weapon", 4)))
	{
		ERR_MSG(L"Insert Item(Weapon) Texture failed");
		return;
	}
	/*if (!m_pTerrain)
	{
		m_pTerrain = new CTerrain;
		m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(this);
	}*/

}
