#include "BaseSector.h"

USING(Engine)

Engine::CBaseSector::CBaseSector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
{

}

Engine::CBaseSector::CBaseSector(const CBaseSector& rhs)
	: CResources(rhs)
{

}

Engine::CBaseSector::~CBaseSector(void)
{

}

HRESULT Engine::CBaseSector::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CBaseSector::Render_Buffer(void)
{

}

void Engine::CBaseSector::Free(void)
{
	CResources::Free();
}

CBaseSector* Engine::CBaseSector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBaseSector*	pInstance = new CBaseSector(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CBaseSector::Clone(void)
{
	return new CBaseSector(*this);
}

