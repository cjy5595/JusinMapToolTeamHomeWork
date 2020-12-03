#pragma once
#include "afxwin.h"


// CTileTool 대화 상자입니다.

class CTerrain;
class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTileTool();

public:
	int m_iDrawID;
	CTerrain* m_pTerrain;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangePicture();
	CStatic m_Picture;
	afx_msg void OnBnClickedButtonCreateTile();
	int m_iTileSizeX;
	int m_iTileSizeY;
	int m_iTileCountX;
	int m_iTileCountY;
	int m_iDrawID2;
	afx_msg void OnBnClickedCheckViewIndex();
	CButton m_ViewIndex;
	CButton m_CheckGrid;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonDeleteAll();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedCheckViewGrid();
};
