#include "BaseBoard.h"

USING(Engine)

Engine::CBaseBoard::CBaseBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
{

}

Engine::CBaseBoard::CBaseBoard(const CBaseBoard& rhs)
	: CResources(rhs)
{

}

Engine::CBaseBoard::~CBaseBoard(void)
{

}

HRESULT Engine::CBaseBoard::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CBaseBoard::Render_Buffer(void)
{

}

void Engine::CBaseBoard::Free(void)
{
	CResources::Free();
}

CBaseBoard* Engine::CBaseBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBaseBoard*	pInstance = new CBaseBoard(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CBaseBoard::Clone(void)
{
	return new CBaseBoard(*this);
}

