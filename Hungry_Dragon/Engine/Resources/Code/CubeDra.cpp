#include "CubeDra.h"

USING(Engine)

Engine::CCubeDra::CCubeDra(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CCubeDra::CCubeDra(const CCubeDra& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CCubeDra::~CCubeDra(void)
{

}

HRESULT Engine::CCubeDra::Ready_Buffer(void)
{
	float OneOverLoot2 = 1/sqrtf(2);

	//m_dwVtxCnt = 24;
	//m_dwTriCnt = 32;
	m_dwVtxCnt = 40;
	m_dwTriCnt = 22;
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
	pVertex[10].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[11].vPosition = _vec3(-0.267653f, 0.500000f, -1.000000f);
	pVertex[12].vPosition = _vec3(-0.267653f, 0.500000f, -1.000000f);
	pVertex[13].vPosition = _vec3(0.297691f, 0.500000f, -1.000000f);
	pVertex[14].vPosition = _vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[15].vPosition = _vec3(-0.267653f, -0.066036f, -1.000000f);
	pVertex[16].vPosition = _vec3(0.297691f, 0.500000f, -1.000000f);
	pVertex[17].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[18].vPosition = _vec3(0.700000f, -0.066036f, 1.000000f);
	pVertex[19].vPosition = _vec3(0.297691f, -0.066036f, -1.000000f);
	pVertex[20].vPosition = _vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[21].vPosition = _vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[22].vPosition = _vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[23].vPosition = _vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[24].vPosition = _vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[25].vPosition = _vec3(0.297691f, 0.500000f, -1.000000f);
	pVertex[26].vPosition = _vec3(-0.267653f, 0.500000f, -1.000000f);
	pVertex[27].vPosition = _vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[28].vPosition = _vec3(0.700000f, 0.500000f, 1.000000f);
	pVertex[29].vPosition = _vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[30].vPosition = _vec3(-0.700000f, 0.500000f, 1.000000f);
	pVertex[31].vPosition = _vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[32].vPosition = _vec3(-0.249538f, 0.500000f, 0.110244f);
	pVertex[33].vPosition = _vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[34].vPosition = _vec3(-0.249538f, 0.500000f, 0.823210f);
	pVertex[35].vPosition = _vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[36].vPosition = _vec3(0.000000f, 1.704008f, 1.737636f);
	pVertex[37].vPosition = _vec3(0.249538f, 0.500000f, 0.823210f);
	pVertex[38].vPosition = _vec3(0.249538f, 0.500000f, 0.110244f);
	pVertex[39].vPosition = _vec3(0.000000f, 1.704008f, 1.737636f);
	for (int i = 0; i < 40; ++i)
	{
		pVertex[i].dwColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
		pVertex[i].vPosition.z *= -1;
	}



	////惑何
	//pVertex[0].vPosition = _vec3(-1.f, 0.f, 0.f);
	//pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[1].vPosition = _vec3(-1.f, OneOverLoot2, OneOverLoot2);
	//pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[2].vPosition = _vec3(-1.f, OneOverLoot2 + 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[3].vPosition = _vec3(-1.f, 0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[4].vPosition = _vec3(1.f, 0.f, 0.f);
	//pVertex[4].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[5].vPosition = _vec3(1.f, OneOverLoot2, OneOverLoot2);
	//pVertex[5].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[6].vPosition = _vec3(1.f, OneOverLoot2 + 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[6].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[7].vPosition = _vec3(1.f, 0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[7].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	////窍何
	//pVertex[8].vPosition = _vec3(-1.f, 0.f, 0.f);
	//pVertex[8].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[9].vPosition = _vec3(-1.f, -OneOverLoot2, OneOverLoot2);
	//pVertex[9].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[10].vPosition = _vec3(-1.f, -OneOverLoot2 - 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[10].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[11].vPosition = _vec3(-1.f, -0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[11].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[12].vPosition = _vec3(1.f, 0.f, 0.f);
	//pVertex[12].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[13].vPosition = _vec3(1.f, -OneOverLoot2, OneOverLoot2);
	//pVertex[13].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[14].vPosition = _vec3(1.f, -OneOverLoot2 - 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[14].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[15].vPosition = _vec3(1.f, -0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[15].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	////个烹
	//pVertex[16].vPosition = _vec3(-1.f, 0.f, 0.f);
	//pVertex[16].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[17].vPosition = _vec3(-1.f, -OneOverLoot2, OneOverLoot2);
	//pVertex[17].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[18].vPosition = _vec3(-1.f, -OneOverLoot2 - 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[18].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[19].vPosition = _vec3(-1.f, -0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[19].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[20].vPosition = _vec3(1.f, 0.f, 0.f);
	//pVertex[20].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[21].vPosition = _vec3(1.f, -OneOverLoot2, OneOverLoot2);
	//pVertex[21].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[22].vPosition = _vec3(1.f, -OneOverLoot2 - 0.2f*OneOverLoot2, OneOverLoot2 - 0.2f*OneOverLoot2);
	//pVertex[22].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[23].vPosition = _vec3(1.f, -0.2f*OneOverLoot2, -0.2f*OneOverLoot2);
	//pVertex[23].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	
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

	pIndex[13]._0 = 24;
	pIndex[13]._1 = 25;
	pIndex[13]._2 = 28;

	pIndex[14]._0 = 24;
	pIndex[14]._1 = 28;
	pIndex[14]._2 = 27;

	pIndex[15]._0 = 29;
	pIndex[15]._1 = 30;
	pIndex[15]._2 = 26;

	pIndex[16]._0 = 29;
	pIndex[16]._1 = 26;
	pIndex[16]._2 = 23;

	pIndex[17]._0 = 27;
	pIndex[17]._1 = 28;
	pIndex[17]._2 = 30;

	pIndex[18]._0 = 27;
	pIndex[18]._1 = 30;
	pIndex[18]._2 = 29;

	pIndex[19]._0 = 31;
	pIndex[19]._1 = 33;
	pIndex[19]._2 = 32;

	pIndex[20]._0 = 34;
	pIndex[20]._1 = 36;
	pIndex[20]._2 = 35;

	pIndex[21]._0 = 37;
	pIndex[21]._1 = 39;
	pIndex[21]._2 = 38;


	//pIndex[0]._0 = 0;
	//pIndex[0]._1 = 1;
	//pIndex[0]._2 = 3;

	//pIndex[1]._0 = 3;
	//pIndex[1]._1 = 1;
	//pIndex[1]._2 = 2;

	//pIndex[2]._0 = 0;
	//pIndex[2]._1 = 4;
	//pIndex[2]._2 = 1;

	//pIndex[3]._0 = 1;
	//pIndex[3]._1 = 4;
	//pIndex[3]._2 = 5;

	//pIndex[4]._0 = 7;
	//pIndex[4]._1 = 6;
	//pIndex[4]._2 = 4;

	//pIndex[5]._0 = 4;
	//pIndex[5]._1 = 6;
	//pIndex[5]._2 = 5;

	//pIndex[6]._0 = 3;
	//pIndex[6]._1 = 2;
	//pIndex[6]._2 = 7;

	//pIndex[7]._0 = 7;
	//pIndex[7]._1 = 2;
	//pIndex[7]._2 = 6;

	//pIndex[8]._0 = 1;
	//pIndex[8]._1 = 5;
	//pIndex[8]._2 = 2;

	//pIndex[9]._0 = 2;
	//pIndex[9]._1 = 5;
	//pIndex[9]._2 = 6;

	////窍窜何
	//pIndex[10]._0 = 0+8;
	//pIndex[10]._2 = 1+8;
	//pIndex[10]._1 = 3+8;

	//pIndex[11]._0 = 3+8;
	//pIndex[11]._2 = 1+8;
	//pIndex[11]._1 = 2+8;

	//pIndex[12]._0 = 0+8;
	//pIndex[12]._2 = 4+8;
	//pIndex[12]._1 = 1+8;
	//	   		
	//pIndex[13]._0 = 1+8;
	//pIndex[13]._2 = 4+8;
	//pIndex[13]._1 = 5+8;

	//pIndex[14]._0 = 7+8;
	//pIndex[14]._2 = 6+8;
	//pIndex[14]._1 = 4+8;

	//pIndex[15]._0 = 4+8;
	//pIndex[15]._2 = 6+8;
	//pIndex[15]._1 = 5+8;
	//				
	//pIndex[16]._0 = 3+8;
	//pIndex[16]._2 = 2+8;
	//pIndex[16]._1 = 7+8;
	//				
	//pIndex[17]._0 = 7+8;
	//pIndex[17]._2 = 2+8;
	//pIndex[17]._1 = 6+8;
	//				
	//pIndex[18]._0 = 1+8;
	//pIndex[18]._2 = 5+8;
	//pIndex[18]._1 = 2+8;
	//				
	//pIndex[19]._0 = 2+8;
	//pIndex[19]._2 = 5+8;
	//pIndex[19]._1 = 6+8;

	////个烹
	//pIndex[20]._0 = 0+16;
	//pIndex[20]._1 = 1+16;
	//pIndex[20]._2 = 3+16;
	//				
	//pIndex[21]._0 = 3+16;
	//pIndex[21]._1 = 1+16;
	//pIndex[21]._2 = 2+16;
	//				
	//pIndex[22]._0 = 0+16;
	//pIndex[22]._1 = 4+16;
	//pIndex[22]._2 = 1+16;
	//				 
	//pIndex[23]._0 = 1+16;
	//pIndex[23]._1 = 4+16;
	//pIndex[23]._2 = 5+16;
	//				
	//pIndex[24]._0 = 7+16;
	//pIndex[24]._1 = 6+16;
	//pIndex[24]._2 = 4+16;
	//				
	//pIndex[25]._0 = 4+16;
	//pIndex[25]._1 = 6+16;
	//pIndex[25]._2 = 5+16;
	//				
	//pIndex[26]._0 = 3+16;
	//pIndex[26]._1 = 2+16;
	//pIndex[26]._2 = 7+16;
	//			
	//pIndex[27]._0 = 7+16;
	//pIndex[27]._1 = 2+16;
	//pIndex[27]._2 = 6+16;
	//				
	//pIndex[28]._0 = 1+16;
	//pIndex[28]._1 = 5+16;
	//pIndex[28]._2 = 2+16;
	//			
	//pIndex[29]._0 = 2+16;
	//pIndex[29]._1 = 5+16;
	//pIndex[29]._2 = 6+16;

	//pIndex[30]._0 = 0 + 16;
	//pIndex[30]._1 = 3 + 16;
	//pIndex[30]._2 = 4 + 16;

	//pIndex[31]._0 = 4 + 16;
	//pIndex[31]._1 = 3 + 16;
	//pIndex[31]._2 = 7 + 16;

	return S_OK;
}

void Engine::CCubeDra::Render_Buffer(void)
{

	//m_fAngle += m_fAngleSpeed;
	//if (m_fAngle > Pi*0.25f || m_fAngle < 0.f)
	//	m_fAngleSpeed *= -1.f;

	//m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	//float fCos1 = cosf(m_fAngle);
	//float fSin1 = sinf(m_fAngle);

	//float fCos2 = cosf(m_fAngle + Pi*0.5f);
	//float fSin2 = sinf(m_fAngle + Pi*0.5f);
	//pVertex[0].vPosition = _vec3(-m_fMouse_Width, 0.f, 0.f);
	//pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[1].vPosition = _vec3(-m_fMouse_Width, fSin1, fCos1);
	//pVertex[1].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[2].vPosition = _vec3(-m_fMouse_Width, fSin1 + m_fMouse_Height*fSin2, fCos1 + m_fMouse_Height*fCos2);
	//pVertex[2].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[3].vPosition = _vec3(-m_fMouse_Width, m_fMouse_Height*fSin2, m_fMouse_Height*fCos2);
	//pVertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[4].vPosition = _vec3(m_fMouse_Width, 0.f, 0.f);
	//pVertex[4].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[5].vPosition = _vec3(m_fMouse_Width, fSin1, fCos1);
	//pVertex[5].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	//pVertex[6].vPosition = _vec3(m_fMouse_Width, fSin1 + m_fMouse_Height*fSin2, fCos1 + m_fMouse_Height*fCos2);
	//pVertex[6].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	//pVertex[7].vPosition = _vec3(m_fMouse_Width, m_fMouse_Height*fSin2, m_fMouse_Height*fCos2);
	//pVertex[7].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	////窍何
	//pVertex[8].vPosition = _vec3(-m_fMouse_Width, 0.f, 0.f);
	//pVertex[8].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[9].vPosition = _vec3(-m_fMouse_Width, -fSin1, fCos1);
	//pVertex[9].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[10].vPosition = _vec3(-m_fMouse_Width, -fSin1 - m_fMouse_Height*fSin2, fCos1 + m_fMouse_Height*fCos2);
	//pVertex[10].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
 //
	//pVertex[11].vPosition = _vec3(-m_fMouse_Width, -m_fMouse_Height*fSin2, m_fMouse_Height*fCos2);
	//pVertex[11].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[12].vPosition = _vec3(m_fMouse_Width, 0.f, 0.f);
	//pVertex[12].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[13].vPosition = _vec3(m_fMouse_Width, -fSin1, fCos1);
	//pVertex[13].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[14].vPosition = _vec3(m_fMouse_Width, -fSin1 - m_fMouse_Height*fSin2, fCos1 + m_fMouse_Height*fCos2);
	//pVertex[14].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[15].vPosition = _vec3(m_fMouse_Width, -m_fMouse_Height*fSin2, m_fMouse_Height*fCos2);
	//pVertex[15].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	////个烹
	//pVertex[16].vPosition = _vec3(-m_fMouse_Width, -0.35f, -3.f);
	//pVertex[16].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[17].vPosition = _vec3(-m_fMouse_Width, -0.35f, 0.f);
	//pVertex[17].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[18].vPosition = _vec3(-m_fMouse_Width, 0.35f, 0.f);
	//pVertex[18].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[19].vPosition = _vec3(-m_fMouse_Width, 0.35f, -3.f);
	//pVertex[19].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[20].vPosition = _vec3(m_fMouse_Width, -0.35f, -3.f);
	//pVertex[20].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[21].vPosition = _vec3(m_fMouse_Width, -0.35f, 0.f);
	//pVertex[21].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	//
	//pVertex[22].vPosition = _vec3(m_fMouse_Width, 0.35f, 0.f);
	//pVertex[22].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	//pVertex[23].vPosition = _vec3(m_fMouse_Width, 0.35f, -3.f);
	//pVertex[23].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	m_pVB->Unlock();

	CVIBuffer::Render_Buffer();
}

void Engine::CCubeDra::Free(void)
{
	CVIBuffer::Free();
}

CCubeDra* Engine::CCubeDra::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeDra*	pInstance = new CCubeDra(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CCubeDra::Clone(void)
{
	return new CCubeDra(*this);
}

