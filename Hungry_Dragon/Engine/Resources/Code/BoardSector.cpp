#include "BoardSector.h"

USING(Engine)

Engine::CBoardSector::CBoardSector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseSector(pGraphicDev)
{

}

Engine::CBoardSector::CBoardSector(const CBoardSector& rhs)
	: CBaseSector(rhs)
{

}

Engine::CBoardSector::~CBoardSector(void)
{

}

HRESULT Engine::CBoardSector::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CBoardSector::Render_Buffer(void)
{

}

void Engine::CBoardSector::Free(void)
{
	CResources::Free();
}

CBoardSector* Engine::CBoardSector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBoardSector*	pInstance = new CBoardSector(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CBoardSector::Clone(void)
{
	return new CBoardSector(*this);
}

