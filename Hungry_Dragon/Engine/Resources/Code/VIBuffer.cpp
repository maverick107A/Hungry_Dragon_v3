#include "VIBuffer.h"

USING(Engine)

Engine::CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
{

}

Engine::CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CResources(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

Engine::CVIBuffer::~CVIBuffer(void)
{

}

HRESULT Engine::CVIBuffer::Ready_Buffer(void)
{

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, // ���ؽ��� ���� ũ��(���ؽ� ����ü�� ũ�� * ������ ����)
															0,	// ���۸� � ���� ����� ���ΰ�(0�� ���� ���� ���۸� D3DUSAGE_DYNAMIC ���� ���۸� �����)
															m_dwFVF,
															D3DPOOL_MANAGED, 
															&m_pVB,
															nullptr), 
															E_FAIL);

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 
															0,	// ���۸� � ���� ����� ���ΰ�(0�� ���� ���� ���۸� D3DUSAGE_DYNAMIC ���� ���۸� �����)
															m_IdxFmt,
															D3DPOOL_MANAGED,
															&m_pIB,
															nullptr),
															E_FAIL);


	return S_OK;
}

void Engine::CVIBuffer::Render_Buffer(void)
{
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pGraphicDev->SetFVF(m_dwFVF);
	m_pGraphicDev->SetIndices(m_pIB);

	// �׸��� �Լ�
	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

void Engine::CVIBuffer::Free(void)
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	CResources::Free();
}

