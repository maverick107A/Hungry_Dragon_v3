#include "CaveCylinder.h"

USING(Engine)

Engine::CCaveCylinder::CCaveCylinder(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CCaveCylinder::CCaveCylinder(const CCaveCylinder& rhs)
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

Engine::CCaveCylinder::~CCaveCylinder(void)
{

}


// 코드 알고싶으면 dx11 방울책 예제소스의 GeometryGenerator 코드를 보면 다양한 모양의 코드가 있으니까 가져다 쓰심됨
HRESULT Engine::CCaveCylinder::Ready_Buffer(void)			// 어쨋든 원기둥 내면 그리는거임 영어로 주석 달아놓음
{
	// 실린더 세팅
	m_fHeight = 1000.f;		// 원기둥 시야
	m_uStackCount = 100;		// 절단면
	m_fStackHeight = m_fHeight / m_uStackCount;	
	m_fRadius = 10.f;			// 원기둥 반지름
	m_uRingCount = m_uStackCount + 1;
	m_uSliceCount = 24;			// 세로 절단면
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
		float z = -0.5f*m_fHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;


		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);
			
			float r = fOld_r*(1.f);
			vertex.vPosition = D3DXVECTOR3(r*c, r*s, z);

			UINT uColor = 96 * (1);
			vertex.dwColor = D3DCOLOR_XRGB(uColor, uColor, uColor);

			pVertex[m_uVtxNum] = vertex;
			++m_uVtxNum;
		}
		pVertex[m_uVtxNum] = pVertex[m_uVtxNum - m_uSliceCount];
		++m_uVtxNum;
	}
	// 몸통부
	for (UINT i = 1; i < m_uRingCount-1; ++i)
	{
		float z = -0.5f*m_fHeight + i*m_fStackHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;


		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);
			float fRand = (float)(rand() % 20 - 10) *0.02f;
			float r = fOld_r*(1.f+ fRand);
			vertex.vPosition = D3DXVECTOR3(r*c, r*s, z);

			UINT uColor = 96 * (1+ fRand*5.f);
			vertex.dwColor = D3DCOLOR_XRGB(uColor, uColor, uColor);

			pVertex[m_uVtxNum] = vertex;
			++m_uVtxNum;
		}
		pVertex[m_uVtxNum] = pVertex[m_uVtxNum- m_uSliceCount];
		++m_uVtxNum;
	}

	// 접합부
	for (UINT i = m_uRingCount-1; i < m_uRingCount; ++i)
	{
		float z = -0.5f*m_fHeight;
		float fOld_r = m_fRadius;

		// vertices of ring
		float dTheta = 2.0f*D3DX_PI / m_uSliceCount;


		for (UINT j = 0; j < m_uSliceCount; ++j)
		{
			VTXCOL vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);

			float r = fOld_r*(1.f);
			vertex.vPosition = D3DXVECTOR3(r*c, r*s, z);

			UINT uColor = 96 * (1);
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
			pIndex[uIdxNum] = { i*ringVertexCount + j ,(i + 1)*ringVertexCount + j,(i + 1)*ringVertexCount + j + 1 };
			++uIdxNum;

			pIndex[uIdxNum] = { i*ringVertexCount + j ,(i + 1)*ringVertexCount + j + 1,i*ringVertexCount + j + 1 };
			++uIdxNum;
		}
	}
	m_pIB->Unlock();

	return S_OK;
}

void Engine::CCaveCylinder::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CCaveCylinder::Free(void)
{
	CVIBuffer::Free();
}

CCaveCylinder* Engine::CCaveCylinder::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCaveCylinder*	pInstance = new CCaveCylinder(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CCaveCylinder::Clone(void)
{
	return new CCaveCylinder(*this);
}

