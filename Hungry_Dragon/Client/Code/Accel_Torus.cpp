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
	return S_OK;
}

void CAccel_Torus::Initialize_Object() {
}

_int CAccel_Torus::Update_Object(const _float & fTimeDelta) {
	Engine::CGameObject::Update_Object(fTimeDelta);
	return _int();
}

void CAccel_Torus::Render_Object(void) {
}

void CAccel_Torus::Set_Transe(_vec3 & _vPos) {
}

HRESULT CAccel_Torus::Add_Component(void) {
	return E_NOTIMPL;
}

CAccel_Torus * CAccel_Torus::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	return nullptr;
}

void CAccel_Torus::Free(void) {
}
