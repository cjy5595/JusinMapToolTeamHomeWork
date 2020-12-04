#pragma once

class CGraphic_Device;
class CMFCToolView;
class CMonster
{
public:
	CMonster();
	~CMonster();


private:
	vector<ITEMDATA*> m_vecItem;
	CGraphic_Device* m_pDevice;
	CMFCToolView* m_pToolView;
};

