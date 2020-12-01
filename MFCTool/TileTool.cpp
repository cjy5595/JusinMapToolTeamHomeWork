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
#include "MiniView.h"

// CTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent), m_iDrawID(0), m_pTerrain(nullptr)
	, m_iTileSizeX(0)
	, m_iTileSizeY(0)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
{

}

CTileTool::~CTileTool()
{
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
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON2, &CTileTool::OnBnClickedButtonCreateTile)
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
		m_pTerrain->m_iTileCountX = m_iTileCountX;
		m_pTerrain->m_iTileCountY = m_iTileCountY;
		m_pTerrain->m_iTileSizeX = m_iTileSizeX;
		m_pTerrain->m_iTileSizeY = m_iTileSizeY;
		m_pTerrain->m_iDrawID = m_iDrawID;

		m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(pView);
		pView->Invalidate(false);
		
	}
	UpdateData(FALSE);

}
