#include "stdafx.h"
#include "Logo_Loop.h"

#include "Export_Function.h"

USING(Engine)

CLogo_Loop::CLogo_Loop(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CLogo_Loop::~CLogo_Loop(void) {

}

HRESULT CLogo_Loop::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale.x = 0.18f;
	m_pTransform->m_vScale.y = 0.32f;

	m_pTransform->m_vInfo[Engine::INFO_POS] = _vec3(0.82f,-0.68f,0.2f);
	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

int CLogo_Loop::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	m_uLogo = (m_uLogo + 1) % 240;

	return 0;
}

void CLogo_Loop::Render_Object(void) {
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture(m_uLogo/4);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CLogo_Loop::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CLogo_Loop::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_LOGO, L"Texture_LoadingLoop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	//// Renderer
	//pComponent = m_pRendererCom = Engine::Get_Renderer();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//pComponent->AddRef();
	//m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Renderer", pComponent);

	return S_OK;
}

CLogo_Loop* CLogo_Loop::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CLogo_Loop*		pInstance = new CLogo_Loop(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

