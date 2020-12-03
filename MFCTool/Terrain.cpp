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

void CTerrain::TileChange(const D3DXVECTOR3 & vMousePos, const BYTE & byDrawID, const BYTE & byOption)
{
	int iIndex = GetTile(vMousePos);

	if (-1 == iIndex)
		return;
 	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
}

int CTerrain::GetTile(const D3DXVECTOR3 & vMousePos)
{
	size_t iSize = m_vecTile.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (IsPicking(vMousePos, i))
			return i;
	}
	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, const int & byDrawID, const BYTE & byOption)
{
	float x = float(vPos.x / m_iTileSizeX);
	float y = float(vPos.y / m_iTileSizeY);
	int iIdx = ((int)y * m_iTileCountX + (int)x);

	if (0 > iIdx || (size_t)iIdx >= m_vecTile.size())
		return false;

	m_vecTile[iIdx]->byDrawID = byDrawID;
	m_vecTile[iIdx]->byOption = byOption;
	return true;

	////////////////////////////내적을 이용한 방법.////////////////////////////////////////////////
	//// 챕터 1. 마름모꼴을 구해내라!

	//D3DXVECTOR3 vVertex[4] =
	//{
	//	{ m_vecTile[iIndex]->vPos.x - (m_iTileSizeX / m_fTileCX * 0.5f), m_vecTile[iIndex]->vPos.y - (m_iTileSizeY / m_fTileCY * 0.5f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x + (m_iTileSizeX / m_fTileCX * 0.5f), m_vecTile[iIndex]->vPos.y - (m_iTileSizeY / m_fTileCY * 0.5f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x + (m_iTileSizeX / m_fTileCX * 0.5f), m_vecTile[iIndex]->vPos.y + (m_iTileSizeY / m_fTileCY * 0.5f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x - (m_iTileSizeX / m_fTileCX * 0.5f), m_vecTile[iIndex]->vPos.y + (m_iTileSizeY / m_fTileCY * 0.5f), 0.f },
	//};
	//// 챕터 2. 방향벡터 그것도 마름모꼴의 방향벡터. 

	//D3DXVECTOR3 vVertexDir[4] =
	//{
	//	vVertex[1] - vVertex[0],
	//	vVertex[2] - vVertex[1],
	//	vVertex[3] - vVertex[2],
	//	vVertex[0] - vVertex[3],

	//};

	////챕터 3. 법선벡터를 뽑아내자!!! 
	//D3DXVECTOR3 vBubsun[4] =
	//{
	//	{ -vVertexDir[0].y, vVertexDir[0].x, 0.f },
	//	{ -vVertexDir[1].y, vVertexDir[1].x, 0.f },
	//	{ -vVertexDir[2].y, vVertexDir[2].x, 0.f },
	//	{ -vVertexDir[3].y, vVertexDir[3].x, 0.f }
	//};

	//// 챕터 4. 마름모꼴 정점에서 마우스를 바라보는 방향벡터를 구하자!!!! 

	//D3DXVECTOR3 vMouseDir[4];
	//for (int i = 0; i < 4; ++i)
	//	vMouseDir[i] = vPos - vVertex[i];

	//for (int i = 0; i < 4; ++i)
	//{
	//	D3DXVec3Normalize(&vBubsun[i], &vBubsun[i]);
	//	D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	//}

	//for (int i = 0; i < 4; ++i)
	//{
	//	if (0 < D3DXVec3Dot(&vMouseDir[i], &vBubsun[i]))
	//		return false;
	//}

	//return true;
}

HRESULT CTerrain::Ready_Terrain()
{
	// 일단. 우리 규칙 찾자. 
	float fCenterX = 0.f, fCenterY = 0.f;
	TILE* pTile = nullptr;
	m_vecTile.reserve(m_iTileCountX * m_iTileCountY);
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_iDrawID);
	if (nullptr == pTexInfo)
		return E_FAIL;

	m_fTileCX = float(pTexInfo->tImageInfo.Width); // 1-1 픽셀단위로 크기를 넣으면 비율에 맞게 사이즈를 정할수 있음.
	m_fTileCY = float(pTexInfo->tImageInfo.Height);

	for (int i = 0; i < m_iTileCountY; ++i)
	{
		for (int j = 0; j < m_iTileCountX; ++j)
		{
			pTile = new TILE;
			pTile->vSize = { (float)m_iTileSizeX / m_fTileCX , (float)m_iTileSizeY / m_fTileCY, 0.f }; // 1-1
			pTile->byDrawID = m_iDrawID;
			pTile->byOption = m_iOption;
			fCenterX = float(j * m_iTileSizeX);
			fCenterY = float(i * m_iTileSizeY);
			pTile->vPos = { fCenterX,fCenterY, 0.f };
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
	for (int i = 0; i < m_iTileCountY; ++i)
	{
		for (int j = 0; j < m_iTileCountX; ++j)
		{
			iIndex = j + (i * m_iTileCountX);
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
				CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
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
