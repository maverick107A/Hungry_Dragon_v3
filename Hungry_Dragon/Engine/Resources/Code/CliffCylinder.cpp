#include "CliffCylinder.h"

USING(Engine)

Engine::CCliffCylinder::CCliffCylinder(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CCliffCylinder::CCliffCylinder(const CCliffCylinder& rhs)
	: CVIBuffer(rhs)
{
	m_fHeight = rhs.m_fHeight;		// 원기둥 시야
	m_uStackCount = rhs.m_uStackCount;		// 절단면
	m_fStackHeight = rhs.m_fStackHeight;
	m_fRadius = rhs.m_fRadius;			// 원기둥 반지름
	m_uRingCount = rhs.m_uRingCount;
	m_uSliceCount = rhs.m_uSliceCount;			// 세로 절단면
	m_uVtxNum = rhs.m_uVtxNum;
}

Engine::CCliffCylinder::~CCliffCylinder(void)
{

}


// 코드 알고싶으면 dx11 방울책 예제소스의 GeometryGenerator 코드를 보면 다양한 모양의 코드가 있으니까 가져다 쓰심됨
HRESULT Engine::CCliffCylinder::Ready_Buffer(void)			// 어쨋든 원기둥 내면 그리는거임 영어로 주석 달아놓음
{
	// 실린더 세팅
	m_fHeight = 5000.f;		// 원기둥 시야
	m_uStackCount = 10;		// 절단면
	m_fStackHeight = m_fHeight / m_uStackCount;	
	m_fRadius = 10000.f;			// 원기둥 반지름
	m_uRingCount = m_uStackCount + 1;
	m_uSliceCount = 48;			// 세로 절단면
	m_uVtxNum = 0;

	// Compute vertices for each stack ring starting at the bottom and moving up.


	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	m_dwVtxCnt = (m_uSliceCount + 1) * (m_uStackCount + 1);
	m_dwTriCnt = m_uSliceCount * m_uStackCount * 2;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);



	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	// 접합부
	for (UINT i = 0; i < 1; ++i)
	{
		float fHeightY = -0.5f*m_fHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;


		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float fCos = cosf(j*dTheta);
			float fSin = sinf(j*dTheta);
			
			float fRandomR = fOld_r*(1.f);
			vertex.vPosition = D3DXVECTOR3(fRandomR*fCos, fHeightY, fRandomR*fSin);

			UINT uColor = 80;
			vertex.dwColor = D3DCOLOR_XRGB(uColor, uColor>>1, uColor>>2);

			pVertex[m_uVtxNum] = vertex;
			++m_uVtxNum;
		}
		pVertex[m_uVtxNum] = pVertex[m_uVtxNum - m_uSliceCount];
		++m_uVtxNum;
	}
	// 몸통부
	for (UINT i = 1; i < m_uRingCount-1; ++i)
	{
		float fHeightY = -0.5f*m_fHeight + i*m_fStackHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;
		float fRand = (float)(rand() % 20 - 10) *0.01f;
		
		

		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float fCos = cosf(j*dTheta);
			float fSin = sinf(j*dTheta);
			float fRandDetail = (float)(rand() % 20 - 10) *0.01f;
			float fRandomR = fOld_r*(1.f + fRand*0.2f + fRandDetail*0.1f);
			vertex.vPosition = D3DXVECTOR3(fRandomR*fCos, fHeightY, fRandomR*fSin);

			UINT uColor = (_uint)(30.f * (1.f- fRand*2.f - fRandDetail));
			vertex.dwColor = D3DCOLOR_XRGB(uColor*3, uColor*2, uColor);

			pVertex[m_uVtxNum] = vertex;
			++m_uVtxNum;
		}
		pVertex[m_uVtxNum] = pVertex[m_uVtxNum- m_uSliceCount];
		++m_uVtxNum;
	}

	// 접합부
	for (UINT i = m_uRingCount-1; i < m_uRingCount; ++i)
	{
		float fHeightY = 0.5f*m_fHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;


		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float fCos = cosf(j*dTheta);
			float fSin = sinf(j*dTheta);

			float fRandomR = fOld_r*(1.f);
			vertex.vPosition = D3DXVECTOR3(fRandomR*fCos, fHeightY, fRandomR*fSin);

			UINT uColor = 60;
			vertex.dwColor = D3DCOLOR_XRGB(uColor, uColor, uColor);

			pVertex[m_uVtxNum] = vertex;
			++m_uVtxNum;
		}
		pVertex[m_uVtxNum] = pVertex[m_uVtxNum - m_uSliceCount];
		++m_uVtxNum;
	}




	m_pVB->Unlock();


	INDEX32*		pIndex = nullptr;
	UINT			uIdxNum = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	UINT ringVertexCount = m_uSliceCount + 1;

	for (UINT i = 0; i < m_uStackCount; ++i)
	{
		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			pIndex[uIdxNum] = { i*ringVertexCount + j  ,(i + 1)*ringVertexCount + j ,(i + 1)*ringVertexCount + j + 1 };
			++uIdxNum;

			pIndex[uIdxNum] = { i*ringVertexCount + j ,(i + 1)*ringVertexCount + j + 1,i*ringVertexCount + j + 1 };
			++uIdxNum;
		}
	}
	m_pIB->Unlock();

	return S_OK;
}

void Engine::CCliffCylinder::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CCliffCylinder::Free(void)
{
	CVIBuffer::Free();
}

CCliffCylinder* Engine::CCliffCylinder::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCliffCylinder*	pInstance = new CCliffCylinder(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CCliffCylinder::Clone(void)
{
	return new CCliffCylinder(*this);
}

