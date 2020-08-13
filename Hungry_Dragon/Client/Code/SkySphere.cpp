 #include "stdafx.h"
#include "SkySphere.h"

#include "Export_Function.h"

USING(Engine)

CSkySphere::CSkySphere(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CSkySphere::~CSkySphere(void)
{

}

HRESULT CSkySphere::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CSkySphere::Update_Object(const _float& fTimeDelta)
{
	//_matrix		matCamWorld;
	//m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	//D3DXMatrixInverse(&matCamWorld, NULL, &matCamWorld);

	//m_pTransform->m_vInfo[INFO_POS] = { matCamWorld._41, matCamWorld._42, matCamWorld._43 };
	//
	//Engine::CGameObject::Update_Object(fTimeDelta);

	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CSkySphere::Render_Object(void)
{
	//여기부터
	_matrix		matCamWorld;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	D3DXMatrixInverse(&matCamWorld, NULL, &matCamWorld);

	m_pTransform->m_vInfo[INFO_POS] = { matCamWorld._41, matCamWorld._42, matCamWorld._43 };

	Engine::CGameObject::Update_Object(float(0));
	//여기까지 레이트업데이트에 넣어줘야함
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CSkySphere::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CSkySphere::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK_RETURN(Clone_Component<CSkyCube>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_SKYSPHERE", ID_STATIC, L"Com_Buffer"), E_FAIL);
	
	// Texture
	FAILED_CHECK_RETURN(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_SkySphere", ID_STATIC, L"Com_Texture"), E_FAIL);
	
	//Transform
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"), E_FAIL);

	// 원본
	/*pComponent = m_pBufferCom = dynamic_cast<Engine::CSkyCube*>
	(Engine::Clone(RESOURCE_STATIC, L"BUFFER_SKYSPHERE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);*/

	/*pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_SkySphere"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);*/

	/*pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);*/
		
	return S_OK;
}

CSkySphere* CSkySphere::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkySphere*		pInstance = new CSkySphere(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

