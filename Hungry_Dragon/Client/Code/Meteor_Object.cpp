#include "stdafx.h"
#include "Meteor_Object.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"

USING(Engine)

CMeteor_Object::CMeteor_Object(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CMeteor_Object::~CMeteor_Object(void) {

}

HRESULT CMeteor_Object::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fForwardSpeed = 10000.f;
	return S_OK;
}

int CMeteor_Object::Update_Object(const float& fTimeDelta) {
		Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	//m_pTransform->Add_Trans(&_vec3(0.f, -m_fForwardSpeed * fTimeDelta,0.f));
	
	_matrix matView;
	_matrix matScale;
	_matrix matTrans;
	_vec3	vecTrans;
	if (m_bBoom)
	{
		D3DXMatrixScaling(&matScale, 5120.f, 5120.f, 1.f);			// 텍스처의 크기
	}
	else
	{
		m_vPosOrigin += _vec3(0.f, -m_fForwardSpeed * fTimeDelta, 0.f);
		D3DXMatrixScaling(&matScale, 2560.f, 2560.f, 1.f);			// 텍스처의 크기
	}
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	memcpy(&vecTrans, &m_vPosOrigin, sizeof(_vec3));
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matScale* matView * m_pTransform->m_matWorld;
	memcpy(&m_pTransform->m_matWorld._41, &vecTrans, sizeof(_vec3));

	if (m_bBoom)
	{
		++m_uTexFrame;
		if (15 < m_uTexFrame)
		{
			m_bActive = false;
			m_bBoom = false;
		}
	}
	else
	{
		m_uTexFrame = (m_uTexFrame + 1) % 16;
		if (m_vPosOrigin.y < 1000.f)
		{
			m_bBoom = true;
			m_uTexFrame = 0;
		}
	}



	return 0;
}

void CMeteor_Object::Render_Object(void) {

	if (!m_bActive)
		return;

	m_pTransform->Set_Transform(m_pGraphicDev);
	
	if (m_bBoom)
	{
		m_pTextureBoom->Set_Texture(m_uTexFrame/3);

	}
	else
	{
		m_pTextureCom->Set_Texture(m_uTexFrame);
	}
	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void CMeteor_Object::Free(void) {
	Engine::CGameObject::Free();
}


void CMeteor_Object::Set_Trans(_vec3& _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
	m_vPosOrigin = _vPos;
	m_pTransform->Update_Component(0);
}

HRESULT CMeteor_Object::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK(Clone_Component<CTexture_Square>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_TexSquare", ID_STATIC, L"Com_Buffer"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_Meteor", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureBoom, RESOURCE_STAGE, L"Texture_Boom", ID_STATIC, L"Com_Texture2"));
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));

	return S_OK;
}

CMeteor_Object* CMeteor_Object::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CMeteor_Object*		pInstance = new CMeteor_Object(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

