#include "stdafx.h"
#include "PlayerUI.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "BaseLand.h"

CPlayerUI::CPlayerUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CPlayerUI::~CPlayerUI(void)
{

}

HRESULT CPlayerUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXCreateSprite(m_pGraphicDev, &m_pSprite);

	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Red.png",
		&m_pRedTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Green.png",
		&m_pGreenTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Yellow.png",
		&m_pYellowTex);

	return S_OK;
}

void CPlayerUI::Initialize_Object(void)
{
}

int CPlayerUI::Update_Object(const float& fTimeDelta)
{
	//여기서 정보받을거야 ㅋ
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CPlayerUI::Render_Object(void)
{
	return;
	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	TCHAR szBuff[32] = L"";
	//	wsprintf(szBuff, L"x :%d, y :%d", int(m_fRight), int(m_fUp));
	//	MessageBox(nullptr, szBuff, L"XY", 0);
	//}
	//if (GetAsyncKeyState(VK_RIGHT))
	//	m_fRight += 1.f;
	//if (GetAsyncKeyState(VK_LEFT))
	//	m_fRight -= 1.f;

	//if (GetAsyncKeyState(VK_UP))
	//	m_fUp -= 10.f;
	//if (GetAsyncKeyState(VK_DOWN))
	//	m_fUp += 10.f;
	//m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 0.f, 0);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX matTrans = {};


	D3DXMatrixTranslation(&matTrans, 100.f, 50.f, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(m_pRedTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&matTrans, 100.f, 80.f, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(m_pGreenTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&matTrans, 300, 880, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(m_pYellowTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	m_pSprite->End();
}

void CPlayerUI::Free(void)
{
	/*m_pYellowTex->Release();
	m_pRedTex->Release();
	m_pGreenTex->Release();*/
	m_pSprite->Release();
	Engine::CGameObject::Free();
}


HRESULT CPlayerUI::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	return S_OK;
}

CPlayerUI* CPlayerUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerUI*		pInstance = new CPlayerUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

