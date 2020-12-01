#pragma once
class CMFCToolView;
class CGraphic_Device;
class CItem
{
public:
	CItem();
	~CItem();

public:
	void AddItem(ITEMDATA * _pItem);
	void ItemRender(const wstring& _strImageKey , const wstring& _strImageState);
	const ITEMDATA* NearItemFind();
	void Release();
public:
	const vector<ITEMDATA*>& GetItemVec() { return m_vecItem; }
private:
	vector<ITEMDATA*> m_vecItem;
	CGraphic_Device* m_pDevice;
	CMFCToolView* m_pToolView;
	
};

