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
	BYTE byDrawID;
	BYTE byOption;
}TILE;

typedef struct tagItem
{
	tagItem(tagItem &_rItem){}
#ifdef _AFX
	CString strName;
#else 
	wstring strName;
#endif
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;

	int iAddHp;
	int iAttack;
	int iDef;
	
	BYTE byWeapon;
	BYTE byItem;
}ITEMDATA;