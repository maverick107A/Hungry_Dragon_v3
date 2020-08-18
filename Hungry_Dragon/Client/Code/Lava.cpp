#include "stdafx.h"
#include "Lava.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "LandTex.h"
#include "Texture.h"


USING(Engine)

CLava::CLava(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CLava::~CLava(void)
{

}

HRESULT CLava::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int CLava::Update_Object(const float& fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	m_pTransform->Add_Trans(&_vec3(1.f, 0.f, -1.f));				// 셰이더로 바꾸기 전 임시
	m_fLoopCnt += 1.f;
	if (1000.f <= m_fLoopCnt)
	{
		m_fLoopCnt -= 1000.f;
		m_pTransform->Add_Trans(&_vec3(-1000.f, 0.f, 1000.f));
	}

	return 0;
}

void CLava::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTexture->Set_Texture();

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);		// 렌더 순서에 의존하겠다

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void CLava::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CLava::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK(Clone_Component<CTexture_Plane>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_LandTex", ID_STATIC, L"Com_Buffer"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_LAVA", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));

	m_pTransform->m_vInfo[INFO_POS] = _vec3(-64000.f, 0.f,-64000.f);
	
	return S_OK;
}

CLava* CLava::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLava*		pInstance = new CLava(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

