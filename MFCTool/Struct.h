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
	D3DXVECTOR3			vPos; //������ ��ġ
	D3DXVECTOR3			vSize; // ������
	BYTE				byOption; // ������������� ������������
	BYTE				byDrawID; // ���� �̹��� �ε���

	int iAddHp;		//�߰��Ǵ� ü�� ����
	int iAttack;	//����
	int iSpeed;		//
	
}ITEMDATA;