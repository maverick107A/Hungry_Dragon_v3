#include "stdafx.h"
#include "Scene_Proto.h"

#include "Export_Function.h"

CScene_Proto::CScene_Proto(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Proto::~CScene_Proto(void) {

}

HRESULT CScene_Proto::Ready_Scene(void) {

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);


	// 임시 적용
	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		100000.f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

_int CScene_Proto::Update_Scene(const _float& fTimeDelta) {
	if (GetAsyncKeyState('F') & 0x0001)
	{
		if(m_bWireFrame)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_bWireFrame = !m_bWireFrame;
	}
	pPlayerTransformCom = dynamic_cast<Engine::CTransform*>
		(Engine::Get_Component(L"GameLogic",
			L"TestPlayer",
			L"Com_Transform",
			Engine::ID_DYNAMIC));

	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);


	Engine::CScene::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_Proto::Render_Scene(void) {
	Engine::CScene::Render_Scene();
}

void CScene_Proto::Free(void) {
	Engine::CScene::Free();
}

CScene_Proto* CScene_Proto::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Proto*	pInstance = new CScene_Proto(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Proto::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Proto::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Proto::Ready_Layer_GameLogic(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();

	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);


	Engine::CGameObject*		pGameObject = nullptr;

	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"BackGround", pGameObject), E_FAIL);

	pGameObject = CChase_Monster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"ChaseMonster", pGameObject), E_FAIL);


	pGameObject = CRun_Monster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"RunMonster", pGameObject), E_FAIL);

	pGameObject = CJump_Monster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"JumpMonster", pGameObject), E_FAIL);

	pGameObject = CTestPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"TestPlayer", pGameObject), E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);



	pGameObject = CFly_Monster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"FlyMonster", pGameObject), E_FAIL);

	

	for(int i = 0 ;  i < 100; ++i)
	{	
		Engine::CGameObject*		pBulletObject = nullptr;
		pBulletObject = CNormal_Bullet::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pBulletObject, E_FAIL);
		CObjectPool::GetInstance()->Add_Object_Pool(pBulletObject, OBJID::NORMAL_BULLET);

	}

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Proto::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_CubeTex",
		Engine::BUFFER_CUBETEX),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TerrainTex",
		Engine::BUFFER_TERRAINTEX,
		129,
		129,
		1),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Terrain",
		Engine::TEX_NORMAL,
		L"../Bin/Resource/Texture/Terrain/Terrain0.png"),
		E_FAIL);



	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BoxHead",
		Engine::TEX_NORMAL,
		L"../Bin/Resource/Texture/BoxHead.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_PlayerBox",
		Engine::TEX_NORMAL,
		L"../Bin/Resource/Texture/PlayerBox.png"),
		E_FAIL);

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



