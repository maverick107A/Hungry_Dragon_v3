#include "stdafx.h"
#include "Scene_PlayerTest.h"
#include "Management.h"
#include "Export_Function.h"

CScene_PlayerTest::CScene_PlayerTest(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{

}

CScene_PlayerTest::~CScene_PlayerTest(void)
{

}

HRESULT CScene_PlayerTest::Ready_Scene(void)
{

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	_matrix		 matProj;

	//임시용 이거 나중에 따로 빼야함
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		100000.f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

_int CScene_PlayerTest::Update_Scene(const _float& fTimeDelta)
{
	if (GetAsyncKeyState('F') & 0x0001)
	{
		if (m_bWireFrame)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_bWireFrame = !m_bWireFrame;
	}
	Engine::CScene::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_PlayerTest::Render_Scene(void)
{
	Engine::CScene::Render_Scene();
}

void CScene_PlayerTest::Free(void)
{
	Engine::CScene::Free();
}

CScene_PlayerTest* CScene_PlayerTest::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_PlayerTest*	pInstance = new CScene_PlayerTest(pGraphicDev);

	(CManagement::GetInstance())->Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);


	return pInstance;
}

HRESULT CScene_PlayerTest::Ready_Layer_UI(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_PlayerTest::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_PlayerTest::Ready_Layer_GameLogic(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.emplace(pLayerTag, pLayer);

	Engine::CGameObject*		pGameObject = nullptr;

	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"BackGround", pGameObject), E_FAIL);

	pGameObject = CTestPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"Player", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_PlayerTest::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax)
{
	Engine::Reserve_ContainerSize(eMax);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_TERRAIN",
		Engine::BUFFER_FOREST),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_CUBEDRA",
		Engine::BUFFER_CUBEDRA),
		E_FAIL);
	return S_OK;
}




