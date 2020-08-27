#include "DragonBody.h"

USING(Engine)

Engine::CDragonBody::CDragonBody(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CDragonBody::CDragonBody(const CDragonBody& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CDragonBody::~CDragonBody(void)
{

}

HRESULT Engine::CDragonBody::Ready_Buffer(void)
{
	m_dwVtxCnt = 76;
	m_dwTriCnt = 40;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = _vec3(-0.153001f, 0.700000f, 0.336590f);
	pVertex[1].vPosition = _vec3(0.127332f, 0.700000f, 0.336590f);
	pVertex[2].vPosition = _vec3(-0.012835f, 1.271080f, 0.578706f);
	pVertex[3].vPosition = _vec3(-0.850000f, -0.700000f, -0.467436f);
	pVertex[4].vPosition = _vec3(-0.850000f, -0.700000f, 0.548020f);
	pVertex[5].vPosition = _vec3(-0.850000f, 0.700000f, 0.548020f);
	pVertex[6].vPosition = _vec3(-0.850000f, 0.700000f, -0.467436f);
	pVertex[7].vPosition = _vec3(-0.397320f, 0.327205f, -1.000000f);
	pVertex[8].vPosition = _vec3(0.397320f, 0.327205f, -1.000000f);
	pVertex[9].vPosition = _vec3(0.397320f, -0.327205f, -1.000000f);
	pVertex[10].vPosition =	_vec3(-0.397320f, -0.327205f, -1.000000f);
	pVertex[11].vPosition =	_vec3(0.465817f, 0.383614f, 1.000000f);
	pVertex[12].vPosition =	_vec3(-0.465817f, 0.383614f, 1.000000f);
	pVertex[13].vPosition =	_vec3(-0.465817f, -0.383614f, 1.000000f);
	pVertex[14].vPosition =	_vec3(0.465817f, -0.383614f, 1.000000f);
	pVertex[15].vPosition =	_vec3(-0.397320f, 0.327205f, -1.000000f);
	pVertex[16].vPosition =	_vec3(-0.397320f, -0.327205f, -1.000000f);
	pVertex[17].vPosition =	_vec3(-0.850000f, -0.700000f, -0.467436f);
	pVertex[18].vPosition =	_vec3(-0.850000f, 0.700000f, -0.467436f);
	pVertex[19].vPosition =	_vec3(0.397320f, 0.327205f, -1.000000f);
	pVertex[20].vPosition =	_vec3(-0.397320f, 0.327205f, -1.000000f);
	pVertex[21].vPosition =	_vec3(-0.850000f, 0.700000f, -0.467436f);
	pVertex[22].vPosition =	_vec3(0.850000f, 0.700000f, -0.467436f);
	pVertex[23].vPosition =	_vec3(-0.397320f, -0.327205f, -1.000000f);
	pVertex[24].vPosition = _vec3(0.397320f, -0.327205f, -1.000000f);
	pVertex[25].vPosition = _vec3(0.850000f, -0.700000f, -0.467436f);
	pVertex[26].vPosition = _vec3(-0.850000f, -0.700000f, -0.467436f);
	pVertex[27].vPosition = _vec3(0.397320f, -0.327205f, -1.000000f);
	pVertex[28].vPosition = _vec3(0.397320f, 0.327205f, -1.000000f);
	pVertex[29].vPosition = _vec3(0.850000f, 0.700000f, -0.467436f);
	pVertex[30].vPosition = _vec3(0.850000f, -0.700000f, -0.467436f);
	pVertex[31].vPosition = _vec3(0.850000f, -0.700000f, -0.467436f);
	pVertex[32].vPosition = _vec3(0.850000f, -0.700000f, 0.548020f);
	pVertex[33].vPosition = _vec3(-0.850000f, -0.700000f, 0.548020f);
	pVertex[34].vPosition = _vec3(-0.850000f, -0.700000f, -0.467436f);
	pVertex[35].vPosition = _vec3(0.465817f, -0.383614f, 1.000000f);
	pVertex[36].vPosition = _vec3(-0.465817f, -0.383614f, 1.000000f);
	pVertex[37].vPosition = _vec3(-0.850000f, -0.700000f, 0.548020f);
	pVertex[38].vPosition = _vec3(0.850000f, -0.700000f, 0.548020f);
	pVertex[39].vPosition = _vec3(0.465817f, 0.383614f, 1.000000f);
	pVertex[40].vPosition = _vec3(0.465817f, -0.383614f, 1.000000f);
	pVertex[41].vPosition = _vec3(0.850000f, -0.700000f, 0.548020f);
	pVertex[42].vPosition = _vec3(0.850000f, 0.700000f, 0.548020f);
	pVertex[43].vPosition = _vec3(-0.465817f, -0.383614f, 1.000000f);
	pVertex[44].vPosition = _vec3(-0.465817f, 0.383614f, 1.000000f);
	pVertex[45].vPosition = _vec3(-0.850000f, 0.700000f, 0.548020f);
	pVertex[46].vPosition = _vec3(-0.850000f, -0.700000f, 0.548020f);
	pVertex[47].vPosition = _vec3(-0.465817f, 0.383614f, 1.000000f);
	pVertex[48].vPosition = _vec3(0.465817f, 0.383614f, 1.000000f);
	pVertex[49].vPosition = _vec3(0.850000f, 0.700000f, 0.548020f);
	pVertex[50].vPosition = _vec3(-0.850000f, 0.700000f, 0.548020f);
	pVertex[51].vPosition = _vec3(0.850000f, 0.700000f, -0.467436f);
	pVertex[52].vPosition = _vec3(0.850000f, 0.700000f, 0.548020f);
	pVertex[53].vPosition = _vec3(0.850000f, -0.700000f, 0.548020f);
	pVertex[54].vPosition = _vec3(0.850000f, -0.700000f, -0.467436f);
	pVertex[55].vPosition = _vec3(-0.153001f, 0.700000f, -0.278713f);
	pVertex[56].vPosition = _vec3(0.127332f, 0.700000f, -0.278713f);
	pVertex[57].vPosition = _vec3(0.850000f, 0.700000f, -0.467436f);
	pVertex[58].vPosition = _vec3(-0.850000f, 0.700000f, -0.467436f);
	pVertex[59].vPosition = _vec3(0.127332f, 0.700000f, 0.336590f);
	pVertex[60].vPosition = _vec3(-0.153001f, 0.700000f, 0.336590f);
	pVertex[61].vPosition = _vec3(-0.850000f, 0.700000f, 0.548020f);
	pVertex[62].vPosition = _vec3(0.850000f, 0.700000f, 0.548020f);
	pVertex[63].vPosition = _vec3(-0.153001f, 0.700000f, -0.278713f);
	pVertex[64].vPosition = _vec3(-0.153001f, 0.700000f, 0.336590f);
	pVertex[65].vPosition = _vec3(-0.153001f, 0.700000f, 0.336590f);
	pVertex[66].vPosition = _vec3(-0.153001f, 0.700000f, -0.278713f);
	pVertex[67].vPosition = _vec3(0.127332f, 0.700000f, 0.336590f);
	pVertex[68].vPosition = _vec3(0.127332f, 0.700000f, -0.278713f);
	pVertex[69].vPosition = _vec3(-0.012835f, 1.271080f, 0.578706f);
	pVertex[70].vPosition = _vec3(0.127332f, 0.700000f, -0.278713f);
	pVertex[71].vPosition = _vec3(-0.153001f, 0.700000f, -0.278713f);
	pVertex[72].vPosition = _vec3(-0.012835f, 1.271080f, 0.578706f);
	pVertex[73].vPosition = _vec3(-0.153001f, 0.700000f, -0.278713f);
	pVertex[74].vPosition = _vec3(-0.153001f, 0.700000f, 0.336590f);
	pVertex[75].vPosition = _vec3(-0.012835f, 1.271080f, 0.578706f);

	for (int i = 0; i < 76; ++i)
	{
		if(i & 0x0001)
			pVertex[i].dwColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
		else
			pVertex[i].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVertex[i].vPosition.z *= -1;
	}

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 2;
	pIndex[0]._2 = 1;

	for (int i = 0; i < 15; ++i)
	{
		pIndex[i * 2 + 1]._0 = 3 + 4 * i;
		pIndex[i * 2 + 1]._1 = 6 + 4 * i;
		pIndex[i * 2 + 1]._2 = 5 + 4 * i;

		pIndex[i * 2 + 2]._0 = 3 + 4 * i;
		pIndex[i * 2 + 2]._1 = 5 + 4 * i;
		pIndex[i * 2 + 2]._2 = 4 + 4 * i;
	}

	pIndex[31]._0 = 56;
	pIndex[31]._1 = 57;
	pIndex[31]._2 = 62;
		   
	pIndex[32]._0 = 56;
	pIndex[32]._1 = 62;
	pIndex[32]._2 = 59;
		   
	pIndex[33]._0 = 60;
	pIndex[33]._1 = 61;
	pIndex[33]._2 = 58;
		   
	pIndex[34]._0 = 60;
	pIndex[34]._1 = 58;
	pIndex[34]._2 = 55;
		   
	pIndex[35]._0 = 63;
	pIndex[35]._1 = 66;
	pIndex[35]._2 = 65;
		   
	pIndex[36]._0 = 63;
	pIndex[36]._1 = 65;
	pIndex[36]._2 = 64;
		   
	pIndex[37]._0 = 67;
	pIndex[37]._1 = 69;
	pIndex[37]._2 = 68;
		   
	pIndex[38]._0 = 70;
	pIndex[38]._1 = 72;
	pIndex[38]._2 = 71;
		   
	pIndex[39]._0 = 73;
	pIndex[39]._1 = 75;
	pIndex[39]._2 = 74;

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CDragonBody::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CDragonBody::Free(void)
{
	CVIBuffer::Free();
}

CDragonBody* Engine::CDragonBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonBody*	pInstance = new CDragonBody(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CDragonBody::Clone(void)
{
	return new CDragonBody(*this);
}

