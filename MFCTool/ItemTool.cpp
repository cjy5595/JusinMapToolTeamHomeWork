// ItemTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ItemTool.h"
#include "afxdialogex.h"
#include "TextureMgr.h"
#include "Graphic_Device.h"
#include "Item.h"
#include "MainFrm.h"
// CItemTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemTool, CDialog)

CItemTool::CItemTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ITEMTOOL, pParent)
	, m_strItemName(_T(""))
	, m_iAddHp(0)
	, m_iAddAtk(0)
	, m_iAddSpeed(0)
	, m_strSearch(_T(""))
{

}

CItemTool::~CItemTool()
{
	Release();
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strItemName);
	DDX_Text(pDX, IDC_EDIT2, m_iAddHp);
	DDX_Text(pDX, IDC_EDIT3, m_iAddAtk);
	DDX_Text(pDX, IDC_EDIT4, m_iAddSpeed);
	DDX_Control(pDX, IDC_LIST1, m_PngListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_RADIO3, m_ItmeOption[0]);
	DDX_Control(pDX, IDC_RADIO4, m_ItmeOption[1]);
	DDX_Control(pDX, IDC_PICTURE2, m_AddPictrue);
	DDX_Control(pDX, IDC_LIST2, m_AddListBox);
	DDX_Control(pDX, IDC_LIST3, m_InstantList);
	DDX_Text(pDX, IDC_EDIT8, m_strSearch);
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CItemTool::ItemAddButton)
	ON_BN_CLICKED(IDC_BUTTON7, &CItemTool::SaveButton)
	ON_BN_CLICKED(IDC_BUTTON8, &CItemTool::LoadButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &CItemTool::ItemPngListBox)
	ON_LBN_SELCHANGE(IDC_LIST2, &CItemTool::AddListBox)
	ON_LBN_SELCHANGE(IDC_LIST3, &CItemTool::InstantList)
	ON_EN_CHANGE(IDC_EDIT8, &CItemTool::SearchDataEditBox)
	ON_BN_CLICKED(IDC_BUTTON10, &CItemTool::ReadyInstantButton)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON9, &CItemTool::vecIndexDeleteButton)
END_MESSAGE_MAP()


// CItemTool �޽��� ó�����Դϴ�.


void CItemTool::Release()
{
	for_each(m_mapPngImage.begin(), m_mapPngImage.end(), DeleteMap());
	m_mapPngImage.clear();

	for_each(m_mapItemData.begin(), m_mapItemData.end(), DeleteMap());
	m_mapItemData.clear();

	Safe_Delete(m_pItemManager);
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
		{
			ERR_MSG(L"�̹�����ΰ� �߸��ǰų� �ε� ��������.");
			return FALSE;
		}
			

		CString strImageName = PathFindFileName(strFilePath);
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());
		m_mapPngImage.emplace(strImageName, pPngImage);
		m_PngListBox.AddString(strImageName);
	}

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ItmeOption[0].SetCheck(TRUE);
	m_pItemManager = new CItem;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}




void CItemTool::ItemAddButton()
{
	//�� ��ư�� ������ ������ �߰��մϴ�.
	UpdateData(TRUE);
	ITEMDATA*		pItemData = new ITEMDATA;
	pItemData->strName = m_strItemName;
	pItemData->iAddHp = m_iAddHp;
	pItemData->iAttack = m_iAddAtk;
	pItemData->iSpeed = m_iAddSpeed;
	pItemData->byDrawID = m_iImageDrawID;

	for (int i = 0; i < 2; ++i)
	{
		if (m_ItmeOption[i].GetCheck())
		{
			pItemData->byOption = i;
			break;
		}
	}
	m_AddListBox.AddString(pItemData->strName);
	m_mapItemData.emplace(pItemData->strName, pItemData);
	
	UpdateData(FALSE);
}


void CItemTool::SaveButton()
{
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"��� ���� ����.");
		return;
	}
	DWORD dwByte = 0;
	DWORD dwStringSize = 0;

	for (auto& rPair : m_mapItemData)
	{
		dwStringSize = sizeof(wchar_t) * (rPair.second->strName.GetLength() + 1);
		WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
		WriteFile(hFile, rPair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
		WriteFile(hFile, &rPair.second->iAddHp, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &rPair.second->iAttack, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &rPair.second->iSpeed, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &rPair.second->byOption, sizeof(BYTE), &dwByte, nullptr);
		WriteFile(hFile, &rPair.second->byDrawID, sizeof(BYTE), &dwByte, nullptr);
	}
	
	CloseHandle(hFile);

}


void CItemTool::LoadButton()
{
	
	
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"��� ���� ����.");
		return;
	}
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;

		for_each(m_mapItemData.begin(), m_mapItemData.end(), DeleteMap());
		m_mapItemData.clear();
		m_AddListBox.ResetContent();
		TCHAR* pTemp = nullptr;
		while (true)
		{
			ITEMDATA* pItemData = new ITEMDATA;
			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			
			pTemp = new TCHAR[dwStringSize];
			ReadFile(hFile, pTemp, dwStringSize, &dwByte, nullptr);
			ReadFile(hFile, &pItemData->iAddHp, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pItemData->iAttack, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pItemData->iSpeed, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pItemData->byOption, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &pItemData->byDrawID, sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				SAFE_DELETE(pItemData);
				if (pTemp)
				{
					delete[] pTemp;
					pTemp = nullptr;
				}
				break;
			}
			pItemData->strName = pTemp;
			m_mapItemData.emplace(pItemData->strName, pItemData);
			m_AddListBox.AddString(pItemData->strName);
			SAFE_DELETE(pTemp);
			
		}
		CloseHandle(hFile);
}


