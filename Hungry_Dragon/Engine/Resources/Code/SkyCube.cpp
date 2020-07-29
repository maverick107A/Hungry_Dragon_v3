#include "SkyCube.h"

USING(Engine)

Engine::CSkyCube::CSkyCube(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CSkyCube::CSkyCube(const CSkyCube& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CSkyCube::~CSkyCube(void)
{

}

HRESULT Engine::CSkyCube::Ready_Buffer(void)
{
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;
	m_dwVtxSize = sizeof(VTXUV);
	m_dwFVF = FVF_UV;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);



	VTXUV*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = { 0.f,0.f,0.f,0.f,0.f};

	m_pVB->Unlock();

	WORD*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 사각형 면을 표현하기 위한 6개의 인덱스를 기준으로 반복문을 돌림
	int baseIndex = 0;

	

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CSkyCube::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CSkyCube::Free(void)
{
	CVIBuffer::Free();
}

CSkyCube* Engine::CSkyCube::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkyCube*	pInstance = new CSkyCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CSkyCube::Clone(void)
{
	return new CSkyCube(*this);
}

