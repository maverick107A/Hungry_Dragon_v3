#include "stdafx.h"
#include "Scene_Cave.h"

#include "Export_Function.h"
#include "SkySphere.h"
#include "Cave.h"
#include "Vent.h"
#include "Obstacle.h"
#include "CavePlayer.h"

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



	_matrix		 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(WINCX) / WINCY,
		1.f,
		1000.f);


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


	return S_OK;
}

_int CScene_Cave::Update_Scene(const _float& fTimeDelta)
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

}

void CScene_Cave::Free(void)
{
	Engine::CScene::Free();
}

CScene_Cave* CScene_Cave::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Cave*	pInstance = new CScene_Cave(pGraphicDev);

	Engine::Set_Scene(pInstance);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CScene_Cave::Ready_Layer_UI(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CScene_Cave::Ready_Layer_Environment(const _tchar * pLayerTag) {
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Register_GameObject<CSkySphere>(pLayer, L"Skybox"), E_FAIL);
	
	// Cylinder(Cave)
	FAILED_CHECK_RETURN(Register_GameObject<CCave>(&m_pCave, pLayer, L"Cave"), E_FAIL);
	FAILED_CHECK_RETURN(Register_GameObject<CVent>(&m_pVent, pLayer, L"Vent"), E_FAIL);
	
	

	//m_pVent->Set_Trans(_vec3(0.f,0.f, m_pCave->Get_EndPoint()+4000.f));
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



