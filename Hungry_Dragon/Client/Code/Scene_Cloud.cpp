#include "stdafx.h"
#include "Scene_Cloud.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Ingame_Info.h"
#include "Line_Renderer.h"


CScene_Cloud::CScene_Cloud(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Cloud::~CScene_Cloud(void) {

}

HRESULT CScene_Cloud::Ready_Scene(void) {
	srand((unsigned int)time(NULL));

	Engine::Ready_ParticleMgr(m_pGraphicDev);

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_IgnoreEffect(L"IgnoreEffect"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	CIngame_Flow::GetInstance()->Init_PlayerObjectByScene();

	// 임시 적용
	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		100000.f);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);



	//
	// Create effect.
	//
	HRESULT hr;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		m_pGraphicDev,
		L"../../Asset/Shader/fog_height.fx",
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

	m_hFogTechHandle = m_pFogEffect->GetTechniqueByName("TShader");
	m_hvFog = m_pFogEffect->GetParameterByName(NULL, "vFog");
	
	//
	// Create effect.
	//
	hr = D3DXCreateEffectFromFile(
		m_pGraphicDev,
		L"../../Asset/Shader/fog_red.txt",
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_DEBUG, // compile flags
		0,                // don't share parameters
		&m_pDarkEffect,
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

	m_hDarkTechHandle = m_pDarkEffect->GetTechniqueByName("Fog");





	Engine::Get_FMOD()->PlayBgm(L"Devil's Pit");




	CIngame_Flow::GetInstance()->Set_StageID(CIngame_Flow::STAGE_SKY);
	return S_OK;
}

_int CScene_Cloud::Update_Scene(const _float& fTimeDelta) {
	if (GetAsyncKeyState('F') & 0x0001)
	{
		if(m_bWireFrame)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_bWireFrame = !m_bWireFrame;
	}
	if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		m_bFogEnable = !m_bFogEnable;
	}
	if (GetAsyncKeyState(VK_F4) & 0x0001)
	{
		CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_MENU);
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if (GetAsyncKeyState(VK_F7) & 0x0001)
	{
		CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_VOLCANO);
	}
	if (GetAsyncKeyState(VK_F8) & 0x0001)
	{
		m_bFogEnable = !m_bFogEnable;
	}

	if (GetAsyncKeyState('H') & 0x8000)
	{
		m_near += 0.001f;
	}
	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_near -= 0.001f;
	}
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_far += 0.001f;
	}
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_far -= 0.001f;
	}

	Engine::Particle_Update(fTimeDelta);

	//플레이어 위치 최신화
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
	// 클라우드 맵 생성 업데이트
	Engine::Set_Monster_CloudMap(OBJID::STAND_MONSTER, 9999, m_vPlayerPos);
	
	
	Engine::CScene::Update_Scene(fTimeDelta);


	CIngame_Info::GetInstance()->Update_Info(fTimeDelta);
	
	CLine_Renderer::GetInstance()->Update_Renderer(fTimeDelta);

	_vec3 vPos;
	CIngame_Flow::GetInstance()->Get_PlayerTransform()->Get_Info(INFO_POS, &vPos);
	//CIngame_Info::GetInstance()->Get_PlayerInfo()->fStage = vPos.z*0.0001f;
	CIngame_Info::GetInstance()->Get_PlayerInfo()->fStage = vPos.z/(m_iRingCnt*2500.f)*1000;
	if (CIngame_Info::GetInstance()->Get_PlayerInfo()->fStage < 0.f)
	{
		CIngame_Info::GetInstance()->Get_PlayerInfo()->fStage = 0.f;
	}
	return 0;
}

void CScene_Cloud::LateUpdate_Scene(const _float & fTimeDelta)
{
	Engine::Particle_LateUpdate(fTimeDelta);
	CScene::LateUpdate_Scene(fTimeDelta);

}

void CScene_Cloud::Render_Scene(void) {


	
	// 행렬 및 파티클/스카이박스 렌더
	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);


	m_mapLayer[L"Environment"]->Render_Layer();

	// 안개셰이더
	if (m_bFogEnable)
	{	// set the technique to use
		m_pFogEffect->SetTechnique(m_hFogTechHandle);

		UINT numPasses = 0;
		m_pFogEffect->Begin(&numPasses, 0);


		D3DXMATRIX I;
		D3DXMatrixIdentity(&I);

		m_pFogEffect->BeginPass(0);

		D3DXVECTOR4 vFog;
		vFog.x = m_far / (m_far - m_near);
		vFog.y = -1.0f / (m_far - m_near);
		//if (m_hvFog != NULL) m_pFogEffect->SetVector(m_hvFog, &vFog);

		// 게임에 적용
		m_mapLayer[L"GameLogic"]->Render_Layer();

		m_pFogEffect->End();
	}

	else
	{
		// set the technique to use
		m_pDarkEffect->SetTechnique(m_hDarkTechHandle);

		UINT numPasses = 0;
		m_pDarkEffect->Begin(&numPasses, 0);


		m_pDarkEffect->BeginPass(0);

		m_mapLayer[L"GameLogic"]->Render_Layer();

		m_pDarkEffect->End();
	}



	m_mapLayer[L"IgnoreEffect"]->Render_Layer();

	_matrix matPers;
	_matrix matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matPers);
	D3DXMatrixOrthoOffCenterRH(&matOrtho, 0, 0, 1600, 900, 0, 1000);

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matOrtho);
	m_mapLayer[L"UI"]->Render_Layer();
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matPers);

	Engine::Particle_Render();

	CLine_Renderer::GetInstance()->Render_Renderer();

	CIngame_Info::GetInstance()->Render_UI();
}

