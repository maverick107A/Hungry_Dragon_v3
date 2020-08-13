#include "TreeBoard.h"

USING(Engine)

Engine::CTreeBoard::CTreeBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseBoard(pGraphicDev)
{

}

Engine::CTreeBoard::CTreeBoard(const CTreeBoard& rhs)
	: CBaseBoard(rhs)
{

}

Engine::CTreeBoard::~CTreeBoard(void)
{

}

HRESULT Engine::CTreeBoard::Ready_Buffer(void)
{
	

	return S_OK;
}

void Engine::CTreeBoard::Render_Buffer(void)
{

}

void Engine::CTreeBoard::Free(void)
{
	CResources::Free();
}

CTreeBoard* Engine::CTreeBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTreeBoard*	pInstance = new CTreeBoard(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CTreeBoard::Clone(void)
{
	return new CTreeBoard(*this);
}

