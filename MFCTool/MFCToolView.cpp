
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()

{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pFormView = dynamic_cast<CMyFormView*>(pMain->m_SecondSplitter.GetPane(1, 0));

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CGraphic_Device::Get_Instance()->Render_Begin();
	//this;
	if(m_pFormView->m_tTileTool.m_pTerrain)
		m_pFormView->m_tTileTool.m_pTerrain->Render_Terrain();
	//InvalidateRect(nullptr, FALSE);
	
	CGraphic_Device::Get_Instance()->Render_End();
	
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
