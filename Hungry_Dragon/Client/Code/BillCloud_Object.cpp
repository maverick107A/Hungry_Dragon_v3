#include "stdafx.h"
#include "BillCloud_Object.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"

USING(Engine)

CBillCloud_Object::CBillCloud_Object(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CBillCloud_Object::~CBillCloud_Object(void) {

}

HRESULT CBillCloud_Object::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int CBillCloud_Object::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	_matrix matView;
	_matrix matScale;
	_matrix matTrans;
	_vec3	vecTrans;
	D3DXMatrixScaling(&matScale, 1600.f, 900.f, 1.f);			// 텍스처의 크기
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	memcpy(&vecTrans, &matView._41, sizeof(_vec3));
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matScale* matView * m_pTransform->m_matWorld;
	memcpy( &m_pTransform->m_matWorld._41, &vecTrans, sizeof(_vec3));

	m_uTexFrame = (m_uTexFrame + 1) % 30;

	return 0;
}

void CBillCloud_Object::Render_Object(void) {

	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pTextureCom->Set_Texture(m_uTexFrame);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, true);
}

void CBillCloud_Object::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CBillCloud_Object::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_BillCloud"));
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

CBillCloud_Object* CBillCloud_Object::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CBillCloud_Object*		pInstance = new CBillCloud_Object(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

