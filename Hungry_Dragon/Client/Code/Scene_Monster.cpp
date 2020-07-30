#include "stdafx.h"
#include "Scene_Monster.h"

#include "Export_Function.h"

CScene_Monster::CScene_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Monster::~CScene_Monster(void) {

}

HRESULT CScene_Monster::Ready_Scene(void) {

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);


	// 임시 적용
	_matrix		matView, matProj;

	D3DXMatrixLookAtLH(&matView,
		&_vec3(64.f, 220.f, 0.f),
		&_vec3(64.f, 0.f, 64.f),
		&_vec3(0.f, 1.f, 0.f));

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(30.f),
		_float(WINCX) / WINCY,
		1.f,
		1000.f);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);




	return S_OK;
}

_int CScene_Monster::Update_Scene(const _float& fTimeDelta) {

	pPlayerTransformCom = dynamic_cast<Engine::CTransform*>
		(Engine::Get_Component(L"GameLogic",
			L"TestPlayer",
			L"Com_Transform",
			Engine::ID_DYNAMIC));

	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);


	Engine::CScene::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_Monster::Render_Scene(void) {
	Engine::CScene::Render_Scene();
}

void CScene_Monster::Free(void) {
	Engine::CScene::Free();
}

CScene_Monster* CScene_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Monster*	pInstance = new CScene_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Monster::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Monster::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Monster::Ready_Layer_GameLogic(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();

	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);


	//Engine::CGameObject*		pGameObject = nullptr;

	////pGameObject = CTerrain::Create(m_pGraphicDev);
	////NULL_CHECK_RETURN(pGameObject, E_FAIL);
	////FAILED_CHECK_RETURN(pLayer->Add_Object(L"Buffer_Terrain", pGameObject), E_FAIL);

	//pGameObject = CChase_Monster::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"ChaseMonster", pGameObject), E_FAIL);


	//pGameObject = CRun_Monster::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"RunMonster", pGameObject), E_FAIL);

	////pGameObject = CJump_Monster::Create(m_pGraphicDev);
	////NULL_CHECK_RETURN(pGameObject, E_FAIL);
	////FAILED_CHECK_RETURN(pLayer->Add_Object(L"JumpMonster", pGameObject), E_FAIL);

	//pGameObject = CPlayer::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"TestPlayer", pGameObject), E_FAIL);



	//pGameObject = CFly_Monster::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"FlyMonster", pGameObject), E_FAIL);

	

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

HRESULT CScene_Monster::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
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




	return S_OK;
}



