#include "RockTex.h"

USING(Engine)

Engine::CRockTex::CRockTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CRockTex::CRockTex(const CRockTex& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CRockTex::~CRockTex(void)
{

}

HRESULT Engine::CRockTex::Ready_Buffer(void)
{
	// ���ؽ� ���� ���� �޽� �� ������ -> �ٵ� ���� ���� �о����

	return S_OK;
}

void Engine::CRockTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CRockTex::Set_Side(void * _bitmap)
{
	// ���߿� �浹 ������ ��� �� ���̰� �����
}

void Engine::CRockTex::Free(void)
{
	CVIBuffer::Free();
}

CRockTex* Engine::CRockTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRockTex*	pInstance = new CRockTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CRockTex::Clone(void)
{
	return new CRockTex(*this);
}