void CItemTool::ItemPngListBox()
{
	// PngData���� �̹������� �����ݴϴ�.
	UpdateData(TRUE);
	
	int iIndex = m_PngListBox.GetCurSel();
	if (0 > iIndex)
	{
		ERR_MSG(L"Png ����Ʈ�� �߸� ���õ�.");
		return;
	}
	m_PngListBox.GetText(iIndex, m_ImageName); // �ε��� �̾Ƴ����۾�.
	auto & iter = m_mapPngImage.find(m_ImageName);

	if (iter == m_mapPngImage.end())
	{
		ERR_MSG(L"���õ� ��Ʈ�������� Map������ ����.");
		return;
	}
	
	m_Picture.SetBitmap(*iter->second);
	
	int i = 0;
	for (; i < m_ImageName.GetLength(); ++i)
	{
		if (isdigit(m_ImageName[i]) != 0)
			break;
	}
	m_ImageName.TrimLeft(L"Item");
	m_iImageDrawID = _tstoi(m_ImageName);
	
	UpdateData(FALSE);
}


void CItemTool::AddListBox()
{
	UpdateData(TRUE);
	CString strSelectName;
	int iSelect = m_AddListBox.GetCurSel();
	m_AddListBox.GetText(iSelect, strSelectName);

	if (0 > iSelect)
	{
		ERR_MSG(L"������ ���� ����Ʈ�� �߸� ���õ�.");
		return;
	}
		

	auto & iter = m_mapItemData.find(strSelectName);
	if (iter == m_mapItemData.end())
	{
		ERR_MSG(L"������ ���� ��Ʈ�������� ����.");
		return;
	}
	
	m_strItemName = iter->second->strName;
	m_iAddHp = iter->second->iAddHp;
	m_iAddAtk = iter->second->iAttack;
	m_iAddSpeed = iter->second->iSpeed;
	
	for (int i = 0; i < 2; ++i)
		m_ItmeOption[i].SetCheck(FALSE);

	m_ItmeOption[iter->second->byOption].SetCheck(TRUE);


	CString strItmeName = L"Item";
	CString strInt = L"";
	strInt.Format(_T("%d"), iter->second->byDrawID);

	strItmeName += strInt;
	auto & iter_Image = m_mapPngImage.find(strItmeName);
	if (iter_Image == m_mapPngImage.end())
	{
		ERR_MSG(L"�̹��� ���� ��Ʈ�������� ����.");
		return;
	}

	m_AddPictrue.SetBitmap(*iter_Image->second);
	UpdateData(FALSE);
}


void CItemTool::InstantList()
{
	UpdateData(TRUE);
	
	
	UpdateData(FALSE);
}


void CItemTool::SearchDataEditBox()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	auto iter = m_mapItemData.find(m_strSearch);

	if (iter == m_mapItemData.end())
		return;

	int iIndex = m_AddListBox.FindString(0, m_strSearch);
	if (iIndex < 0)
	{
		ERR_MSG(L"������ ����� ����Ʈ ��Ʈ�� Ž������");
		return;
	}
	m_AddListBox.SetCurSel(iIndex);

	m_strItemName = iter->second->strName;
	m_iAddHp = iter->second->iAddHp;
	m_iAddAtk = iter->second->iAttack;
	m_iAddSpeed = iter->second->iSpeed;

	for (int i = 0; i < 2; ++i)
		m_ItmeOption[i].SetCheck(FALSE);

	m_ItmeOption[iter->second->byOption].SetCheck(TRUE);

	UpdateData(FALSE);
	
}


void CItemTool::ReadyInstantButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString strSelectName;
	int iSelect = m_AddListBox.GetCurSel();
	m_AddListBox.GetText(iSelect, strSelectName);

	if (0 > iSelect)
	{
		ERR_MSG(L"������ ���� ����Ʈ�� �߸� ���õ�.");
		return;
	}


	auto & iter = m_mapItemData.find(strSelectName);
	if (iter == m_mapItemData.end())
	{
		ERR_MSG(L"������ ���� ��Ʈ�������� ����.");
		return;
	}


	m_pInstantData = iter->second;
	((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::ITEM_RENDER;
	((CMainFrame*)AfxGetMainWnd())->m_pToolView->Invalidate(FALSE);
	UpdateData(FALSE);

}



void CItemTool::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pToolView->m_eRenderMode = CMFCToolView::RENDER_END;
	CDialog::OnClose();
}


void CItemTool::vecIndexDeleteButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strName;

	int iSelect = m_InstantList.GetCurSel();
	if (m_pItemManager->GetItemVec()->empty())
		return;
	
	for (size_t i = 0; i < m_pItemManager->GetItemVec()->size(); ++i)
	{
		if (iSelect == i)
		{
			SAFE_DELETE(*(m_pItemManager->GetItemVec()->begin() + i));
			m_pItemManager->GetItemVec()->erase(m_pItemManager->GetItemVec()->begin() + i);
			m_InstantList.DeleteString(iSelect);
			m_InstantList.ResetContent();
			break;
		}
	}
	
	for (size_t i = 0; i < m_pItemManager->GetItemVec()->size(); ++i)
	{
		strName.Format(_T("%d"), i);
		m_InstantList.AddString(strName);
	}

	((CMainFrame*)AfxGetMainWnd())->m_pToolView->Invalidate(FALSE);
	UpdateData(FALSE);
}
