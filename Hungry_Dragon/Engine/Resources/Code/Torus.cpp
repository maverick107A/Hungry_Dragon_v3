#include "Torus.h"

USING(Engine)

CTorus::CTorus(LPDIRECT3DDEVICE9 pGraphicDev)
	:CResources(pGraphicDev)
	,m_pTorus(nullptr)
{

}

CTorus::CTorus(const CTorus & rhs)
	:CResources(rhs)
	,m_pTorus(rhs.m_pTorus)
	,m_fInnerRadius(rhs.m_fInnerRadius)
	,m_fOuterRadius(rhs.m_fOuterRadius)
{
	m_pTorus->AddRef();
}

CTorus::~CTorus(void) {
}

HRESULT CTorus::Ready_Buffer(void) {
	return D3DXCreateTorus(m_pGraphicDev, m_fInnerRadius, m_fOuterRadius, 10, 10, &m_pTorus, nullptr);
}

void CTorus::Render_Buffer(void) {
	m_pTorus->DrawSubset(0);
}

CTorus * CTorus::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CTorus*	pInstance = new CTorus(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CTorus::Clone(void) {
	return new CTorus(*this);
}

void CTorus::Free(void) {
	Safe_Release(m_pTorus);

	CResources::Free();
}
