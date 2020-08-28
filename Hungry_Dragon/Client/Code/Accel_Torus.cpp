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

	GOLD_MATERIAL.Ambient = GOLD;
	GOLD_MATERIAL.Diffuse = GOLD;
	GOLD_MATERIAL.Specular = GOLD;
	GOLD_MATERIAL.Emissive = GOLD;
	GOLD_MATERIAL.Power = 2.f;
	return S_OK;
}

void CAccel_Torus::Initialize_Object() {
}

_int CAccel_Torus::Update_Object(const _float & fTimeDelta) {
	m_pTransform->Rotation(Engine::ROT_Z, D3DXToRadian(1.f));
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CAccel_Torus::Render_Object(void) {
	D3DMATERIAL9 tempMaterial;
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, true);
	m_pGraphicDev->GetMaterial(&tempMaterial);
	m_pGraphicDev->SetMaterial(&GOLD_MATERIAL);
	m_pTorus->Render_Buffer();
	m_pGraphicDev->SetMaterial(&tempMaterial);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);
}

void CAccel_Torus::Get_Radius(_float * _fInnerRadius, _float * _fOuterRadius)
{
	if (nullptr != m_pTorus)
		m_pTorus->Get_Radius(_fInnerRadius, _fOuterRadius);
}

_vec3 CAccel_Torus::Get_Pos()
{
	_matrix tempMatrix = m_pTransform->Get_World();
	return _vec3(tempMatrix._41, tempMatrix._42, tempMatrix._43);
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