void CScene_Cloud::Free(void) {
	Engine::Clear_RenderGroup();
	Engine::CScene::Free();
	Engine::Clear_ObjectPool();
	Safe_Release(m_pFogEffect);
	Safe_Release(m_pDarkEffect);
}

void CScene_Cloud::Set_AccelRingPos(Engine::CLayer* pLayer)
{
	CAccel_Torus* tempAccel;
	_vec3 vOrigin = _vec3(0.f, 0.f, 1000.f);
	for (int i = 0; i < m_iRingCnt; ++i)
	{
		tempAccel =CAccel_Torus::Create(m_pGraphicDev);
		tempAccel->Set_Trans(vOrigin);
		pLayer->Add_Object(L"Accel_Torus",tempAccel);
		vOrigin.x += (5 - rand() % 11) * 75;
		vOrigin.y += (5 - rand() % 10) * 50;
		vOrigin.z += 2500;

		if (vOrigin.x < -1400)
		{
			vOrigin.x = -1325;
		}
		else if (vOrigin.x > 1400)
		{
			vOrigin.x = 1325;
		}

		if (vOrigin.y < -800)
		{
			vOrigin.y = -700;
		}
		else if (vOrigin.y > 800)
		{	
			vOrigin.y = 700;
		}
	}
}

CScene_Cloud* CScene_Cloud::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Cloud*	pInstance = new CScene_Cloud(pGraphicDev);
	
	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);


	Engine::Initialize();

	return pInstance;
}

HRESULT CScene_Cloud::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	

	m_mapLayer.emplace(pLayerTag, pLayer);

	FAILED_CHECK_RETURN(Register_GameObject<CPlayerUI>(pLayer, L"PlayerUI"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CView_Mask>(&m_pMaskSprite, pLayer, L"Sprite"), E_FAIL);


	return S_OK;
}

HRESULT CScene_Cloud::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();

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

HRESULT CScene_Cloud::Ready_Layer_IgnoreEffect(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();


	FAILED_CHECK_RETURN(Register_GameObject<CBillCloud_Locater>(pLayer, L"Spawner"), E_FAIL);

	return S_OK;
}

HRESULT CScene_Cloud::Ready_Layer_GameLogic(const _tchar * pLayerTag) {

	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();

	Engine::CGameObject*		pGameObject = nullptr;

	// 지형없이 안터지는 플레이어 설정해주세요

	CTestPlayer* tempPlayer = nullptr;
	FAILED_CHECK_RETURN(Register_GameObject<CCloud_Locater>(pLayer, L"Cloud"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CCliff_Locater>(pLayer, L"Cliff"), E_FAIL);

	FAILED_CHECK(Register_GameObject<CBillCloud_Locater>(&m_pBillCloudLocater,pLayer,L"BillCloudLocater"));

	FAILED_CHECK_RETURN(Register_GameObject<CTestPlayer>(&tempPlayer, pLayer, L"TestPlayer"), E_FAIL);
	pPlayerTransformCom = static_cast<CTransform*>(tempPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);


	for (int i = 0; i < 250; ++i)
	{
		FAILED_CHECK_RETURN(Register_ObjectPool<CFlyGolem>(pLayer, OBJID::STAND_MONSTER), E_FAIL);

		FAILED_CHECK_RETURN(Register_ObjectPool<CFlyChaseGolem>(pLayer, OBJID::STAND_MONSTER), E_FAIL);


	//	FAILED_CHECK_RETURN(Register_ObjectPool<CFly_Monster>(pLayer, OBJID::STAND_MONSTER), E_FAIL);
	}



	for (int i = 0; i < 10000; ++i)
	{
		FAILED_CHECK_RETURN(Register_ObjectPool<CNormal_Bullet>(pLayer, OBJID::NORMAL_BULLET), E_FAIL);
		//	FAILED_CHECK_RETURN(Register_ObjectPool<CMonsterBeam>(pLayer, OBJID::NORMAL_BULLET), E_FAIL);
	}
	for (int i = 0; i < 50; ++i)
	{
		FAILED_CHECK_RETURN(Register_ObjectPool<CRedCrystal_Monster>(pLayer, OBJID::STAND_MONSTER), E_FAIL);
	}

	Set_AccelRingPos(pLayer);

	return S_OK;
}

HRESULT CScene_Cloud::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	return S_OK;
}



