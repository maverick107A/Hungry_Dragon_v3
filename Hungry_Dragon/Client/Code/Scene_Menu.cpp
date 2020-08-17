#include "stdafx.h"
#include "Scene_Menu.h"
#include "Ingame_Flow.h"

#include "Export_Function.h"

CScene_Menu::CScene_Menu(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Menu::~CScene_Menu(void) {

}

HRESULT CScene_Menu::Ready_Scene(void) {
	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);


	return S_OK;
}

_int CScene_Menu::Update_Scene(const _float& fTimeDelta) {
	_int iExit = Engine::CScene::Update_Scene(fTimeDelta);

	
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		--m_uFocusNum;
		if (2< m_uFocusNum)
		{
			m_uFocusNum = 2;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		--m_uFocusNum;
		if (2< m_uFocusNum)
		{
			m_uFocusNum = 2;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_uFocusNum = (m_uFocusNum + 1) % 3;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_uFocusNum = (m_uFocusNum + 1) % 3;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {

		switch (m_uFocusNum)
		{
		case 0:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_SELECT);
			break;
		case 1:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_OPTION);
			break;
		case 2:
			PostQuitMessage(0);
			break;
		case 3:
			//CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_VOLCANO);
			//CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_ICELAND);
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

void CScene_Menu::Render_Scene(void) {
	// debug용
	TCHAR str[128] = L"";
	wsprintf(str, L"배고픈 용가리");
	Engine::Render_Font(L"Font_Jinji", str, &_vec2(400.f, 200.f), D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
	switch (m_uFocusNum)
	{
	case 0:
		wsprintf(str, L"게임 시작");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 450.f), D3DXCOLOR(0.f, 1.f, 1.f, 1.f));
		wsprintf(str, L"옵션 설정");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 550.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		wsprintf(str, L"게임 종료");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 650.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		break;
	case 1:
		wsprintf(str, L"게임 시작");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 450.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		wsprintf(str, L"옵션 설정");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 550.f), D3DXCOLOR(0.f, 1.f, 1.f, 1.f));
		wsprintf(str, L"게임 종료");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 650.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		break;
	case 2:
		wsprintf(str, L"게임 시작");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 450.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		wsprintf(str, L"옵션 설정");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 550.f), D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f));
		wsprintf(str, L"게임 종료");
		Engine::Render_Font(L"Font_Default", str, &_vec2(400.f, 650.f), D3DXCOLOR(0.f, 1.f, 1.f, 1.f));
		break;
	}
	
	

	Engine::CScene::Render_Scene();
}

void CScene_Menu::Free(void) 
{
	Engine::CScene::Free();

}

CScene_Menu* CScene_Menu::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Menu*	pInstance = new CScene_Menu(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Menu::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// BackGround
	pGameObject = CBackGround_Logo::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"BackGround", pGameObject), E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Menu::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	

	return S_OK;
}
