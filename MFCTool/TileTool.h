#pragma once
#include "afxwin.h"


// CTileTool ��ȭ �����Դϴ�.

class CTerrain;
class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTileTool();

public:
	int m_iDrawID;
	CTerrain* m_pTerrain;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
