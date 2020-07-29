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
	// 버텍스 툴로 바위 메쉬 찍어서 읽을거 -> 근데 여러 종류 읽어야함

	return S_OK;
}

void Engine::CRockTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CRockTex::Set_Side(void * _bitmap)
{
	// 나중에 충돌 부위의 경우 좀 파이게 만들거
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

