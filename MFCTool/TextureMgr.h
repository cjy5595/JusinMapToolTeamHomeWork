#pragma once
class CTexture;
class CTextureMgr
{
public:
	static CTextureMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTextureMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	enum TEX_ID { MULTI_TEX, SINGLE_TEX };
public:
	CTextureMgr();
	~CTextureMgr();

public:
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iIndex = 0);
	HRESULT Insert_Texture_Manager(TEX_ID eTexID, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iIndex = 0);
	void Release_TextureMgr();
private:
	static CTextureMgr* m_pInstance;
	map<wstring, CTexture*> m_mapTexture;
};

