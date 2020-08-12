#include "stdafx.h"
#include "TerrainPlayer.h"

#include "Export_Function.h"
#include "ForestLand.h"

CTerrainPlayer::CTerrainPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	m_pSkyBox = 0;
	m_pSkyTex = 0;
}

CTerrainPlayer::~CTerrainPlayer(void)
{

}

HRESULT CTerrainPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXCreateSphere(m_pGraphicDev, 1, 10, 10, &m_pSkyBox, 0);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	return S_OK;
}

_int CTerrainPlayer::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CTerrainPlayer::Render_Object(void)
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1000.f, 1000.f, 1000.f);
	matScale *= matTrans;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matScale);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);   //Z¹öÆÛ ²ô±â
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);   //Á¶¸í ²ô±â

	//m_pSkyTex->Set_Texture();
	m_pSkyBox->DrawSubset(0);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);  
	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
}

void CTerrainPlayer::Free(void)
{

	Engine::CGameObject::Free();
	Safe_Release(m_pSkyBox);
	Safe_Release(m_pSkyTex);
}


HRESULT CTerrainPlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CForestLand*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TerrainTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	// SkyTex
	//pComponent = m_pSkyTex = dynamic_cast<Engine::CTexture*>
	//	(Engine::Clone(RESOURCE_LOGO, L"Texture_SkyTex"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);



	

	return S_OK;
}

CTerrainPlayer* CTerrainPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainPlayer*		pInstance = new CTerrainPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

