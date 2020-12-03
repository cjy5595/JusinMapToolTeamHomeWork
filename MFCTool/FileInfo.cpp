#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{

}

CString CFileInfo::ConvertRelativePath(CString strFileFullPath)
{
	TCHAR szRelativePath[MAX_PATH] = L""; 
	TCHAR szCurrentPath[MAX_PATH] = L"";
	// ���� ��� ������ GetCurrentDirectory
	// ���� ��ο��� ���� ���ϴ� ��α����� ��θ� ����η� ��ȯ PathRelativePathTo
	GetCurrentDirectory(MAX_PATH, szCurrentPath); 
	// �� �Լ��� ���� ��ο��� ��� ��η� ��ȯ���ִ� �Լ�. 
	// ��, ���� ����̺꿡���� ��� �ֵ� ã�Ƴ��� ���� �׷���. ����̺갡 �ٸ��� �Ұ�. 
	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY, strFileFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);
	return CString(szRelativePath);
}
