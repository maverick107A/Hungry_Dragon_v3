#include "CubeCol.h"

USING(Engine)

Engine::CCubeCol::CCubeCol(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CVIBuffer(pGraphicDev)
{
}

Engine::CCubeCol::CCubeCol(const CCubeCol & rhs) 
	:CVIBuffer(rhs)
{
}

Engine::CCubeCol::~CCubeCol(void) {
}

HRESULT Engine::CCubeCol::Ready_Buffer(void) {
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	//각각의 버텍스 위치를 잡아준다
	pVertex[0].vPosition = _vec3{ -1.f,-1.f,-1.f };
	pVertex[1].vPosition = _vec3{ -1.f,1.f,-1.f };
	pVertex[2].vPosition = _vec3{ 1.f,1.f,-1.f };
	pVertex[3].vPosition = _vec3{ 1.f,-1.f,-1.f };
	pVertex[4].vPosition = _vec3{ -1.f,-1.f,1.f };
	pVertex[5].vPosition = _vec3{ -1.f,1.f,1.f };
	pVertex[6].vPosition = _vec3{ 1.f,1.f,1.f };
	pVertex[7].vPosition = _vec3{ 1.f,-1.f,1.f };

	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVertex[1].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 1.f, 1.f);
	pVertex[4].dwColor = D3DXCOLOR(1.f, 1.f, 0.f, 1.f);
	pVertex[5].dwColor = D3DXCOLOR(0.f, 1.f, 1.f, 1.f);
	pVertex[6].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pVertex[7].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	m_pVB->Unlock();

	INDEX16* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	//각각의 인덱스 배열에 그리고자 하는 순서대로 삽입
	pIndex[0]._0 = 0; pIndex[0]._1 = 1; pIndex[0]._2 = 2;
	pIndex[1]._0 = 0; pIndex[1]._1 = 2; pIndex[1]._2 = 3;
	pIndex[2]._0 = 4; pIndex[2]._1 = 6; pIndex[2]._2 = 5;
	pIndex[3]._0 = 4; pIndex[3]._1 = 7; pIndex[3]._2 = 6;
	pIndex[4]._0 = 4; pIndex[4]._1 = 5; pIndex[4]._2 = 1;
	pIndex[5]._0 = 4; pIndex[5]._1 = 1; pIndex[5]._2 = 0;
	pIndex[6]._0 = 3; pIndex[6]._1 = 2; pIndex[6]._2 = 6;
	pIndex[7]._0 = 3; pIndex[7]._1 = 6; pIndex[7]._2 = 7;
	pIndex[8]._0 = 1; pIndex[8]._1 = 5; pIndex[8]._2 = 6;
	pIndex[9]._0 = 1; pIndex[9]._1 = 6; pIndex[9]._2 = 2;
	pIndex[10]._0 = 4; pIndex[10]._1 = 0; pIndex[10]._2 = 3;
	pIndex[11]._0 = 4; pIndex[11]._1 = 3; pIndex[11]._2 = 7;


	m_pIB->Unlock();
	return S_OK;
}

void Engine::CCubeCol::Render_Buffer(void) {
	CVIBuffer::Render_Buffer();
}

CCubeCol* Engine::CCubeCol::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CCubeCol* pInstance = new CCubeCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CCubeCol::Clone(void) {
	return new CCubeCol(*this);
}

void Engine::CCubeCol::Free(void) {
	CVIBuffer::Free();
}
