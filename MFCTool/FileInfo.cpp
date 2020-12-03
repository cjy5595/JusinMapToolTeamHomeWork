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
	// 현재 경로 얻어오고 GetCurrentDirectory
	// 현재 경로에서 내가 원하는 경로까지의 경로를 상대경로로 변환 PathRelativePathTo
	GetCurrentDirectory(MAX_PATH, szCurrentPath); 
	// 이 함수가 절대 경로에서 상대 경로로 변환해주는 함수. 
	// 단, 같은 드라이브에서는 어디에 있든 찾아낼수 있음 그러나. 드라이브가 다르면 불가. 
	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY, strFileFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);
	return CString(szRelativePath);
}
