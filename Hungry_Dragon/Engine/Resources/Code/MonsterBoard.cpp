#include "MonsterBoard.h"

USING(Engine)

Engine::CMonsterBoard::CMonsterBoard(LPDIRECT3DDEVICE9 pGraphicDev, _float _iAnimUCnt, _float _iAnimVCnt)
	: CVIBuffer(pGraphicDev),
	m_iAnimUCnt((_int)_iAnimUCnt),
	m_iAnimVCnt((_int)_iAnimVCnt)
{

}

Engine::CMonsterBoard::CMonsterBoard(const CMonsterBoard& rhs)
	: CVIBuffer(rhs),
	 m_iAnimUCnt(rhs.m_iAnimUCnt),
	 m_iAnimVCnt(rhs.m_iAnimVCnt),
	 m_fTexU(rhs.m_fTexU),
	 m_fTexV(rhs.m_fTexV)
{
	
}

Engine::CMonsterBoard::~CMonsterBoard(void)
{

}

HRESULT Engine::CMonsterBoard::Ready_Buffer(void)
{
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2;
	m_fTexU = 1.f / m_iAnimUCnt;
	m_fTexV = 1.f / m_iAnimVCnt;

	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	//pVertex[0] = VTXTEX(-1.0f, -1.0f, -1.0f,     0.0f, 0.0f, -1.0f         , m_fTexU * (m_fFrameUCnt - 1 ) , m_fTexV * (m_fFrameVCnt - 1));
	//pVertex[1] = VTXTEX(-1.0f, 1.0f, -1.0f ,     0.0f, 0.0f, -1.0f         , m_fTexU * (m_fFrameUCnt - 1 ) , m_fTexV *  m_fFrameVCnt);
	//pVertex[2] = VTXTEX( 1.0f, 1.0f, -1.0f ,     0.0f, 0.0f, -1.0f         , m_fTexU * m_fFrameUCnt        , m_fTexV *  m_fFrameVCnt);
	//pVertex[3] = VTXTEX( 1.0f, -1.0f, -1.0f,     0.0f, 0.0f, -1.0f         , m_fTexU * m_fFrameUCnt        , m_fTexV * (m_fFrameVCnt - 1));

	pVertex[0] = VTXTEX(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.f, 1.f);
	pVertex[1] = VTXTEX(-1.0f, 1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  1.f, 0.f);
	pVertex[2] = VTXTEX(1.0f, 1.0f,   0.0f, 0.0f, 0.0f, -1.0f,   0.f, 0.f);
	pVertex[3] = VTXTEX(1.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.f, 1.f);
									  


	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}


void Engine::CMonsterBoard::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CMonsterBoard::Free(void)
{
	CVIBuffer::Free();
}

CMonsterBoard* Engine::CMonsterBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev , _float _fU , _float _fV)
{
	CMonsterBoard*	pInstance = new CMonsterBoard(pGraphicDev , _fU , _fV);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CMonsterBoard::Clone(void)
{
	return new CMonsterBoard(*this);
}

