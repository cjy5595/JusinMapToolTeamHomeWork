// ItemTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ItemTool.h"
#include "afxdialogex.h"


// CItemTool ��ȭ �����Դϴ�.

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


// CItemTool �޽��� ó�����Դϴ�.


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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
