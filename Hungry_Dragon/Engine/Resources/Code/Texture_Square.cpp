#include "Texture_Square.h"

USING(Engine)

CTexture_Square::CTexture_Square(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CTexture_Square::CTexture_Square(const CTexture_Square & rhs) 
	:CVIBuffer(rhs)
{
	m_pColorEntry = rhs.m_pColorEntry;
}

CTexture_Square::~CTexture_Square(void) {
}

HRESULT CTexture_Square::Ready_Buffer(void) {
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2;
	m_dwVtxSize = sizeof(VTXBOARD);
	m_dwFVF = FVF_BOARD;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXBOARD*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = _vec3(-0.5f, 0.5f, 0.f);
	pVertex[0].vTexUV = _vec2(0.f, 0.f);

	pVertex[1].vPosition = _vec3(0.5f, 0.5f, 0.f);
	pVertex[1].vTexUV = _vec2(1.f, 0.f);

	pVertex[2].vPosition = _vec3(0.5f, -0.5f, 0.f);
	pVertex[2].vTexUV = _vec2(1.f, 1.f);

	pVertex[3].vPosition = _vec3(-0.5f, -0.5f, 0.f);
	pVertex[3].vTexUV = _vec2(0.f, 1.f);

	pVertex[0].dwColor = 0xffffffff;
	pVertex[1].dwColor = 0xffffffff;
	pVertex[2].dwColor = 0xffffffff;
	pVertex[3].dwColor = 0xffffffff;
	m_pColorEntry = &pVertex[0].dwColor;

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

void CTexture_Square::Render_Buffer(void) {
	CVIBuffer::Render_Buffer();
}

void CTexture_Square::Set_VertexColor(DWORD _dwColor)
{
	VTXBOARD*		pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	memcpy(m_pColorEntry, &_dwColor, sizeof(DWORD));
	memcpy(&pVertex[0].dwColor, &_dwColor, sizeof(DWORD));
	m_pColorEntry = &pVertex[0].dwColor;
	m_pVB->Unlock();
}

void CTexture_Square::Free(void) {
	CVIBuffer::Free();
}

CTexture_Square * CTexture_Square::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CTexture_Square*	pInstance = new CTexture_Square(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CTexture_Square::Clone(void) {
	return new CTexture_Square(*this);
}

