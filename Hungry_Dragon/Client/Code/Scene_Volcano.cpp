#include "stdafx.h"
#include "Scene_Volcano.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"

CScene_Volcano::CScene_Volcano(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev) {

}

CScene_Volcano::~CScene_Volcano(void) {

}

HRESULT CScene_Volcano::Ready_Scene(void) {

	Engine::Ready_ParticleMgr(m_pGraphicDev);

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_IgnoreEffect(L"IgnoreEffect"), E_FAIL);
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



	//
	// Create effect.
	//
	HRESULT hr;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		m_pGraphicDev,
		L"../../Asset/Shader/fog_fardark.txt",
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

_int CScene_Volcano::Update_Scene(const _float& fTimeDelta) {
	if (GetAsyncKeyState('F') & 0x0001)
	{
		if(m_bWireFrameMode)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_bWireFrameMode = !m_bWireFrameMode;
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_bWireFrameMode = true;
	}
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_bWireFrameMode = false;
	}
	if (GetAsyncKeyState(VK_F7) & 0x0001)
	{
		CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_CAVE);
	}
	if (GetAsyncKeyState(VK_F8) & 0x0001)
	{
		m_bFogEnable = !m_bFogEnable;
	}
	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		m_iMaskNum = (m_iMaskNum + 1) % 8;
	}

	Engine::Particle_Update(fTimeDelta);

	//플레이어 위치 최신화
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
	Engine::Set_Monster_LayerMap(OBJID::STAND_MONSTER, 9999, m_vPlayerPos);
	
	
	Engine::CScene::Update_Scene(fTimeDelta);

	
	return 0;
}

void CScene_Volcano::LateUpdate_Scene(const _float & fTimeDelta)
{
	Engine::Particle_LateUpdate(fTimeDelta);
	CScene::LateUpdate_Scene(fTimeDelta);

}

void CScene_Volcano::Render_Scene(void) {
	// set the technique to use
	m_pFogEffect->SetTechnique(m_hFogTechHandle);

	

	

	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	
	

	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	//Engine::Particle_Render();
	
	//CIngame_Flow::GetInstance()->Set_MaskColor(m_iMaskNum); 
	CIngame_Flow::GetInstance()->Set_DefaultTex();


	

	UINT numPasses = 0;
	m_pFogEffect->Begin(&numPasses, 0);
	if (m_bFogEnable)
		m_pFogEffect->BeginPass(0);

	if (!m_bWireFrameMode)
	{
		m_mapLayer[L"Environment"]->Render_Layer();
	}

	m_mapLayer[L"GameLogic"]->Render_Layer();
	
	m_pFogEffect->End();

	m_mapLayer[L"IgnoreEffect"]->Render_Layer();

	m_mapLayer[L"UI"]->Render_Layer();

	Engine::Particle_Render();
}

void CScene_Volcano::Free(void) {
	Engine::Clear_RenderGroup();
	Engine::CScene::Free();
	Engine::Clear_ObjectPool();
	Safe_Release(m_pFogEffect);
}

CScene_Volcano* CScene_Volcano::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CScene_Volcano*	pInstance = new CScene_Volcano(pGraphicDev);
	
	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);


	Engine::Initialize();

	return pInstance;
}

HRESULT CScene_Volcano::Ready_Layer_UI(const _tchar* pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	

	m_mapLayer.emplace(pLayerTag, pLayer);

	FAILED_CHECK_RETURN(Register_GameObject<CPlayerUI>(pLayer, L"PlayerUI"), E_FAIL);

	return S_OK;
}

HRESULT CScene_Volcano::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();

	// 템플릿으로 1줄 처리함 알아서들 쓰세염, 컴포넌트 버전도 만들어놓음
	FAILED_CHECK_RETURN(Register_GameObject<CRedSky>(pLayer, L"Skybox"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CLava>(pLayer, L"BaseLayer"), E_FAIL);

	

	return S_OK;
}

HRESULT CScene_Volcano::Ready_Layer_IgnoreEffect(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();


	FAILED_CHECK_RETURN(Register_GameObject<CAshCloud_Locater>(pLayer, L"AshCloud"), E_FAIL);

	return S_OK;
}

HRESULT CScene_Volcano::Ready_Layer_GameLogic(const _tchar * pLayerTag) {

	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();

	Engine::CGameObject*		pGameObject = nullptr;
	
	
	FAILED_CHECK_RETURN(Register_GameObject<CTestPlayer>(pLayer, L"TestPlayer"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CVolcano_Parts>(pLayer, L"Land"), E_FAIL);

	//
	
	CGameObject* tempPlayer = pLayer->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
	pPlayerTransformCom = static_cast<CTransform*>(tempPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);


	return S_OK;
}

HRESULT CScene_Volcano::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax) {
	Engine::Reserve_ContainerSize(eMax);

	return S_OK;
}



