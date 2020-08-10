#include "stdafx.h"
#include "Logo.h"
#include "Scene_Proto.h"
#include "Scene_Cave.h"

#include "Export_Function.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CLogo::~CLogo(void) {

}

HRESULT CLogo::Ready_Scene(void) {
	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	m_pLoading = CScene_Loading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	return S_OK;
}

_int CLogo::Update_Scene(const _float& fTimeDelta) {
	_int iExit = Engine::CScene::Update_Scene(fTimeDelta);

	if (true == m_pLoading->Get_Finish()) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			Engine::CScene*		pScene = nullptr;

			//pScene = CScene_Proto::Create(m_pGraphicDev);
			pScene = CScene_Cave::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, -1);
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
	}

	return iExit;
}

void CLogo::Render_Scene(void) {
	// debug¿ë
	Engine::Render_Font(L"Font_Jinji", m_pLoading->Get_String(), &_vec2(10.f, 10.f), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
	Engine::CScene::Render_Scene();
}

void CLogo::Free(void) 
{
	Engine::Safe_Release(m_pLoading);
	Engine::CScene::Free();

}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CLogo*	pInstance = new CLogo(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CLogo::Ready_Layer_UI(const _tchar* pLayerTag) {
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

HRESULT CLogo::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TexSquare",
		Engine::BUFFER_TEXSQUARE),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_LOGO,
		L"Texture_Logo",
		Engine::TEX_NORMAL,
		L"../../Asset/Loading/Loading.png"),
		E_FAIL);

	return S_OK;
}
