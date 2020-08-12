#include "CubeDra.h"

USING(Engine)

Engine::CCubeDra::CCubeDra(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CCubeDra::CCubeDra(const CCubeDra& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CCubeDra::~CCubeDra(void)
{

}

HRESULT Engine::CCubeDra::Ready_Buffer(void)
{
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = _vec3(-0.1f, 0.f, -0.4f);
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPosition = _vec3(-0.1f, 0.f, 0.1f);
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPosition = _vec3(0.1f, 0.f, 0.1f);
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[3].vPosition = _vec3(0.1f, 0.f, -0.4f);
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[4].vPosition = _vec3(-0.1f, 0.2f, -0.4f);
	pVertex[4].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[5].vPosition = _vec3(-0.1f, 0.2f, 0.1f);
	pVertex[5].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[6].vPosition = _vec3(0.1f, 0.2f, 0.1f);
	pVertex[6].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[7].vPosition = _vec3(0.1f, 0.2f, -0.4f);
	pVertex[7].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	
	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	//전면
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 4;
	pIndex[0]._2 = 3;

	pIndex[1]._0 = 3;
	pIndex[1]._1 = 4;
	pIndex[1]._2 = 7;
	//우면
	pIndex[2]._0 = 3;
	pIndex[2]._1 = 7;
	pIndex[2]._2 = 2;

	pIndex[3]._0 = 2;
	pIndex[3]._1 = 7;
	pIndex[3]._2 = 6;
	//후면
	pIndex[4]._0 = 2;
	pIndex[4]._1 = 6;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 1;
	pIndex[5]._1 = 6;
	pIndex[5]._2 = 5;
	//좌면
	pIndex[6]._0 = 1;
	pIndex[6]._1 = 5;
	pIndex[6]._2 = 0;

	pIndex[7]._0 = 0;
	pIndex[7]._1 = 5;
	pIndex[7]._2 = 4;
	//상면
	pIndex[8]._0 = 4;
	pIndex[8]._1 = 5;
	pIndex[8]._2 = 7;

	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 6;
	//하면
	pIndex[10]._0 = 1;
	pIndex[10]._1 = 0;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 2;
	pIndex[11]._1 = 0;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CCubeDra::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CCubeDra::Free(void)
{
	CVIBuffer::Free();
}

CCubeDra* Engine::CCubeDra::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeDra*	pInstance = new CCubeDra(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CCubeDra::Clone(void)
{
	return new CCubeDra(*this);
}

