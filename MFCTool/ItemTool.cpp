// ItemTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ItemTool.h"
#include "afxdialogex.h"


// CItemTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CItemTool, CDialog)

CItemTool::CItemTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ITEMTOOL, pParent)
{

}

CItemTool::~CItemTool()
{
	Release();
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
END_MESSAGE_MAP()


// CItemTool 메시지 처리기입니다.


void CItemTool::Release()
{
	for_each(m_mapPngImage.begin(), m_mapPngImage.end(), DeleteMap());
	m_mapPngImage.clear();
}

BOOL CItemTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR strFilePath[MAX_PATH] = L"";
	
	for (int i = 0; i < 4; ++i)
	{
		swprintf_s(strFilePath, L"../Texture/Item/MfcItem/Item%d.png", i);
		CImage* pPngImage = new CImage;
		HRESULT hImageInit = pPngImage->Load(strFilePath);
		if (hImageInit == E_FAIL)
			return FALSE;

		CString strImageName = PathFindFileName(strFilePath);
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());
		m_mapPngImage.emplace(strImageName, pPngImage);
		/*ex.AddString(strImageName);*/
	}

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
