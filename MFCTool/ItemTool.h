#pragma once


// CItemTool ��ȭ �����Դϴ�.
#include "FileInfo.h"
#include "afxwin.h"
class CGraphic_Device;
class CMFCToolView;
class CItem;
class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	map<CString, CImage*>  m_mapPngImage;
	map<CString, ITEMDATA*> m_mapItemData;
	CMFCToolView*		   m_pToolView;
	ITEMDATA*			   m_pInstantData;

public:
	void Release();
	virtual BOOL OnInitDialog();
	
	// �������� �̸��Դϴ�.
	CString m_ImageName;
	CString m_strItemName;
	// ������ȿ�� ü���߰�
	int m_iAddHp;
	// �߰��Ǵ� ���ݷ�
	int m_iAddAtk;
	// �߰��Ǵ� ���ǵ�
	int m_iAddSpeed;
	afx_msg void ItemAddButton();
	afx_msg void SaveButton();
	afx_msg void LoadButton();
	afx_msg void ItemPngListBox();
	CListBox m_PngListBox;
	CStatic  m_Picture;
	CButton  m_ItmeOption[2];
	// �߰��Ⱦ������� �׸�
	CStatic m_AddPictrue;
	CListBox m_AddListBox;
	afx_msg void AddListBox();
	// �信 ��ġ�� ��ü���� �ε����� ������ ����Ʈ
	CListBox m_InstantList;
	afx_msg void InstantList();

	int m_iImageDrawID = 0;
	afx_msg void SearchDataEditBox();
	// �˻��� ���ڿ��� �Է¹޴� ��Ʈ��
	CString m_strSearch;
	// CItem Ŭ����

	CItem*		m_pItemManager;
	afx_msg void ReadyInstantButton();
};
