#pragma once
class CMFCToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
	void Set_Ratio(D3DXMATRIX matWorld, float fRatioX, float fRatioY);
public:
	void TileChange(const D3DXVECTOR3& vMousePos, const BYTE& byDrawID, const BYTE& byOption = 0);
	int GetTile(const D3DXVECTOR3& vMousePos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int& iIndex);
public:
	HRESULT Ready_Terrain();
	void	Render_Terrain();
	void	MiniRender_Terrain();
	void	Release_Terrain();

private:
	CMFCToolView* m_pView;
	vector<TILE*> m_vecTile;
public:
	int m_iTileCountX = 0;
	int m_iTileCountY = 0;

	int m_iTileSizeX = 0;
	int m_iTileSizeY = 0;

	int m_iDrawID = 0;
	int m_iOption = 0;

};

