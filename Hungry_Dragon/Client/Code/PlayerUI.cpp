#include "stdafx.h"
#include "PlayerUI.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "BaseLand.h"
#include "PlayerMain.h"

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
		L"../../Asset/HUD/gagebar00.png",
		&m_pRedTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../../Asset/HUD/gagebar01.png",
		&m_pGreenTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../../Asset/HUD/gagebar02.png",
		&m_pYellowTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../../Asset/HUD/gagebar04.png",
		&m_pPurpleTex);

	return S_OK;
}

void CPlayerUI::Initialize_Object(void)
{
	m_pPlayer = static_cast<Engine::CPlayerMain*>(Engine::Get_Object(L"GameLogic", L"TestPlayer"));
}

int CPlayerUI::Update_Object(const float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CPlayerUI::Render_Object(void)
{
	return;									//================================= ��Ȱ��ȭ ====================================================================
	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	TCHAR szBuff[32] = L"";
	//	wsprintf(szBuff, L"x :%d, y :%d", int(m_fRight), int(m_fUp));
	//	MessageBox(nullptr, szBuff, L"XY", 0);
	//}
	if (GetAsyncKeyState(VK_RIGHT))
		m_fRight += 1.f;
	if (GetAsyncKeyState(VK_LEFT))
		m_fRight -= 1.f;

	//if (GetAsyncKeyState(VK_UP))
	//	m_fUp -= 10.f;
	//if (GetAsyncKeyState(VK_DOWN))
	//	m_fUp += 10.f;
	//m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 0.f, 0);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX matScale = {};
	D3DXMATRIX matTrans = {};
	D3DXMATRIX matWorld = {};

	RECT tRect = { 0,0,int(m_pPlayer->Get_Hp()),128 };

	D3DXMatrixScaling(&matScale, 1.f, 0.2f, 0.f);
	D3DXMatrixTranslation(&matTrans, 100.f, 50.f, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pRedTex, &tRect, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	tRect = { 0,0,int(m_pPlayer->Get_Mana()),128 };

	D3DXMatrixTranslation(&matTrans, 100.f, 80.f, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pGreenTex, &tRect, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	tRect = { 0,0,int(m_pPlayer->Get_Stamina()),128 };

	D3DXMatrixTranslation(&matTrans, 100.f, 110.f, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pYellowTex, &tRect, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	tRect = { 0,0,int(m_pPlayer->Get_Stamina()),128};

	D3DXMatrixTranslation(&matTrans, 300.f, 680.f, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pPurpleTex, &tRect, nullptr, nullptr, D3DCOLOR_ARGB(155, 255, 255, 255));



	m_pSprite->End();
}

void CPlayerUI::Free(void)
{
	m_pYellowTex->Release();
	m_pRedTex->Release();
	m_pGreenTex->Release();
	m_pPurpleTex->Release();
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

