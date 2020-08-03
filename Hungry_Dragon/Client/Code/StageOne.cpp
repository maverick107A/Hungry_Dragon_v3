#include "stdafx.h"
#include "StageOne.h"

#include "Export_Function.h"
#include "TerrainPlayer.h"


CStageOne::CStageOne(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{

}

CStageOne::~CStageOne(void)
{
	int i = 0;
}

HRESULT CStageOne::Ready_Scene(void)
{

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);



	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		10000.f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);


	return S_OK;
}

_int CStageOne::Update_Scene(const _float& fTimeDelta)
{
	Engine::CScene::Update_Scene(fTimeDelta);

	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	return 0;
}

void CStageOne::Render_Scene(void)
{
	Engine::CScene::Render_Scene();
}

void CStageOne::Free(void)
{
	Engine::CScene::Free();
	m_pTestObj->Free();
}

CStageOne* CStageOne::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStageOne*	pInstance = new CStageOne(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CStageOne::Ready_Layer_UI(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStageOne::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStageOne::Ready_Layer_GameLogic(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// Terrain
	m_pTestObj = pGameObject = CTerrainPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"TerrainPlayer", pGameObject), E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStageOne::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax)
{
	Engine::Reserve_ContainerSize(eMax);
	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TerrainTex",
		Engine::BUFFER_FOREST),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_LOGO,
		L"Texture_SkyTex",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/TestSkybox.dds"),
		E_FAIL);

	return S_OK;
}



