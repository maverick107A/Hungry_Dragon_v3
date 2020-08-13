#include "RoadSector.h"

USING(Engine)

Engine::CRoadSector::CRoadSector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseSector(pGraphicDev)
{

}

Engine::CRoadSector::CRoadSector(const CRoadSector& rhs)
	: CBaseSector(rhs)
{

}

Engine::CRoadSector::~CRoadSector(void)
{

}

HRESULT Engine::CRoadSector::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CRoadSector::Render_Buffer(void)
{

}

void Engine::CRoadSector::Free(void)
{
	CResources::Free();
}

CRoadSector* Engine::CRoadSector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRoadSector*	pInstance = new CRoadSector(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CRoadSector::Clone(void)
{
	return new CRoadSector(*this);
}

