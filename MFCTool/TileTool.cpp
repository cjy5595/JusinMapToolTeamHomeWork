// TileTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "TileTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "TextureMgr.h"
#include "Graphic_Device.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "MyFormView.h"


// CTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent), m_iDrawID(0), m_pTerrain(nullptr)
	, m_iTileSizeX(0)
	, m_iTileSizeY(0)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
	, m_iDrawID2(0)
{

}

CTileTool::~CTileTool()
{
	Safe_Delete(m_pTerrain);
}

void CTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT5, m_iTileSizeX);
	DDX_Text(pDX, IDC_EDIT7, m_iTileSizeY);
	DDX_Text(pDX, IDC_EDIT1, m_iTileCountX);
	DDX_Text(pDX, IDC_EDIT2, m_iTileCountY);
	DDX_Text(pDX, IDC_EDIT6, m_iDrawID2);
	DDX_Control(pDX, IDC_CHECK2, m_ViewIndex);
	DDX_Control(pDX, IDC_CHECK3, m_CheckGrid);
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON2, &CTileTool::OnBnClickedButtonCreateTile)
	ON_BN_CLICKED(IDC_CHECK2, &CTileTool::OnBnClickedCheckViewIndex)
	ON_BN_CLICKED(IDC_BUTTON4, &CTileTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CTileTool::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON6, &CTileTool::OnBnClickedButtonDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON1, &CTileTool::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_CHECK3, &CTileTool::OnBnClickedCheckViewGrid)
END_MESSAGE_MAP()


// CTileTool 메시지 처리기입니다.


void CTileTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szBuf[MAX_PATH] = L"";
	
	TCHAR szFileName[MAX_PATH] = L"";
	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szBuf, MAX_PATH);
		CString strRelativePath = CFileInfo::ConvertRelativePath(szBuf);
		CString strFileNameAndExtent = PathFindFileName(strRelativePath);
		lstrcpy(szFileName, strFileNameAndExtent.GetString());
		PathRemoveExtension(szFileName);
		m_ListBox.AddString(szFileName);
	}

	UpdateData(FALSE);

	CDialog::OnDropFiles(hDropInfo);
}


void CTileTool::OnLbnSelchangePicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strFileName;
	int iIndex = m_ListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFileName);

	int i = 0;

	for (; i < strFileName.GetLength(); ++i)
	{
		if (isdigit(strFileName[i]))
			break;
	}
	strFileName.Delete(0, i);
	m_iDrawID = _wtoi(strFileName);
	m_iDrawID2 = m_iDrawID;

	D3DXMATRIX matScale, matTrans;
	float fRatioX = WINCX / TILECX;
	float fRatioY = WINCY / TILECY;

	D3DXMatrixScaling(&matScale, fRatioX , fRatioY, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX >> 1), float(WINCY >> 1), 0.f);
	matScale *= matTrans;
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_iDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >>1;

	CGraphic_Device::Get_Instance()->Render_Begin();
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);

	((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::TILE_RENDER;
	((CMainFrame*)AfxGetMainWnd())->m_pToolView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CTileTool::OnBnClickedButtonCreateTile()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pTerrain)
	{
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));

		m_pTerrain = new CTerrain;
		m_pTerrain->m_tTerrainInfo.iTileCountX = m_iTileCountX;
		m_pTerrain->m_tTerrainInfo.iTileCountY = m_iTileCountY;
		m_pTerrain->m_iTileSizeX = m_iTileSizeX;
		m_pTerrain->m_iTileSizeY = m_iTileSizeY;
		m_pTerrain->m_iDrawID = m_iDrawID;

		m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(pView);
	
		pView->SetScrollSizes(MM_TEXT, CSize(m_iTileSizeX * m_iTileCountX, m_iTileSizeY * m_iTileCountY));
		pView->Invalidate(false);
		
	}
	UpdateData(FALSE);

}


