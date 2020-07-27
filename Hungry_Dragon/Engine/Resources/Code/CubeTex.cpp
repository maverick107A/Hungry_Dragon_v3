#include "CubeTex.h"

USING(Engine)

CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}


CCubeTex::CCubeTex(const CCubeTex & rhs)
	: CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex(void)
{
}

HRESULT CCubeTex::Ready_Buffer(void)
{

	// 인덱스 버퍼 및 버텍스 버퍼 초기화
	m_dwVtxCnt = 24;
	m_dwTriCnt = 12;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);


	pVertex[0] = VTXTEX(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[1] = VTXTEX(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[2] = VTXTEX(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	pVertex[3] = VTXTEX(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[4] = VTXTEX(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	pVertex[5] = VTXTEX(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	pVertex[6] = VTXTEX(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[7] = VTXTEX(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	pVertex[8] = VTXTEX(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pVertex[9] = VTXTEX(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[10] = VTXTEX(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[11] = VTXTEX(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	pVertex[12] = VTXTEX(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	pVertex[13] = VTXTEX(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[14] = VTXTEX(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[15] = VTXTEX(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	pVertex[16] = VTXTEX(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pVertex[17] = VTXTEX(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pVertex[18] = VTXTEX(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[19] = VTXTEX(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	pVertex[20] = VTXTEX(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pVertex[21] = VTXTEX(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pVertex[22] = VTXTEX(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[23] = VTXTEX(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	m_pVB->Unlock();
	INDEX16*		pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;


	pIndex[2]._0 = 4;
	pIndex[2]._1 = 5;
	pIndex[2]._2 = 6;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 6;
	pIndex[3]._2 = 7;


	pIndex[4]._0 = 8;
	pIndex[4]._1 = 9;
	pIndex[4]._2 = 10;

	pIndex[5]._0 = 8;
	pIndex[5]._1 = 10;
	pIndex[5]._2 = 11;

	pIndex[6]._0 = 12;
	pIndex[6]._1 = 13;
	pIndex[6]._2 = 14;


	pIndex[7]._0 = 12;
	pIndex[7]._1 = 14;
	pIndex[7]._2 = 15;

	pIndex[8]._0 = 16;
	pIndex[8]._1 = 17;
	pIndex[8]._2 = 18;


	pIndex[9]._0 = 16;
	pIndex[9]._1 = 18;
	pIndex[9]._2 = 19;

	pIndex[10]._0 = 20;
	pIndex[10]._1 = 21;
	pIndex[10]._2 = 22;


	pIndex[11]._0 = 20;
	pIndex[11]._1 = 22;
	pIndex[11]._2 = 23;





	m_pIB->Unlock();
	return S_OK;
}

void CCubeTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CCubeTex * CCubeTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeTex*	pInstance = new CCubeTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CCubeTex::Clone(void)
{
	return new CCubeTex(*this);
}

void CCubeTex::Free(void)
{
	CVIBuffer::Free();
}
