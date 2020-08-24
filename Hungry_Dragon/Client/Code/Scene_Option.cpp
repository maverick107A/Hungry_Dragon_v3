#include "stdafx.h"
#include "Scene_Option.h"
#include "Ingame_Flow.h"

#include "Export_Function.h"

CScene_Option::CScene_Option(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Option::~CScene_Option(void) {

}

HRESULT CScene_Option::Ready_Scene(void) {
	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	_matrix matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matIdentity);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matIdentity);

	return S_OK;
}

_int CScene_Option::Update_Scene(const _float& fTimeDelta) {
	_int iExit = Engine::CScene::Update_Scene(fTimeDelta);


	


	
	
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		--m_uFocusNum;
		if (99< m_uFocusNum)
		{
			m_uFocusNum = 3;
		}
		Engine::Get_FMOD()->PlayEffect(L"MouseOn");
	}
	
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_uFocusNum = (m_uFocusNum + 1) % 4;
		Engine::Get_FMOD()->PlayEffect(L"MouseOn");
	}


	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		switch (m_uFocusNum)
		{
		case 0:
			Get_FMOD()->Add_BgmVolume(-0.1f);
			break;
		case 1:
			Get_FMOD()->Add_SfxVolume(-0.1f);
			break;
		case 2:

			break;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		switch (m_uFocusNum)
		{
		case 0:
			Get_FMOD()->Add_BgmVolume(0.1f);
			break;
		case 1:
			Get_FMOD()->Add_SfxVolume(0.1f);
			break;
		case 2:

			break;
		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {

		switch (m_uFocusNum)
		{
		case 0:
			
			
			break;
		case 1:

			break;
		case 2:

			break;
		case 3:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_MENU);
			
			break;
		}
		//CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_PROTO);
		return -1;
	}

	//if (Engine::Get_DIKeyState(DIK_RETURN) & 0x80)
	//{
	//	Engine::CScene*		pScene = nullptr;
	//
	//	pScene = CScene_Proto::Create(m_pGraphicDev);
	//	NULL_CHECK_RETURN(pScene, -1);
	//
	//	//FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
	//
	//	return -1;
	//}
	return iExit;
}

void CScene_Option::Render_Scene(void) {
	// debug용
	TCHAR str[128] = L"";

	wsprintf(str, L"옵션");
	Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 150.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	wsprintf(str, L"사운드");
	Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 300.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	wsprintf(str, L"배경음 : %.2d", (int)(Get_FMOD()->Get_BgmVolume()*10.f));
	Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 350.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	wsprintf(str, L"효과음 : %.2d", (int)(Get_FMOD()->Get_SfxVolume()*10.f));
	Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 400.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	wsprintf(str, L"조작");
	Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 500.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	wsprintf(str, L"마우스 감도 : %d", 5);
	Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 550.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

	wsprintf(str, L"확인", 0);
	Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 800.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

	switch (m_uFocusNum)
	{
	case 0:
		wsprintf(str, L"사운드");
		Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 300.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		wsprintf(str, L"◀ 배경음 : %.2d ▶", (int)(Get_FMOD()->Get_BgmVolume()*10.f));
		Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 350.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		break;
	case 1:
		wsprintf(str, L"사운드");
		Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 300.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		wsprintf(str, L"◀ 효과음 : %.2d ▶", (int)(Get_FMOD()->Get_SfxVolume()*10.f));
		Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 400.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		break;
	case 2:
		wsprintf(str, L"조작");
		Engine::Render_Font_Center(L"Font_Bold", str, &_vec2(1600.f, 500.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		wsprintf(str, L"◀ 마우스 감도 : %d ▶", 0);
		Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 550.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		break;
	case 3:
		wsprintf(str, L"▶ 확인 ◀", 0);
		Engine::Render_Font_Center(L"Font_Light", str, &_vec2(1600.f, 800.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		break;
	}
	
	

	Engine::CScene::Render_Scene();
}

void CScene_Option::Free(void) 
{
	Engine::CScene::Free();

}

CScene_Option* CScene_Option::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Option*	pInstance = new CScene_Option(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Option::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// BackGround
	pGameObject = CBackGround_Logo::Create(m_pGraphicDev, 1);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"LogoOption", pGameObject), E_FAIL);

	

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Option::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	

	return S_OK;
}
