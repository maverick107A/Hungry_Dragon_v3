#include "stdafx.h"
#include "BackGround_Logo.h"

#include "Export_Function.h"

USING(Engine)

CBackGround_Logo::CBackGround_Logo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CBackGround_Logo::~CBackGround_Logo(void) {

}

HRESULT CBackGround_Logo::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransform->m_vScale.x = 2.f;
	//m_pTransform->m_vScale.y = 2.f;

	//m_pTransform->m_vInfo[Engine::INFO_POS].z = 0.2f;
	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

int CBackGround_Logo::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	return 0;
}

void CBackGround_Logo::Render_Object(void) {
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}

void CBackGround_Logo::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CBackGround_Logo::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_LOGO, L"Texture_Logo"));
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

CBackGround_Logo* CBackGround_Logo::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CBackGround_Logo*		pInstance = new CBackGround_Logo(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

