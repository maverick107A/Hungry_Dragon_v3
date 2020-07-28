#include "MeteorBoard.h"

USING(Engine)

Engine::CMeteorBoard::CMeteorBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseBoard(pGraphicDev)
{

}

Engine::CMeteorBoard::CMeteorBoard(const CMeteorBoard& rhs)
	: CBaseBoard(rhs)
{

}

Engine::CMeteorBoard::~CMeteorBoard(void)
{

}

HRESULT Engine::CMeteorBoard::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CMeteorBoard::Render_Buffer(void)
{

}

void Engine::CMeteorBoard::Free(void)
{
	CResources::Free();
}

CMeteorBoard* Engine::CMeteorBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMeteorBoard*	pInstance = new CMeteorBoard(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CMeteorBoard::Clone(void)
{
	return new CMeteorBoard(*this);
}

