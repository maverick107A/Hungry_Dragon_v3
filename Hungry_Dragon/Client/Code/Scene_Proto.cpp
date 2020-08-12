#include "stdafx.h"
#include "Scene_Proto.h"
#include "Export_Function.h"
#include "GameMgr.h"

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


	// �ӽ� ����
	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		10000.f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);



	//
	// Create effect.
	//
	HRESULT hr;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		m_pGraphicDev,
		L"../../Asset/Shader/fog_base.txt",
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_DEBUG, // compile flags
		0,                // don't share parameters
		&m_pFogEffect,
		&errorBuffer);

	// output any error messages
	if (errorBuffer)
	{
		TCHAR szTemp[512];
		MultiByteToWideChar(0, 0, (char*)errorBuffer->GetBufferPointer(), strlen((char*)errorBuffer->GetBufferPointer()), szTemp, strlen((char*)errorBuffer->GetBufferPointer()));
		::MessageBox(0, szTemp, 0, 0);
		//::MessageBox(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		Safe_Release(errorBuffer);
	}

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXCreateEffectFromFile() - FAILED", 0, 0);
		return E_FAIL;
	}

	// 
	// Save Frequently Accessed Parameter Handles
	//

	m_hFogTechHandle = m_pFogEffect->GetTechniqueByName("Fog");

	
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
	if (GetAsyncKeyState(VK_F8) & 0x0001)
	{
		m_bFogEnable = !m_bFogEnable;
	}

	//�÷��̾� ��ġ �ֽ�ȭ
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
	CGameMgr::GetInstance()->Game_Update(m_vPlayerPos);

	Engine::CScene::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_Proto::Render_Scene(void) {


	// set the technique to use
	m_pFogEffect->SetTechnique(m_hFogTechHandle);

	UINT numPasses = 0;
	m_pFogEffect->Begin(&numPasses, 0);

	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	
	if(m_bFogEnable)
		m_pFogEffect->BeginPass(0);


	m_mapLayer[L"Environment"]->Render_Layer();
	m_mapLayer[L"GameLogic"]->Render_Layer();

	m_pFogEffect->End();
}

void CScene_Proto::Free(void) {
	Engine::Clear_RenderGroup();
	Engine::CScene::Free();
	CGameMgr::DestroyInstance();
	Safe_Release(m_pFogEffect);
}

CScene_Proto* CScene_Proto::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Proto*	pInstance = new CScene_Proto(pGraphicDev);
	
	Engine::Set_Scene(pInstance);

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
	pLayer->Set_Address();

	// ���ø����� 1�� ó���� �˾Ƽ��� ������, ������Ʈ ������ ��������
	FAILED_CHECK_RETURN(Register_GameObject<CSkySphere>(pLayer, L"Skybox"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<COcean>(pLayer, L"BaseLayer"), E_FAIL);

	// �̷��� ���ӿ�����Ʈ �̾ƿ� ���� ����
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
	pLayer->Set_Address();

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CBackGround>(pLayer, L"BackGround"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CTestPlayer>(pLayer, L"TestPlayer"), E_FAIL);

	//for (int i = 0; i < 100; ++i)
	//{
	//	Engine::CGameObject*		pFly_MonsterObject = nullptr;
	//	D3DXVECTOR3 vMonsterPos = { (i * (rand() % 15)) + 1000.f ,  1000.f  , (i * (rand() % 10)) + 1000.f };
	//	pFly_MonsterObject = CFly_Monster::Create(m_pGraphicDev, vMonsterPos);
	//	NULL_CHECK_RETURN(pFly_MonsterObject, E_FAIL);
	//	pFly_MonsterObject->Set_Address(pLayer);
	//	Engine::Add_Object_Pool(pFly_MonsterObject, OBJID::STAND_MONSTER);

	//}

	for (int i = 0; i < 20; ++i)
	{
		Engine::CGameObject*		pChase_MonsterObject = nullptr;
		D3DXVECTOR3 vMonsterPos = { (i * (rand() % 10)) + 1000.f ,  1000.f  , (i * (rand() % 15)) + 1000.f };
		pChase_MonsterObject = CChase_Monster::Create(m_pGraphicDev, vMonsterPos);
		NULL_CHECK_RETURN(pChase_MonsterObject, E_FAIL);
		pChase_MonsterObject->Set_Address(pLayer);
		Engine::Add_Object_Pool(pChase_MonsterObject, OBJID::STAND_MONSTER);
	}


	//for (int i = 0; i < 100; ++i)
	//{
	//	Engine::CGameObject*		pRun_MonsterObject = nullptr;
	//	D3DXVECTOR3 vMonsterPos = { (i * (rand() % 15)) + 1000.f ,  1000.f  , (i * (rand() % 10)) + 1000.f };
	//	pRun_MonsterObject = CRun_Monster::Create(m_pGraphicDev, vMonsterPos);
	//	NULL_CHECK_RETURN(pRun_MonsterObject, E_FAIL);
	//	pRun_MonsterObject->Set_Address(pLayer);
	//	Engine::Add_Object_Pool(pRun_MonsterObject, OBJID::STAND_MONSTER);
	//}

	//for (int i = 0; i < 100; ++i)
	//{
	//	Engine::CGameObject*		pJump_MonsterObject = nullptr;
	//	D3DXVECTOR3 vMonsterPos = { (i * (rand() % 15)) + 1000.f ,  1000.f  , (i * (rand() % 10)) + 1000.f };
	//	pJump_MonsterObject = CJump_Monster::Create(m_pGraphicDev, vMonsterPos);
	//	NULL_CHECK_RETURN(pJump_MonsterObject, E_FAIL);
	//	pJump_MonsterObject->Set_Address(pLayer);
	//	Engine::Add_Object_Pool(pJump_MonsterObject, OBJID::STAND_MONSTER);
	//}

	// �̰� �˾Ƽ� �Ͻð� ������Ʈ Ǯ �̱����̶� �ͽ���Ʈ ����� �ɾ �;����ٵ�?
	for(int i = 0 ;  i < 10000; ++i)
	{	
		Engine::CGameObject*		pBulletObject = nullptr;
		pBulletObject = CNormal_Bullet::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pBulletObject, E_FAIL);
		pBulletObject->Set_Address(pLayer);
		Engine::Add_Object_Pool(pBulletObject, OBJID::NORMAL_BULLET);

	}

	CGameObject* tempPlayer = pLayer->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
	pPlayerTransformCom = static_cast<CTransform*>(tempPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));

	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);


	return S_OK;
}

HRESULT CScene_Proto::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	return S_OK;
}



