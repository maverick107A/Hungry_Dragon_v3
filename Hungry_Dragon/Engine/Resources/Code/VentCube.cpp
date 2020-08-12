#include "VentCube.h"

USING(Engine)

Engine::CVentCube::CVentCube(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CVentCube::CVentCube(const CVentCube& rhs)
	: CVIBuffer(rhs)
{
	m_fHeight = rhs.m_fHeight;		// 큐브길이
}

Engine::CVentCube::~CVentCube(void)
{

}


// 코드 알고싶으면 dx11 방울책 예제소스의 GeometryGenerator 코드를 보면 다양한 모양의 코드가 있으니까 가져다 쓰심됨
HRESULT Engine::CVentCube::Ready_Buffer(void)			// 어쨋든 원기둥 내면 그리는거임 영어로 주석 달아놓음
{
	// 실린더 세팅
	m_fHeight = 1000.f;		// 원기둥 시야
	m_fRadius = 5.f;
	float fSliceCnt = m_fHeight / m_fRadius * 0.5f;

	// Compute vertices for each stack ring starting at the bottom and moving up.


	m_dwVtxSize = sizeof(VTXUV);
	m_dwFVF = FVF_UV;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	m_dwVtxCnt = 8;
	m_dwTriCnt = 8;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);



	VTXUV*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = { -m_fRadius,m_fRadius,m_fHeight*0.5f, 0.f, -fSliceCnt*0.5f};
	pVertex[1] = { m_fRadius,m_fRadius,m_fHeight*0.5f, 1.f, -fSliceCnt*0.5f };
	pVertex[2] = { m_fRadius,-m_fRadius,m_fHeight*0.5f, 0.f, -fSliceCnt*0.5f };
	pVertex[3] = {-m_fRadius,-m_fRadius,m_fHeight*0.5f, 1.f,-fSliceCnt*0.5f };

	pVertex[4] = { -m_fRadius,m_fRadius, -m_fHeight*0.5f, 0.f, fSliceCnt*0.5f };
	pVertex[5] = { m_fRadius,m_fRadius, -m_fHeight*0.5f, 1.f, fSliceCnt*0.5f };
	pVertex[6] = { m_fRadius,-m_fRadius, -m_fHeight*0.5f, 0.f,fSliceCnt*0.5f };
	pVertex[7] = { -m_fRadius,-m_fRadius, -m_fHeight*0.5f,1.f ,fSliceCnt*0.5f };

	m_pVB->Unlock();


	INDEX16*		pIndex = nullptr;
	UINT			uIdxNum = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0] = { 3,2,6 };
	pIndex[1] = { 3,6,7 };
	pIndex[2] = { 2,1,5 };
	pIndex[3] = { 2,5,6 };
	pIndex[4] = { 1,0,4 };
	pIndex[5] = { 1,4,5 };
	pIndex[6] = { 0,3,7 };
	pIndex[7] = { 0,7,4 };

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CVentCube::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CVentCube::Free(void)
{
	CVIBuffer::Free();
}

CVentCube* Engine::CVentCube::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVentCube*	pInstance = new CVentCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CVentCube::Clone(void)
{
	return new CVentCube(*this);
}

