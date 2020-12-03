#pragma once

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImageInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	int iTileSizeX;
	int iTileSizeY;
	float fTileCX;
	float fTileCY;
	int byDrawID;
	BYTE byOption;
}TILE;

typedef struct tagTerrainInfo
{
	int	iTotalCount;
	int iTileCountX;
	int iTileCountY;
	int iTileSizeX;
	int iTileSizeY;
}TERRAININFO;

typedef struct tagItem
{
	tagItem() {}
	tagItem(tagItem &_rItem) {	strName = _rItem.strName;}
#ifdef _AFX
	CString strName;
#else 
	wstring strName;
#endif
	D3DXVECTOR3			vPos; //아이템 위치
	D3DXVECTOR3			vSize; // 사이즈
	BYTE				byOption; // 무기아이템인지 사용아이템인지
	BYTE				byDrawID; // 무기 이미지 인덱스

	int iAddHp;		//추가되는 체력 스펙
	int iAttack;	//공격
	int iSpeed;		//
	
}ITEMDATA;