void CTileTool::OnBnClickedCheckViewIndex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
	CMyFormView* pFormView = dynamic_cast<CMyFormView*>(pMain->m_MainSplitter.GetPane(0, 1));
	if (BST_CHECKED == m_ViewIndex.GetCheck())
		pFormView->m_tTileTool.m_pTerrain->m_bText = true;
	else if (BST_UNCHECKED == m_ViewIndex.GetCheck())
		pFormView->m_tTileTool.m_pTerrain->m_bText = false;
	
	pView->InvalidateRect(nullptr, FALSE);
	UpdateData(FALSE);
}


void CTileTool::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	vector<TILE*>& rvecTile = m_pTerrain->Get_vecTile();
	CFileDialog Dlg(FALSE, 
		L"dat", 
		L"*.dat",
		OFN_OVERWRITEPROMPT, 
		L"Data File(*dat) | *.dat||",
		this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			ERR_MSG(L"저장 실패");
			return;
		}
		
		DWORD dwByte = 0;
		WriteFile(hFile, &m_pTerrain->m_tTerrainInfo, sizeof(TERRAININFO), &dwByte, nullptr);
		for (auto& pTile : rvecTile)
		{
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

}


void CTileTool::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));

	CFileDialog Dlg(TRUE, L"dat", L"*.dat",
		OFN_OVERWRITEPROMPT, L"Data File(*dat) | *.dat||",
		this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			ERR_MSG(L"불러오기 실패");
			return;
		}

		if (m_pTerrain)
			m_pTerrain->Release_Terrain();
		
		if (nullptr == m_pTerrain)
			m_pTerrain = new CTerrain;

		DWORD dwByte = 0;
		TILE* pTile = nullptr;

		ReadFile(hFile, &m_pTerrain->m_tTerrainInfo, sizeof(TERRAININFO), &dwByte, nullptr);

		while (true)
		{
			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}
			m_pTerrain->Set_TileData(pTile);
		}
		CloseHandle(hFile);
		//m_pTerrain->Get_vecTile().reserve(m_pTerrain->m_tTerrainInfo.iTotalCount);
		//m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(pView);

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMyFormView* pFormView = dynamic_cast<CMyFormView*>(pMain->m_MainSplitter.GetPane(0, 1));
		m_iTileCountX = m_pTerrain->m_tTerrainInfo.iTileCountX;
		m_iTileCountY = m_pTerrain->m_tTerrainInfo.iTileCountY;
		m_iTileSizeX = m_pTerrain->m_tTerrainInfo.iTileSizeX;
		m_iTileSizeY = m_pTerrain->m_tTerrainInfo.iTileSizeY;
		
		m_pTerrain->Set_View(pView);

		pView->SetScrollSizes(MM_TEXT, CSize(m_iTileSizeX * m_iTileCountX, m_iTileSizeY * m_iTileCountY));
		pView->Invalidate(false);

		((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::TILE_RENDER;
		Invalidate(FALSE);
	}
	UpdateData(FALSE);
}


void CTileTool::OnBnClickedButtonDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
	UpdateData(TRUE);

	m_pTerrain->Release_Terrain();
	SAFE_DELETE(m_pTerrain);

	pView->InvalidateRect(nullptr, FALSE);
	UpdateData(FALSE);
}


void CTileTool::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTileTool::OnBnClickedCheckViewGrid()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
	CMyFormView* pFormView = dynamic_cast<CMyFormView*>(pMain->m_MainSplitter.GetPane(0, 1));
	if (BST_CHECKED == m_CheckGrid.GetCheck())
		pFormView->m_tTileTool.m_pTerrain->m_bGrid = true;
	else if (BST_UNCHECKED == m_CheckGrid.GetCheck())
		pFormView->m_tTileTool.m_pTerrain->m_bGrid = false;

	pView->InvalidateRect(nullptr, FALSE);
	UpdateData(FALSE);
}
