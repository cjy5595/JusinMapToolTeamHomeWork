#pragma once
class CGraphic_Device final
{
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device;

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
private:
	explicit CGraphic_Device();
	~CGraphic_Device();
	// 복사 생성자, 디폴트 대입연산자. 
	explicit CGraphic_Device(const CGraphic_Device& rObject) {};
	void operator=(const CGraphic_Device& rObject) {};

public:
	LPDIRECT3DDEVICE9	Get_Device() { return m_pDevice; }
	LPD3DXSPRITE		Get_Sprite() { return m_pSprite; }
	LPD3DXFONT			Get_Font()	 { return m_pFont; }

public:
	HRESULT Ready_Graphic_Device();
	void Release_Graphic_Device();
	void Render_Begin();
	void Render_End(HWND hWND = nullptr);

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;
	static CGraphic_Device* m_pInstance;
};

