#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"
#include "TextureMgr.h"
#include "Graphic_Device.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_Terrain();
}

void CTerrain::Set_Ratio(D3DXMATRIX matWorld, float fRatioX, float fRatioY)
{
	/*
	x	y	z	w
	x	11	12	13	14
	y	21	22	23	24
	z	31	32	33	34
	w	41	42	43	44
	*/

	matWorld._11 *= fRatioX;
	matWorld._21 *= fRatioX;
	matWorld._31 *= fRatioX;
	matWorld._41 *= fRatioX;

	matWorld._12 *= fRatioY;
	matWorld._22 *= fRatioY;
	matWorld._32 *= fRatioY;
	matWorld._42 *= fRatioY;
}

void CTerrain::TileChange(const D3DXVECTOR3 & vPos, const int & byDrawID, const BYTE & byOption)
{
	if (m_vecTile.empty())
		return;

	//float x = float(vPos.x / m_iTileSizeX);
	//float y = float(vPos.y / m_iTileSizeY);
	float x = float(vPos.x / m_tTerrainInfo.iTileSizeX);
	float y = float(vPos.y / m_tTerrainInfo.iTileSizeY);
	int iIdx = ((int)y * m_tTerrainInfo.iTileCountX + (int)x);

	if (0 > iIdx || (size_t)iIdx >= m_vecTile.size())
		return;

	m_vecTile[iIdx]->byDrawID = byDrawID;
	m_vecTile[iIdx]->byOption = byOption;

}

HRESULT CTerrain::Ready_Terrain()
{
	// 일단. 우리 규칙 찾자. 
	float fCenterX = 0.f, fCenterY = 0.f;
	TILE* pTile = nullptr;
	m_tTerrainInfo.iTotalCount = m_tTerrainInfo.iTileCountX *  m_tTerrainInfo.iTileCountY;
	m_vecTile.reserve(m_tTerrainInfo.iTotalCount);
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_iDrawID);
	if (nullptr == pTexInfo)
		return E_FAIL;

	//m_fTileCX = float(pTexInfo->tImageInfo.Width); // 1-1 픽셀단위로 크기를 넣으면 비율에 맞게 사이즈를 정할수 있음.
	//m_fTileCY = float(pTexInfo->tImageInfo.Height);

	for (int i = 0; i < m_tTerrainInfo.iTileCountX; ++i)
	{
		for (int j = 0; j < m_tTerrainInfo.iTileCountY; ++j)
		{
			pTile = new TILE;
			pTile->fTileCX = float(pTexInfo->tImageInfo.Width); // 1-1 픽셀단위로 크기를 넣으면 비율에 맞게 사이즈를 정할수 있음.
			pTile->fTileCY = float(pTexInfo->tImageInfo.Height);
			pTile->iTileSizeX = m_iTileSizeX;
			pTile->iTileSizeY = m_iTileSizeY;
			m_tTerrainInfo.iTileSizeX = m_iTileSizeX;
			m_tTerrainInfo.iTileSizeY = m_iTileSizeY;

			pTile->vSize = { (float)m_iTileSizeX / pTile->fTileCX , (float)m_iTileSizeY / pTile->fTileCY, 0.f }; // 1-1
			pTile->byDrawID = m_iDrawID;
			pTile->byOption = m_iOption;
			fCenterX = float(j * m_iTileSizeX);
			fCenterY = float(i * m_iTileSizeY);
			pTile->vPos = { fCenterX + ((float)m_iTileSizeX * 0.5f),fCenterY + ((float)m_iTileSizeY * 0.5f), 0.f };
			m_vecTile.emplace_back(pTile);
		}
	}

	return S_OK;
}

void CTerrain::Render_Terrain()
{
	if (m_vecTile.empty())
		return;

	int iIndex = 0;
	TCHAR szBuf[MAX_PATH] = L"";
	RECT rcView = {};
	m_pView->GetWindowRect(&rcView);
	SetRect(&rcView, 0, 0, rcView.right - rcView.left, rcView.bottom - rcView.top);
	float fRatioX = float(WINCX) / rcView.right;
	float fRatioY = float(WINCY) / rcView.bottom;
	for (int i = 0; i < m_tTerrainInfo.iTileCountY; ++i)
	{
		for (int j = 0; j < m_tTerrainInfo.iTileCountX; ++j)
		{
			iIndex = j + (i * m_tTerrainInfo.iTileCountX);
			swprintf_s(szBuf, L"%d", iIndex);
			const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
			if (nullptr == pTexInfo)
				return;

			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			D3DXMATRIX matScale, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pView->GetScrollPos(0), m_vecTile[iIndex]->vPos.y - m_pView->GetScrollPos(1), 0.f);
			matWorld = matScale * matTrans;

			Set_Ratio(matWorld, fRatioX, fRatioY);
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			if (m_bText)
				CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			
			D3DXVECTOR2 vLinePos[5] =
			{ { fCenterX -m_fTileCX * 0.5f, fCenterY - m_fTileCY * 0.5f },
			{ fCenterX + m_fTileCX * 0.5f, fCenterY - m_fTileCY * 0.5f },
			{ fCenterX + m_fTileCX * 0.5f, fCenterY + m_fTileCY * 0.5f },
			{ fCenterX - m_fTileCX * 0.5f, fCenterY + m_fTileCY * 0.5f },
			{ fCenterX - m_fTileCX * 0.5f, fCenterY - m_fTileCY * 0.5f } };
			if (m_bGrid)
			{
				CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(5);
				CGraphic_Device::Get_Instance()->Get_Line()->Draw(vLinePos, 5, D3DCOLOR_ARGB(200, 255, 200, 0));
			}
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
	}
}

void CTerrain::Release_Terrain()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.swap(vector<TILE*>());
}
