#include "GlacierTex.h"

USING(Engine)

Engine::CGlacierTex::CGlacierTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CGlacierTex::CGlacierTex(const CGlacierTex& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CGlacierTex::~CGlacierTex(void)
{

}

HRESULT Engine::CGlacierTex::Ready_Buffer(void)
{
	// ���ؽ� ���� ���� �޽� �� ������ -> �ٵ� ���� ���� �о����

	return S_OK;
}

void Engine::CGlacierTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CGlacierTex::Free(void)
{
	CVIBuffer::Free();
}

CGlacierTex* Engine::CGlacierTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGlacierTex*	pInstance = new CGlacierTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CGlacierTex::Clone(void)
{
	return new CGlacierTex(*this);
}

