#include "stdafx.h"
#include "Select_Map.h"

#include "Export_Function.h"

USING(Engine)

CSelect_Map::CSelect_Map(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CSelect_Map::~CSelect_Map(void) {

}

HRESULT CSelect_Map::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale.x = 0.5f;
	m_pTransform->m_vScale.y = 0.5f;

	m_pTransform->m_vInfo[Engine::INFO_POS] = _vec3(0.f, -0.4f, 0.2f);
	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

int CSelect_Map::Update_Object(const float& fTimeDelta) {

	if (m_bFocused)
	{
		m_pTransform->m_vScale.x = 0.6f;
		m_pTransform->m_vScale.y = 0.6f;
	}
	else
	{
		m_pTransform->m_vScale.x = 0.4f;
		m_pTransform->m_vScale.y = 0.4f;
	}

	if (fabsf(m_pTransform->m_vInfo[Engine::INFO_POS].x - m_fLerpX) < 0.01f)
	{
		m_pTransform->m_vInfo[Engine::INFO_POS].x = m_fLerpX;
	}
	else
	{
		m_pTransform->m_vInfo[Engine::INFO_POS].x = (m_pTransform->m_vInfo[Engine::INFO_POS].x + m_fLerpX) *0.5f;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	

	return 0;
}

void CSelect_Map::Render_Object(void) {
	
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture(m_uMapNum);


	m_pBufferCom->Render_Buffer();

}

void CSelect_Map::Free(void) {
	Engine::CGameObject::Free();
}


void CSelect_Map::Set_PosX(Engine::_float _fX)
{
	m_pTransform->m_vInfo[Engine::INFO_POS].x = _fX;
}

HRESULT CSelect_Map::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_LOGO, L"Texture_SelectMap"));
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

CSelect_Map* CSelect_Map::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CSelect_Map*		pInstance = new CSelect_Map(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

