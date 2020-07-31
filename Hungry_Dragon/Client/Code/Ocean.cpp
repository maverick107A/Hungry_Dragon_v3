#include "stdafx.h"
#include "Ocean.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "LandTex.h"
#include "Texture.h"


USING(Engine)

COcean::COcean(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

COcean::~COcean(void)
{

}

HRESULT COcean::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int COcean::Update_Object(const float& fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	m_pTransform->Add_Trans(&_vec3(1.f, 0.f, -1.f));
	m_fLoopCnt += 1.f;
	if (1000.f <= m_fLoopCnt)
	{
		m_fLoopCnt -= 1000.f;
		m_pTransform->Add_Trans(&_vec3(-1000.f, 0.f, 1000.f));
	}

	return 0;
}

void COcean::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTexture->Set_Texture();

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void COcean::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT COcean::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK_RETURN(Clone_Component<CLandTex>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_LandTex", ID_STATIC, L"Com_Buffer"), E_FAIL);
	FAILED_CHECK_RETURN(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_OCEAN", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"), E_FAIL);

	m_pTransform->m_vInfo[INFO_POS] = _vec3(-64000.f, 0.f,-64000.f);
	
	return S_OK;
}

COcean* COcean::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COcean*		pInstance = new COcean(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

