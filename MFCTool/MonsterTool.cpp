// MonsterTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"


// CMonsterTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialog)

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONSTERTOOL, pParent)
{

}

CMonsterTool::~CMonsterTool()
{
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialog)
END_MESSAGE_MAP()


// CMonsterTool 메시지 처리기입니다.
