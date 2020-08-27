#include "stdafx.h"
#include "Accel_Torus.h"

#include "Export_Function.h"

CAccel_Torus::CAccel_Torus(LPDIRECT3DDEVICE9 pGraphicDev) 
	:Engine::CGameObject(pGraphicDev)
{
}

CAccel_Torus::~CAccel_Torus(void) {
}

HRESULT CAccel_Torus::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->Set_Scale(10000.f);
	m_pTransform->Set_Trans(&_vec3(0.f, 1000.f, 6000.f));
	m_pTransform->Update_Component(0.f);
	return S_OK;
}

void CAccel_Torus::Initialize_Object() {
}

_int CAccel_Torus::Update_Object(const _float & fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CAccel_Torus::Render_Object(void) {
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTorus->Render_Buffer();
}

void CAccel_Torus::Set_Trans(_vec3 & _vPos) {
	m_pTransform->Set_Trans(&_vPos);
	m_pTransform->Update_Component(0);
}

HRESULT CAccel_Torus::Add_Component(void) {
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"), E_FAIL);
	FAILED_CHECK_RETURN(Clone_Component<CTorus>(&m_pTorus, RESOURCE_STAGE, L"BUFFER_TORUS",ID_STATIC,L"Com_Buffer"), E_FAIL);

	
	return S_OK;
}

CAccel_Torus * CAccel_Torus::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CAccel_Torus* pInstance = new CAccel_Torus(pGraphicDev);
	if (FAILED(pInstance->Ready_Object())) {
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CAccel_Torus::Free(void) {
	Safe_Release(m_pTorus);
	Engine::CGameObject::Free();
}
