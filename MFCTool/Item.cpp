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
	m_pToolView = ((CMainFrame*)AfxGetMainWnd())->m_pToolView;

	ITEMDATA* pItme = new ITEMDATA(*_pItem);
	pItme->vPos = D3DXVECTOR3((float)GetMouse().x + m_pToolView->GetScrollPos(0), 
		(float)GetMouse().y + m_pToolView->GetScrollPos(1), 0.f);
	m_vecItem.emplace_back(pItme);

	CString strIndexName;
	int iSize = m_vecItem.size() - 1;
	
	strIndexName.Format(_T("%d"), iSize);
	((CMainFrame*)AfxGetMainWnd())->m_pFormView->m_tItemTool.m_InstantList.AddString(strIndexName);
}

void CItem::ItemRender(const wstring& _strImageKey, const wstring& _strImageState)
{
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());			
	m_pToolView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
	D3DXMATRIX matScale, matTrans;
				
	if (m_vecItem.empty())
		return;

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		TCHAR szBuf[MAX_PATH] = L"";
		swprintf_s(szBuf, L"%d", i);

		const TEXINFO* pTexture = CTextureMgr::Get_Instance()->Get_TexInfo(_strImageKey, _strImageState,  m_vecItem[i]->byDrawID);
		if (!pTexture)
		{
			ERR_MSG(L" 텍스처 못찾음 ");
			return;
		}

		float fX = float(pTexture->tImageInfo.Width >> 1);
		float fY = float(pTexture->tImageInfo.Height >> 1);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,   m_vecItem[i]->vPos.x - m_pToolView->GetScrollPos(0),
			m_vecItem[i]->vPos.y - m_pToolView->GetScrollPos(1),
			0.f);

		matScale *= matTrans;
		m_pDevice->Get_Sprite()->SetTransform(&matScale);
		m_pDevice->Get_Sprite()->Draw(pTexture->pTexture, nullptr, &D3DXVECTOR3(fX, fY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf),nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
}


const ITEMDATA * CItem::NearItemFind()
{
	//안씀
	if (m_vecItem.empty())
		return nullptr;

	float fDis = 0.f;
	ITEMDATA* pTargetItme = nullptr;


	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{

	}
	/*for (auto & pItme : m_vecItem)
	{
		float fX = GetMouse().x - pItme->vPos.x;
		float fY = GetMouse().y - pItme->vPos.y;
		float fCurDis = D3DXVec3Length(&D3DXVECTOR3(fX, fY, 0.f));
		if (fDis > fCurDis || !pTargetItme)
		{
			pTargetItme = pItme;
			fDis = fCurDis;
		}
	}*/
	return pTargetItme;
}


void CItem::Release()
{
	for_each(m_vecItem.begin(), m_vecItem.end(), Safe_Delete<ITEMDATA*>);
	m_vecItem.clear();
	m_vecItem.swap(vector<ITEMDATA*>());
}
