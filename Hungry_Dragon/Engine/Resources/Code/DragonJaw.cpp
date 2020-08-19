#include "DragonJaw.h"

USING(Engine)

Engine::CDragonJaw::CDragonJaw(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CDragonJaw::CDragonJaw(const CDragonJaw& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CDragonJaw::~CDragonJaw(void)
{

}

HRESULT Engine::CDragonJaw::Ready_Buffer(void)
{
	float OneOverLoot2 = 1/sqrtf(2);

	m_dwVtxCnt = 24;
	m_dwTriCnt = 12;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[1].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[2].vPosition = _vec3(-0.700000f, -0.066036f, 1.000000f);
	pVertex[3].vPosition = _vec3(0.700000f, -0.066036f, 1.000000f);
	pVertex[4].vPosition = _vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[5].vPosition = _vec3(0.700000f, -0.066036f, 1.000000f);
	pVertex[6].vPosition = _vec3(-0.700000f, -0.066036f, 1.000000f);
	pVertex[7].vPosition = _vec3(-0.267653f, -0.066036f, -1.000000f);
	pVertex[8].vPosition = _vec3(-0.267653f, -0.066036f, -1.000000f);
	pVertex[9].vPosition = _vec3(-0.700000f, -0.066036f, 1.000000f);
	pVertex[10].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[11].vPosition = _vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[12].vPosition = _vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[13].vPosition = _vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[14].vPosition = _vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[15].vPosition = _vec3(-0.267653f, -0.066036f, -1.000000f);
	pVertex[16].vPosition = _vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[17].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[18].vPosition = _vec3(0.700000f, -0.066036f, 1.000000f);
	pVertex[19].vPosition = _vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[20].vPosition = _vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[21].vPosition = _vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[22].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[23].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);

	for (int i = 0; i < 24; ++i)
	{
		pVertex[i].dwColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
		pVertex[i].vPosition.z *= -1;
		pVertex[i].vPosition.y *= -1;
	}

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

void Engine::CDragonJaw::Render_Buffer(void)
{
	m_pVB->Unlock();

	CVIBuffer::Render_Buffer();
}

void Engine::CDragonJaw::Free(void)
{
	CVIBuffer::Free();
}

CDragonJaw* Engine::CDragonJaw::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonJaw*	pInstance = new CDragonJaw(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CDragonJaw::Clone(void)
{
	return new CDragonJaw(*this);
}

