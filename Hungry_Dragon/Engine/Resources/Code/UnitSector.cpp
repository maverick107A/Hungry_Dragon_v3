#include "UnitSector.h"

USING(Engine)

Engine::CUnitSector::CUnitSector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseSector(pGraphicDev)
{

}

Engine::CUnitSector::CUnitSector(const CUnitSector& rhs)
	: CBaseSector(rhs)
{

}

Engine::CUnitSector::~CUnitSector(void)
{

}

HRESULT Engine::CUnitSector::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CUnitSector::Render_Buffer(void)
{

}

void Engine::CUnitSector::Free(void)
{
	CResources::Free();
}

CUnitSector* Engine::CUnitSector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUnitSector*	pInstance = new CUnitSector(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CUnitSector::Clone(void)
{
	return new CUnitSector(*this);
}

