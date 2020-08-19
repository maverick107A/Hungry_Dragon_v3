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
	m_vPosOrigin = _vec3(0.f, 100.f,0.f);
	return S_OK;
}

int CBillCloud_Object::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	_matrix matView;
	_matrix matScale;
	_matrix matTrans;
	_vec3	vecTrans;
	D3DXMatrixScaling(&matScale, 1920.f, 524.f, 1.f);			// 텍스처의 크기
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	memcpy(&vecTrans, &m_vPosOrigin, sizeof(_vec3));
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matScale * matView * m_pTransform->m_matWorld;
	memcpy( &m_pTransform->m_matWorld._41, &vecTrans, sizeof(_vec3));

	return 0;
}

void CBillCloud_Object::Render_Object(void) {

	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pTextureCom->Set_Texture();

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

void CBillCloud_Object::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CBillCloud_Object::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK(Clone_Component<CTexture_Square>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_TexSquare", ID_STATIC, L"Com_Buffer"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_BillCloud", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));

	return S_OK;
}

CBillCloud_Object* CBillCloud_Object::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CBillCloud_Object*		pInstance = new CBillCloud_Object(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

