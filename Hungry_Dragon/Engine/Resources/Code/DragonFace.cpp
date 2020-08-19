#include "DragonFace.h"

USING(Engine)

Engine::CDragonFace::CDragonFace(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CDragonFace::CDragonFace(const CDragonFace& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CDragonFace::~CDragonFace(void)
{

}

HRESULT Engine::CDragonFace::Ready_Buffer(void)
{
	float OneOverLoot2 = 1/sqrtf(2);

	//m_dwVtxCnt = 24;
	//m_dwTriCnt = 32;
	m_dwVtxCnt = 48;
	m_dwTriCnt = 23;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	//VTXCOL*		pVertex = nullptr;


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
	pVertex[10].vPosition =_vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[11].vPosition =_vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[12].vPosition =_vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[13].vPosition =_vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[14].vPosition =_vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[15].vPosition =_vec3(-0.267653f, -0.066036f, -1.000000f);
	pVertex[16].vPosition =_vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[17].vPosition =_vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[18].vPosition =_vec3(0.700000f, -0.066036f, 1.000000f);
	pVertex[19].vPosition =_vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[20].vPosition =_vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[21].vPosition =_vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[22].vPosition =_vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[23].vPosition =_vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[24].vPosition =_vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[25].vPosition =_vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[26].vPosition =_vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[27].vPosition =_vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[28].vPosition =_vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[29].vPosition =_vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[30].vPosition =_vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[31].vPosition =_vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[32].vPosition =_vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[33].vPosition =_vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[34].vPosition =_vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[35].vPosition =_vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[36].vPosition =_vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[37].vPosition =_vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[38].vPosition =_vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[39].vPosition =_vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[40].vPosition = _vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[41].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[42].vPosition = _vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[43].vPosition = _vec3(-0.267653f, 0.116341f, -1.000000f);
	pVertex[44].vPosition = _vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[45].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[46].vPosition = _vec3(0.297691f, 0.116341f, -1.000000f);
	pVertex[47].vPosition = _vec3(0.249538f, 0.500000f, 0.110244f);

	for (int i = 0; i < 48; ++i)
	{
		pVertex[i].dwColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
		pVertex[i].vPosition.z *= -1;
	}

	for (int i = 0; i < 23; ++i)
	{
		VTXCOL tempVertex;
		tempVertex.vPosition = pVertex[i].vPosition;
		tempVertex.dwColor = pVertex[i].dwColor;
		vertexList.emplace_back(tempVertex);
	}

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 3;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 1;

	pIndex[2]._0 = 4;
	pIndex[2]._1 = 7;
	pIndex[2]._2 = 6;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 6;
	pIndex[3]._2 = 5;

	pIndex[4]._0 = 8;
	pIndex[4]._1 = 11;
	pIndex[4]._2 = 10;

	pIndex[5]._0 = 8;
	pIndex[5]._1 = 10;
	pIndex[5]._2 = 9;

	pIndex[6]._0 = 12;
	pIndex[6]._1 = 15;
	pIndex[6]._2 = 14;

	pIndex[7]._0 = 12;
	pIndex[7]._1 = 14;
	pIndex[7]._2 = 13;

	pIndex[8]._0 = 16;
	pIndex[8]._1 = 19;
	pIndex[8]._2 = 18;

	pIndex[9]._0 = 16;
	pIndex[9]._1 = 18;
	pIndex[9]._2 = 17;

	pIndex[10]._0 = 20;
	pIndex[10]._1 = 22;
	pIndex[10]._2 = 21;

	pIndex[11]._0 = 23;
	pIndex[11]._1 = 26;
	pIndex[11]._2 = 25;

	pIndex[12]._0 = 23;
	pIndex[12]._1 = 25;
	pIndex[12]._2 = 24;

	pIndex[13]._0 = 27;
	pIndex[13]._1 = 30;
	pIndex[13]._2 = 29;

	pIndex[14]._0 = 27;
	pIndex[14]._1 = 29;
	pIndex[14]._2 = 28;

	pIndex[15]._0 = 31;
	pIndex[15]._1 = 33;
	pIndex[15]._2 = 32;

	pIndex[16]._0 = 34;
	pIndex[16]._1 = 36;
	pIndex[16]._2 = 35;

	pIndex[17]._0 = 37;
	pIndex[17]._1 = 39;
	pIndex[17]._2 = 38;

	pIndex[18]._0 = 28;
	pIndex[18]._1 = 29;
	pIndex[18]._2 = 40;

	pIndex[19]._0 = 41;
	pIndex[19]._1 = 43;
	pIndex[19]._2 = 42;

	pIndex[20]._0 = 44;
	pIndex[20]._1 = 30;
	pIndex[20]._2 = 27;

	pIndex[22]._0 = 45;
	pIndex[22]._1 = 47;
	pIndex[22]._2 = 46;

	for (int i = 0; i < 23; ++i)
	{
		indexList.emplace_back(pIndex[i]);
	}


	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, "../DragonFace.dat", "wb");

	if (0 == err)
	{
		int vertexSize = (int)vertexList.size();
		fwrite(&vertexSize, sizeof(int), 1, fp);

		for (list<VTXCOL>::iterator iter = vertexList.begin(); iter != vertexList.end(); ++iter)
		{
			VTXCOL tempVtx = (*iter);
			fwrite(&tempVtx, sizeof(VTXCOL), 1, fp);
		}

		int indexSize = (int)indexList.size();
		fwrite(&indexSize, sizeof(int), 1, fp);

		for (list<INDEX16>::iterator iter = indexList.begin(); iter != indexList.end(); ++iter)
		{
			INDEX16 tempIdx = (*iter);
			fwrite(&tempIdx, sizeof(INDEX16), 1, fp);
		}

		fclose(fp);
	}
	return S_OK;
}

void Engine::CDragonFace::Render_Buffer(void)
{
	m_pVB->Unlock();

	CVIBuffer::Render_Buffer();
}

void Engine::CDragonFace::Free(void)
{
	CVIBuffer::Free();
}

CDragonFace* Engine::CDragonFace::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonFace*	pInstance = new CDragonFace(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CDragonFace::Clone(void)
{
	return new CDragonFace(*this);
}

