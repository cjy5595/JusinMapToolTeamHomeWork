#pragma once
#include "Texture.h"
class CMulti_Texture :
	public CTexture
{
public:
	explicit CMulti_Texture();
	virtual ~CMulti_Texture();

public:
	// CTexture��(��) ���� ��ӵ�
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const int & iIndex = 0) override;
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iIndex = 0) override;
	virtual void Release_Texture() override;
private:
	// ���� ���� Ű���� ? StateKey
	map<wstring, vector<TEXINFO*>> m_mapTexture;
};

