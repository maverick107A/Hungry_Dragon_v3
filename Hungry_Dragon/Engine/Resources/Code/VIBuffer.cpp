#include "VIBuffer.h"

USING(Engine)

Engine::CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
{

}

Engine::CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CResources(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

Engine::CVIBuffer::~CVIBuffer(void)
{

}

HRESULT Engine::CVIBuffer::Ready_Buffer(void)
{

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, // 버텍스의 최종 크기(버텍스 구조체의 크기 * 정점의 갯수)
															0,	// 버퍼를 어떤 것을 사용할 것인가(0인 경우는 정적 버퍼를 D3DUSAGE_DYNAMIC 동적 버퍼를 사용함)
															m_dwFVF,
															D3DPOOL_MANAGED, 
															&m_pVB,
															nullptr), 
															E_FAIL);

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 
															0,	// 버퍼를 어떤 것을 사용할 것인가(0인 경우는 정적 버퍼를 D3DUSAGE_DYNAMIC 동적 버퍼를 사용함)
															m_IdxFmt,
															D3DPOOL_MANAGED,
															&m_pIB,
															nullptr),
															E_FAIL);


	return S_OK;
}

void Engine::CVIBuffer::Render_Buffer(void)
{
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pGraphicDev->SetFVF(m_dwFVF);
	m_pGraphicDev->SetIndices(m_pIB);

	// 그리기 함수
	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

void CVIBuffer::Save_To_Dat(const char* _path, list<VTXCOL> _vertexList, list<INDEX16> _indexList)
{
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, _path, "wb");

	if (0 == err)
	{
		int vertexSize = (int)_vertexList.size();
		fwrite(&vertexSize, sizeof(int), 1, fp);

		for (list<VTXCOL>::iterator iter = _vertexList.begin(); iter != _vertexList.end(); ++iter)
		{
			VTXCOL tempVtx = (*iter);
			fwrite(&tempVtx, sizeof(VTXCOL), 1, fp);
		}

		int indexSize = (int)_indexList.size();
		fwrite(&indexSize, sizeof(int), 1, fp);

		for (list<INDEX16>::iterator iter = _indexList.begin(); iter != _indexList.end(); ++iter)
		{
			INDEX16 tempIdx = (*iter);
			fwrite(&tempIdx, sizeof(INDEX16), 1, fp);
		}

		fclose(fp);
	}
}

void Engine::CVIBuffer::Free(void)
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	CResources::Free();
}

