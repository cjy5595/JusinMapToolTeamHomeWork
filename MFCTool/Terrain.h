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
	void Set_TileData(TILE* pTile) { return m_vecTile.emplace_back(pTile); }
	vector<TILE*>& Get_vecTile() { return m_vecTile; }
public:
	void TileChange(const D3DXVECTOR3 & vPos, const int & byDrawID, const BYTE & byOption = 0);
public:
	HRESULT Ready_Terrain();
	void	Render_Terrain();
	void	Release_Terrain();
private:
	CMFCToolView* m_pView;
	vector<TILE*> m_vecTile;
public:
	TERRAININFO m_tTerrainInfo;
	//int	m_iTotalCount = 0;
	//int m_iTileCountX = 0;
	//int m_iTileCountY = 0;

	float m_fTileCX = 0;
	float m_fTileCY = 0;
	int m_iTileSizeX = 0;
	int m_iTileSizeY = 0;

	int m_iDrawID = 0;
	int m_iOption = 0;

	bool m_bText = false;
	bool m_bGrid = false;

};

