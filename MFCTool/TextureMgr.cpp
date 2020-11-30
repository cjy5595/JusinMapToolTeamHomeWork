#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"

CTextureMgr* CTextureMgr::m_pInstance = nullptr;
CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release_TextureMgr();
}

const TEXINFO * CTextureMgr::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter_Find = m_mapTexture.find(wstrObjectKey);
	if (m_mapTexture.end() == iter_Find)
		return nullptr;

	return iter_Find->second->Get_TexInfo(wstrStateKey, iIndex);
}

HRESULT CTextureMgr::Insert_Texture_Manager(TEX_ID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter_Find = m_mapTexture.find(wstrObjectKey);
	// 이때는 어떤 상황? - 제일 처음 집어넣ㄴ느 그런 상황. 
	CTexture* pTexture = nullptr;
	if (m_mapTexture.end() == iter_Find)
	{
		switch (eTexID)
		{
		case CTextureMgr::MULTI_TEX:
			pTexture = new CMulti_Texture;
			break;
		case CTextureMgr::SINGLE_TEX:
			pTexture = new CSingle_Texture;
			break;
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, iIndex)))
		{
			ERR_MSG(L"TextureManager Insert Faield");
			return E_FAIL;
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (eTexID == MULTI_TEX)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, iIndex)))
		{
			ERR_MSG(L"TextureManager MultiTexture Insert Faield");
			return E_FAIL;
		}
	}
	return S_OK;
}

void CTextureMgr::Release_TextureMgr()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second);

	m_mapTexture.clear();
}
