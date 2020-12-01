#include "stdafx.h"
#include "Item.h"
#include "TextureMgr.h"
#include "Graphic_Device.h"
#include "MFCToolView.h"
#include "MainFrm.h"
CItem::CItem() : m_pDevice(CGraphic_Device::Get_Instance()) , m_pToolView(nullptr)
{
}


CItem::~CItem()
{
	Release();
}

void CItem::AddItem(ITEMDATA * _pItem)
{
	ITEMDATA* pItem = new ITEMDATA(*_pItem);
	m_vecItem.emplace_back(pItem);
	Safe_Delete(pItem);
}

void CItem::ItemRender(const wstring& _strImageKey, const wstring& _strImageState)
{
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());			
	m_pToolView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
	D3DXMATRIX matScale, matTrans;
																							
																							/*CString str;
																							wstring wstr;
																							wstr  = str.operator LPCWSTR();*/

	for (auto & pItme : m_vecItem)
	{
		const TEXINFO* pTexture = CTextureMgr::Get_Instance()->Get_TexInfo(_strImageKey, _strImageState, pItme->byDrawID);
		float fX = float(pTexture->tImageInfo.Width >> 1);
		float fY = float(pTexture->tImageInfo.Height >> 1);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, pItme->vPos.x - m_pToolView->GetScrollPos(0), 
			pItme->vPos.y - m_pToolView->GetScrollPos(1), 
			0.f); 

		matScale *= matTrans;
		m_pDevice->Get_Sprite()->SetTransform(&matScale);
		m_pDevice->Get_Sprite()->Draw(pTexture->pTexture, nullptr, &D3DXVECTOR3(fX, fY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

const ITEMDATA * CItem::NearItemFind()
{
	if (m_vecItem.empty())
		return nullptr;

	float fDis = 0.f;
	ITEMDATA* pTargetItme = nullptr;
	for (auto & pItme : m_vecItem)
	{
		float fX = GetMouse().x - pItme->vPos.x;
		float fY = GetMouse().y - pItme->vPos.y;
		float fCurDis = D3DXVec3Length(&D3DXVECTOR3(fX, fY, 0.f));
		if (fDis > fCurDis || !pTargetItme)
		{
			pTargetItme = pItme;
			fDis = fCurDis;
		}
	}
	return pTargetItme;
}


void CItem::Release()
{
	for_each(m_vecItem.begin(), m_vecItem.end(), Safe_Delete<ITEMDATA*>);
	m_vecItem.clear();
	m_vecItem.swap(vector<ITEMDATA*>());
}
