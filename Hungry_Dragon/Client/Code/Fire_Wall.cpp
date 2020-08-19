#include "stdafx.h"
#include "Fire_Wall.h"

#include "Export_Function.h"

USING(Engine)

CFire_Wall::CFire_Wall(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CFire_Wall::~CFire_Wall(void) {

}

HRESULT CFire_Wall::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale.x = 2.f;
	m_pTransform->m_vScale.y = 2.f;

	m_pTransform->m_vInfo[Engine::INFO_POS] = _vec3(0.f,0.f,0.2f);
	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

int CFire_Wall::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	m_uLogo = (m_uLogo + 1) % 76;

	return 0;
}

void CFire_Wall::Render_Object(void) {
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture(m_uLogo/2);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	

}

void CFire_Wall::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CFire_Wall::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_FireWall"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);

	// Texture
	pComponent = m_pTextureMask = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"TEX_RED"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture2", pComponent);

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

CFire_Wall* CFire_Wall::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CFire_Wall*		pInstance = new CFire_Wall(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

