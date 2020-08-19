#include "stdafx.h"
#include "Scene_Select.h"
#include "Ingame_Flow.h"

#include "Export_Function.h"

CScene_Select::CScene_Select(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Select::~CScene_Select(void) {

}

HRESULT CScene_Select::Ready_Scene(void) {
	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	Engine::Get_FMOD()->PlayBgm(L"SelectBgm");

	return S_OK;
}

_int CScene_Select::Update_Scene(const _float& fTimeDelta) {
	_int iExit = Engine::CScene::Update_Scene(fTimeDelta);

	
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		--m_uFocusNum;
		if (0 > m_uFocusNum)
		{
			m_uFocusNum = 3;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		--m_uFocusNum;
		if (0 > m_uFocusNum)
		{
			m_uFocusNum = 3;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_uFocusNum = (m_uFocusNum + 1) % 4;
	}
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_uFocusNum = (m_uFocusNum + 1) % 4;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {

		switch (m_uFocusNum)
		{
		case 0:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_FOREST);
			break;
		case 1:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_CAVE);
			break;
		case 2:
			CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_CLOUD);
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

void CScene_Select::Render_Scene(void) {
	// debug용
	TCHAR str[32] = L"";
	switch (m_uFocusNum)
	{
	case 0:
		wsprintf(str, L"1스테이지 : 숲");
		break;
	case 1:
		wsprintf(str, L"2스테이지 : 동굴");
		break;
	case 2:
		wsprintf(str, L"3스테이지 : 구름");
		break;
	case 3:
		wsprintf(str, L"4스테이지 : 화산");
		//CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_VOLCANO);
		//CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_ICELAND);
		break;
	}
	
	Engine::Render_Font(L"Font_Default", str, &_vec2(300.f, 450.f), D3DXCOLOR(0.f, 1.f, 1.f, 1.f));

	Engine::CScene::Render_Scene();
}

void CScene_Select::Free(void) 
{
	Engine::CScene::Free();

}

CScene_Select* CScene_Select::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Select*	pInstance = new CScene_Select(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Select::Ready_Layer_UI(const _tchar* pLayerTag) {
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

HRESULT CScene_Select::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	

	return S_OK;
}
