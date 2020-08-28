#include "stdafx.h"
#include "Meteor_Circular.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Line_Renderer.h"
#include "Ingame_Flow.h"

USING(Engine)

CMeteor_Circular::CMeteor_Circular(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMeteor_Object(pGraphicDev) {

}

CMeteor_Circular::~CMeteor_Circular(void) {

}

HRESULT CMeteor_Circular::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int CMeteor_Circular::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);
	
	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	//m_pTransform->Add_Trans(&_vec3(0.f, -m_fForwardSpeed * fTimeDelta,0.f));
	
	_matrix matView;
	_matrix matScale;
	_matrix matRot;
	_matrix matTrans;
	_vec3	vecTrans;
	if (m_bBoom)
	{
		D3DXMatrixScaling(&matScale, 1024.f, 1024.f, 1.f);			// 텍스처의 크기
	}
	else
	{
		m_fAngle += fTimeDelta * m_fRotateSpeed;
		if (2.f*D3DX_PI < m_fAngle)
		{
			m_fAngle -= 2.f*D3DX_PI;
		}
		D3DXMatrixTranslation(&matTrans, m_vRadius.x, m_vRadius.y, m_vRadius.z);
		D3DXMatrixRotationAxis(&matRot, &m_vAxis, m_fAngle);
		D3DXMatrixScaling(&matScale, 512.f, 512.f, 1.f);			// 텍스처의 크기
		matTrans = matScale * matTrans * matRot;
		D3DXVec3TransformCoord(&m_vPosOrigin, &_vec3(0.f,0.f,0.f), &matTrans);
		m_vPosOrigin += m_vCenter;
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

		// 충돌
		_vec3 vDist = CIngame_Flow::GetInstance()->Get_PlayerTransform()->m_vInfo[INFO_POS] - m_vPosOrigin;
		if (D3DXVec3Dot(&vDist, &vDist) < 57600.f)
		{
			m_bBoom = true;
			CIngame_Flow::GetInstance()->Get_PlayerObject()->Add_Hp(-40);
		}
	}

	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);
	CLine_Renderer::GetInstance()->Draw_Dot(vPos.x, vPos.y , vPos.z , 512.f, 512.f, D3DCOLOR_ARGB(255, 255,255,255));


	_uint uRand = rand() % 10 + 5;
	for (int i = 0; i < 1; ++i)
	{
		CLine_Renderer::GetInstance()->Draw_Dot(vPos.x+((rand()%256) - 128), vPos.y + ((rand() % 256) - 128), vPos.z + ((rand() % 256) - 128), 384.f, 256.f, D3DCOLOR_ARGB(255, 255,255,255));
	}
	return 0;
}

void CMeteor_Circular::Render_Object(void) {

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

void CMeteor_Circular::Free(void) {

	CMeteor_Object::Free();
}


HRESULT CMeteor_Circular::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK(Clone_Component<CTexture_Square>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_TexSquare", ID_STATIC, L"Com_Buffer"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_Meteor", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureBoom, RESOURCE_STAGE, L"Texture_Boom", ID_STATIC, L"Com_Texture2"));
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));


	return S_OK;
}

CMeteor_Circular* CMeteor_Circular::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CMeteor_Circular*		pInstance = new CMeteor_Circular(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

