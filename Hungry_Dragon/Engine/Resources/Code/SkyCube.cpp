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
	// ¿ø ¼¼ÆÃ
	_float fRadius = 5.f;
	_uint uSliceCnt = 10;
	_uint uStackCnt = 10;
	int iVtxNum = 0;
	int iIdxNum = 0;

	m_dwVtxCnt = (uStackCnt-1) * (uSliceCnt+1) + 2;
	m_dwTriCnt = uSliceCnt * uStackCnt * 3;
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwFVF = FVF_CUBE;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);



	VTXCUBE*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	
	pVertex[iVtxNum].vPosition = { 0.f,fRadius,0.f };
	pVertex[iVtxNum].vTexUV = pVertex[iVtxNum].vPosition;
	++iVtxNum;

	float fDeltaPhi = D3DX_PI / uStackCnt;
	float fDeltaTheta = 2.f * D3DX_PI / uSliceCnt;

	for (_uint i = 1; i <= uStackCnt-1; ++i)
	{
		float fPhi = i*fDeltaPhi;
		for (_uint j = 0; j <= uSliceCnt; ++j)
		{
			float fTheta = j*fDeltaTheta;
			pVertex[iVtxNum].vPosition = { fRadius*sinf(fPhi)*cosf(fTheta),fRadius*cosf(fPhi),fRadius*sinf(fPhi)*sinf(fTheta) };
			pVertex[iVtxNum].vTexUV = pVertex[iVtxNum].vPosition;
			++iVtxNum;
		}
	}

	pVertex[iVtxNum].vPosition = { 0.f,-fRadius,0.f };
	pVertex[iVtxNum].vTexUV = pVertex[iVtxNum].vPosition;
	++iVtxNum;



	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_uint i = 1; i <= uSliceCnt; ++i)
	{
		pIndex[i - 1] = { 0, i + 1, i };
	}
	iIdxNum += uSliceCnt*3;

	_uint uBaseIndex = 1;
	_uint uRingVertexCount = uSliceCnt + 1;
	for (_uint i = 0; i < uStackCnt - 2; ++i)
	{
		for (_uint j = 0; j < uSliceCnt; ++j)
		{
			pIndex[iIdxNum++] = {uBaseIndex + i*uRingVertexCount + j, uBaseIndex + i*uRingVertexCount + j + 1, uBaseIndex + (i+1)*uRingVertexCount + j };
			pIndex[iIdxNum++] = { uBaseIndex + (i + 1)*uRingVertexCount + j, uBaseIndex + i*uRingVertexCount + j + 1, uBaseIndex + (i + 1)*uRingVertexCount + j+1 };
		}
	}
	
	_uint uSouthPoleIdx = iVtxNum - 1;
	uBaseIndex = uSouthPoleIdx - uRingVertexCount;

	for (_uint i = 0; i < uSliceCnt; ++i)
	{
		pIndex[iIdxNum++] = { uSouthPoleIdx, uBaseIndex+i, uBaseIndex+i+1 };
	}

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

