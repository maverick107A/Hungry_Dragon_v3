﻿#include "stdafx.h"
#include "Scene_Cave.h"
#include "Export_Function.h"
#include "SkySphere.h"
#include "Cave.h"
#include "Vent.h"
#include "Obstacle.h"
#include "CavePlayer.h"
#include "PlayerUI.h"
#include "Ingame_Flow.h"
#include "Ingame_Info.h"

CScene_Cave::CScene_Cave(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{

}

CScene_Cave::~CScene_Cave(void)
{
	
}

HRESULT CScene_Cave::Ready_Scene(void)
{

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	CIngame_Flow::GetInstance()->Init_PlayerObjectByScene();

	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		10000.f);


	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);


	D3DXMATRIX V;
	D3DXVECTOR3 m_vPos(0,1,-1);
	D3DXVECTOR3 m_vDir(0,-1,4);
	//D3DXVECTOR3 m_vPos(1, 0, 10);
	//D3DXVECTOR3 m_vDir(-1, -1, 10);
	D3DXVECTOR3 m_vUp1(0,1,0);
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp1);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);


	//
	// Create effect.
	//
	HRESULT hr;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		m_pGraphicDev,
		L"../../Asset/Shader/fog_dark.txt",
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

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);


	Engine::Get_FMOD()->PlayBgm(L"CaveBgm");
	CIngame_Flow::GetInstance()->Set_StageID(CIngame_Flow::STAGE_CAVE_ONE);
	return S_OK;
}

_int CScene_Cave::Update_Scene(const _float& fTimeDelta)
{
	Engine::CScene::Update_Scene(fTimeDelta);

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
		CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_CLOUD);
	}
	if (GetAsyncKeyState(VK_F8) & 0x0001)
	{
		m_ePhaseNum = (SCENEPHASE)(((int)m_ePhaseNum + 1) % 3);
		switch (m_ePhaseNum)		// Ready 부분
		{
		case CScene_Cave::PHASE_1:
			m_pVent->Set_Active(false);
			m_pVent->Set_ObsLoop(false);
			static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(0);
			m_pCave->Set_Speed(400.f);
			m_pVent->Set_Speed(400.f);
			break;
		case CScene_Cave::PHASE_2:
			m_pVent->Set_Trans(_vec3(0.f, 0.f, 4000.f));
			m_pVent->Set_Active(true);
			m_pVent->Set_ObsLoop(false);
			static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(1);
			m_pCave->Set_Speed(100.f);
			m_pVent->Set_Speed(100.f);
			break;
		case CScene_Cave::PHASE_3:
			m_pVent->Set_Trans(_vec3(0.f, 0.f, 0.f));
			m_pVent->Set_Active(true);
			m_pVent->Set_ObsLoop(true);
			static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(2);
			m_pCave->Set_Speed(400.f);
			m_pVent->Set_Speed(400.f);
			break;
		default:
			break;
		}
	}
	//플레이어 위치 최신화
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
	switch (m_ePhaseNum)
	{
	case CScene_Cave::PHASE_1:			// 카메라 Z회전 안함
		Engine::Set_Monster_CaveMap(OBJID::STAND_MONSTER, 9999, m_vPlayerPos);
		break;
	case CScene_Cave::PHASE_2:			// 카메라 횡스크롤
		CIngame_Flow::GetInstance()->Set_StageID(CIngame_Flow::STAGE_CAVE_TWO);
		Engine::Set_Monster_HorizonCaveRedMap(OBJID::HORIZON_REDMONSTER, 9999, m_vPlayerPos);	// 횡스크롤로 변경
		Engine::Set_Monster_HorizonCaveMap(OBJID::HORIZON_MONSTER, 9999, m_vPlayerPos);	// 횡스크롤로 변경

		break;
	case CScene_Cave::PHASE_3:			// 카메라 Z회전 함
										// 여기 몬스터 안나오게 해줘
	CIngame_Flow::GetInstance()->Set_StageID(CIngame_Flow::STAGE_CAVE_FINAL);
		break;
	default:
		break;
	}

	CIngame_Info::GetInstance()->Update_Info(fTimeDelta);
	
	return 0;
}

