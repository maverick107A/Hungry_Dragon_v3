#include "stdafx.h"
#include "Bill_Line.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"

USING(Engine)

CBill_Line::CBill_Line(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CBill_Line::~CBill_Line(void) {

}

HRESULT CBill_Line::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_vPosOrigin = _vec3(0.f, 100.f,0.f);
	//m_vScaleOrigin = { 50.f,50.f,1.f };
	m_fScale = 50.f;
	m_fShrinkSpeed = 1.f;
	return S_OK;
}

int CBill_Line::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	_matrix matView;
	_matrix matScale;
	_matrix matTrans;
	_vec3	vecTrans;
	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, 1.f);			// 텍스처의 크기
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	memcpy(&vecTrans, &m_vPosOrigin, sizeof(_vec3));
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matScale * matView * m_pTransform->m_matWorld;
	memcpy( &m_pTransform->m_matWorld._41, &vecTrans, sizeof(_vec3));

	// 점점 사라지고 삭제
	//m_vPosOrigin.x += 1000.f * fTimeDelta;
	m_fScale -= m_fShrinkSpeed * fTimeDelta;
	if (0.f > m_fScale)
	{
		return OBJ_DEAD;
	}

	return 0;
}

void CBill_Line::Render_Object(void) {

	m_pTransform->Set_Transform(m_pGraphicDev);
	
	//m_pTextureCom->Set_Texture();
	//
	//m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pBufferCom->Render_Buffer();
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

void CBill_Line::Render_Sprite(LPDIRECT3DTEXTURE9 _pTex)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	RECT tRect = { 0,0,64,64 };
	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, 0.f);
	D3DXMatrixTranslation(&matTrans, m_vPosOrigin.x, m_vPosOrigin.y, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(_pTex, &tRect, nullptr, nullptr, m_dwColor);
}

void CBill_Line::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CBill_Line::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	//// buffer
	FAILED_CHECK(Clone_Component<CTexture_Square>(&m_pBufferCom, RESOURCE_STATIC, L"Buffer_TexSquare", ID_STATIC, L"Com_Buffer"));
	//FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_BillDot", ID_STATIC, L"Com_Texture"));
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));

	return S_OK;
}

CBill_Line* CBill_Line::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CBill_Line*		pInstance = new CBill_Line(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

