#pragma once


// CItemTool 대화 상자입니다.
#include "FileInfo.h"
#include "afxwin.h"
class CGraphic_Device;
class CMFCToolView;
class CItem;
class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CItemTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	map<CString, CImage*>  m_mapPngImage;
	map<CString, ITEMDATA*> m_mapItemData;
	CMFCToolView*		   m_pToolView;
	ITEMDATA*			   m_pInstantData;

public:
	void Release();
	virtual BOOL OnInitDialog();
	
	// 아이템의 이름입니다.
	CString m_ImageName;
	CString m_strItemName;
	// 아이템효과 체력추가
	int m_iAddHp;
	// 추가되는 공격력
	int m_iAddAtk;
	// 추가되는 스피드
	int m_iAddSpeed;
	afx_msg void ItemAddButton();
	afx_msg void SaveButton();
	afx_msg void LoadButton();
	afx_msg void ItemPngListBox();
	CListBox m_PngListBox;
	CStatic  m_Picture;
	CButton  m_ItmeOption[2];
	// 추가된아이템의 그림
	CStatic m_AddPictrue;
	CListBox m_AddListBox;
	afx_msg void AddListBox();
	// 뷰에 설치된 객체들의 인덱스를 정리할 리스트
	CListBox m_InstantList;
	afx_msg void InstantList();

	int m_iImageDrawID = 0;
	afx_msg void SearchDataEditBox();
	// 검색할 문자열을 입력받는 스트링
	CString m_strSearch;
	// CItem 클래스

	CItem*		m_pItemManager;
	afx_msg void ReadyInstantButton();
};