void CScene_Cave::LateUpdate_Scene(const _float & fTimeDelta)
{
	Engine::Particle_LateUpdate(fTimeDelta);
	CScene::LateUpdate_Scene(fTimeDelta);

	
}

void CScene_Cave::Render_Scene(void)
{
	// set the technique to use
	m_pFogEffect->SetTechnique(m_hFogTechHandle);

	UINT numPasses = 0;
	m_pFogEffect->Begin(&numPasses, 0);

	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);

	if (m_bFogEnable)
		m_pFogEffect->BeginPass(0);


	m_mapLayer[L"Environment"]->Render_Layer();
	m_mapLayer[L"GameLogic"]->Render_Layer();

	m_pFogEffect->End();

	m_mapLayer[L"UI"]->Render_Layer();

	CIngame_Info::GetInstance()->Render_UI();

}

void CScene_Cave::Free(void)
{
	Engine::CScene::Free();
	Engine::Clear_ObjectPool();
	Safe_Release(m_pFogEffect);
}

CScene_Cave* CScene_Cave::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Cave*	pInstance = new CScene_Cave(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	Engine::Initialize();

	return pInstance;
}

HRESULT CScene_Cave::Ready_Layer_UI(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CPlayerUI>(pLayer, L"PlayerUI"), E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

void CScene_Cave::Switch_Phase(int _iNum)
{
	switch (_iNum)
	{
	case 0:
		static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(0);
		m_pCave->Set_Speed(400.f);
		m_pVent->Set_Speed(400.f);
		break;
	case 1:
		static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(1);
		m_pCave->Set_Speed(100.f);
		m_pVent->Set_Speed(100.f);
		break;
	case 2:
		static_cast<CCavePlayer*>(Get_Object(L"GameLogic", L"TestPlayer"))->Switch_Phase(2);
		m_pCave->Set_Speed(400.f);
		m_pVent->Set_Speed(400.f);
		break;
	}
}

HRESULT CScene_Cave::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CSkySphere>(pLayer, L"Skybox"), E_FAIL);
	
	// Cylinder(Cave)
	FAILED_CHECK_RETURN(Register_GameObject<CCave>(&m_pCave, pLayer, L"Cave"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CVent>(&m_pVent, pLayer, L"Vent"), E_FAIL);
	
	for (int i = 0; i < 1000; ++i)
	{
		FAILED_CHECK_RETURN(Register_ObjectPool<CBat_Monster>(pLayer, OBJID::STAND_MONSTER), E_FAIL);	
	}

	for (int i = 0; i < 500; ++i)
	{
		pGameObject = CHorizonBat_Monster::Create(m_pGraphicDev, true );
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Set_Address(pLayer);
		Engine::Add_Object_Pool(pGameObject, OBJID::HORIZON_REDMONSTER);

		pGameObject = CHorizonBat_Monster::Create(m_pGraphicDev, false);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Set_Address(pLayer);
		Engine::Add_Object_Pool(pGameObject, OBJID::HORIZON_MONSTER);
	}

	//m_pVent->Set_Trans(_vec3(0.f,0.f, m_pCave->Get_EndPoint()+4000.f));
	m_pVent->Set_Active(false);
	m_mapLayer.emplace(pLayerTag, pLayer);

	//m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	
	return S_OK;
}

HRESULT CScene_Cave::Ready_Layer_GameLogic(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::Set_Object_LayerMap(pLayer);
	m_mapLayer.emplace(pLayerTag, pLayer);
	pLayer->Set_Address();

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CCavePlayer>(pLayer, L"TestPlayer"), E_FAIL);

	CGameObject* tempPlayer = pLayer->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
	pPlayerTransformCom = static_cast<CTransform*>(tempPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
	return S_OK;
}

HRESULT CScene_Cave::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax)
{
	Engine::Reserve_ContainerSize(eMax);
	/*FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TerrainTex",
		Engine::BUFFER_FOREST),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(pGraphicDev,
		RESOURCE_LOGO,
		L"Texture_SkyTex",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/TestSkybox.dds"),
		E_FAIL);*/

	return S_OK;
}



