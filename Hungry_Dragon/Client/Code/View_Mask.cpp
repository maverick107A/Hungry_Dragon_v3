#include "stdafx.h"
#include "View_Mask.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "TestPlayer.h"
#include "CameraMain.h"

USING(Engine)

CView_Mask::CView_Mask(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CView_Mask::~CView_Mask(void) {

}

HRESULT CView_Mask::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pCam = dynamic_cast<CTestPlayer*>(::Get_Object(L"GameLogic", L"TestPlayer"))->Get_Camera();

	return S_OK;
}

int CView_Mask::Update_Object(const float& fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	_matrix matView;
	_matrix matScale;
	_matrix matTrans;
	_vec3	vecTrans = m_pCam->Get_Pos() + m_pCam->Get_Dir()*10.f;
	D3DXMatrixScaling(&matScale, 16.f+ m_fAccel*16.f, 9.f + m_fAccel*9.f, 1.f);			// 텍스처의 크기
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matScale* matView * m_pTransform->m_matWorld;
	memcpy( &m_pTransform->m_matWorld._41, &vecTrans, sizeof(_vec3));

	m_uTexFrame = (m_uTexFrame + 1) % 30;

	if (GetAsyncKeyState(VK_SHIFT) & 0x0001)
	{
		if (!m_bAccel)
		{
			Engine::Get_FMOD()->PlayEffect(L"FlightOnce");
		}
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_bAccel = true;
		m_fAccel -= fTimeDelta;
		if (0.f > m_fAccel)
		{
			m_fAccel = 0.f;
		}
	}
	else
	{
		m_bAccel = false;
		m_fAccel = 2.f;
	}

	return 0;
}

void CView_Mask::Render_Object(void) {
	if (!m_bAccel)
	{
		return;
	}
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pTextureCom->Set_Texture(m_uTexFrame);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, true);
}

void CView_Mask::Free(void) {
	Engine::CGameObject::Free();
}


HRESULT CView_Mask::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_Blur"));
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

CView_Mask* CView_Mask::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CView_Mask*		pInstance = new CView_Mask(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

