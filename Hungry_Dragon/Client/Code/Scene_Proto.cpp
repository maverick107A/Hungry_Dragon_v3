#include "stdafx.h"
#include "Scene_Proto.h"
#include <time.h>
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
	Engine::Render_GameObject();
}

void CScene_Proto::Free(void) {
	Engine::Clear_RenderGroup();
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
	m_mapLayer.emplace(pLayerTag, pLayer);

	// 템플릿으로 1줄 처리함 알아서들 쓰세염, 컴포넌트 버전도 만들어놓음
	FAILED_CHECK_RETURN(Register_GameObject<CSkySphere>(pLayer, L"Skybox"), E_FAIL);


	// 이렇게 게임오브젝트 뽑아올 수도 있음
	//CSkySphere*		pGameObject = nullptr;
	//FAILED_CHECK_RETURN(Register_GameObject<CSkySphere>(&pGameObject, pLayer, L"Skybox"), E_FAIL);

	//pGameObject = CSkySphere::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"Skybox", pGameObject), E_FAIL);

	

	return S_OK;
}

HRESULT CScene_Proto::Ready_Layer_GameLogic(const _tchar * pLayerTag) {

	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);
	m_mapLayer.emplace(pLayerTag, pLayer);

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CBackGround>(pLayer, L"BackGround"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CTestPlayer>(pLayer, L"TestPlayer"), E_FAIL);
	srand(unsigned(time(NULL)));

	for (int i = 0; i < 100; ++i)
	{
		Engine::CGameObject*		pJumpMonsterObject = nullptr;
		D3DXVECTOR3 vMonsterPos = { (i * (rand() % 10)) + 1000.f ,  600.f  , (i * (rand() % 10)) + 1000.f };
		pJumpMonsterObject = CFly_Monster::Create(m_pGraphicDev, vMonsterPos);
		NULL_CHECK_RETURN(pJumpMonsterObject, E_FAIL);
		pLayer->Add_Monster_Object(pJumpMonsterObject, vMonsterPos);
	}

	for (int i = 0; i < 100; ++i)
	{
		Engine::CGameObject*		pJumpMonsterObject = nullptr;
		D3DXVECTOR3 vMonsterPos = { (i * (rand() % 10)) + 1000.f ,  1000.f  , (i * (rand() % 10)) + 1000.f };
		pJumpMonsterObject = CJump_Monster::Create(m_pGraphicDev , vMonsterPos);
		NULL_CHECK_RETURN(pJumpMonsterObject, E_FAIL);
		pLayer->Add_Monster_Object(pJumpMonsterObject , vMonsterPos);
	}

	for (int i = 0; i < 100; ++i)
	{
		Engine::CGameObject*		pJumpMonsterObject = nullptr;
		D3DXVECTOR3 vMonsterPos = { (i * (rand() % 15)) + 1000.f ,  1000.f  , (i * (rand() % 10)) + 1000.f };
		pJumpMonsterObject = CRun_Monster::Create(m_pGraphicDev, vMonsterPos);
		NULL_CHECK_RETURN(pJumpMonsterObject, E_FAIL);
		pLayer->Add_Monster_Object(pJumpMonsterObject, vMonsterPos);

	}


	for (int i = 0; i < 100; ++i)
	{
		Engine::CGameObject*		pJumpMonsterObject = nullptr;
		D3DXVECTOR3 vMonsterPos = { (i * (rand() % 10)) + 1000.f ,  1000.f  , (i * (rand() % 15)) + 1000.f };
		pJumpMonsterObject = CChase_Monster::Create(m_pGraphicDev, vMonsterPos);
		NULL_CHECK_RETURN(pJumpMonsterObject, E_FAIL);
		pLayer->Add_Monster_Object(pJumpMonsterObject, vMonsterPos);
	}


	




	// 이건 알아서 하시고 오브젝트 풀 싱글턴이라 익스포트 헤더에 걸어서 와야할텐데?
	for(int i = 0 ;  i < 10000; ++i)
	{	
		Engine::CGameObject*		pBulletObject = nullptr;
		pBulletObject = CNormal_Bullet::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pBulletObject, E_FAIL);
		Engine::Add_Object_Pool(pBulletObject, OBJID::NORMAL_BULLET);

	}


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
		L"Texture_SkySphere",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/TestSkybox.dds"),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BoxHead",
		Engine::TEX_NORMAL,
		L"../../Asset/HeadPng/Head%d.png",6),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_TERRAIN",
		Engine::BUFFER_FOREST),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_SKYSPHERE",
		Engine::BUFFER_SKYSPHERE),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_CUBEDRA",
		Engine::BUFFER_CUBEDRA),
		E_FAIL);


	return S_OK;
}



