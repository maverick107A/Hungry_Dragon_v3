#include "stdafx.h"
#include "Page_Out.h"

#include "Export_Function.h"

USING(Engine)

CPage_Out::CPage_Out(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CPage_Out::~CPage_Out(void) {

}

HRESULT CPage_Out::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale.x = 2.f;
	m_pTransform->m_vScale.y = 2.f;

	m_pTransform->m_vInfo[Engine::INFO_POS].z = 0.2f;
	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);
	m_uLogo = 0;
	return S_OK;
}

int CPage_Out::Update_Object(const float& fTimeDelta) {

	if (!m_bActivate)
	{
		return 0;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	++m_uLogo;
	if (75 < m_uLogo)
	{
		m_uLogo = 75;
		m_bPageOut = true;
	}

	return 0;
}

void CPage_Out::Render_Object(void) {
	if (!m_bActivate)
	{
		return;
	}

	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture(m_uLogo);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}

Engine::_bool CPage_Out::Set_Activate(Engine::_bool _bActivate)
{
	Engine::Get_FMOD()->PlayEffect(L"BreathTest"); 
	return m_bActivate = _bActivate;
}

void CPage_Out::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CPage_Out::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_SceneChange"));
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

CPage_Out* CPage_Out::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CPage_Out*		pInstance = new CPage_Out(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

