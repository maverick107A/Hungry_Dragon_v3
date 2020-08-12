#include "VICustom.h"

USING(Engine)

CVICustom::CVICustom(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CVICustom::CVICustom(const CVICustom& rhs)
	:CVIBuffer(rhs)
{
	auto& iter_vtx=rhs.m_listVertex.begin();
	for (; iter_vtx != rhs.m_listVertex.end(); ++iter_vtx)
	{
		m_listVertex.emplace_back((*iter_vtx));
	}

	auto& iter_idx = rhs.m_listIndex.begin();
	for (; iter_idx != rhs.m_listIndex.end(); ++iter_idx)
	{
		m_listIndex.emplace_back((*iter_idx));
	}

}

CVICustom::~CVICustom(void)
{
}

HRESULT CVICustom::Ready_Buffer(void)
{
	return S_OK;
}

HRESULT CVICustom::Ready_Buffer(LPCTSTR _address)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	Load_VI(_address);

	m_dwVtxCnt = (int)m_listVertex.size();
	m_dwTriCnt = (int)m_listIndex.size();

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	list<VTXCOL>::iterator iter_vtx = m_listVertex.begin();
	for (size_t i = 0; i < m_listVertex.size(); ++i, ++iter_vtx)
	{
		pVertex[i] = (*iter_vtx);
	}

	m_pVB->Unlock();

	INDEX16* pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	list<INDEX16>::iterator iter_idx = m_listIndex.begin();
	for (size_t i = 0; i < m_listIndex.size(); ++i, ++iter_idx)
	{
		pIndex[i] = (*iter_idx);
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVICustom::Ready_Buffer(list<VTXCOL> _listVertex, list<INDEX16> _listIndex)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	m_listVertex = _listVertex;
	m_listIndex = _listIndex;

	m_dwVtxCnt = (int)m_listVertex.size();
	m_dwTriCnt = (int)m_listIndex.size();

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	list<VTXCOL>::iterator iter_vtx = m_listVertex.begin();
	for (size_t i = 0; i < m_listVertex.size(); ++i, ++iter_vtx)
	{
		pVertex[i] = (*iter_vtx);
	}

	m_pVB->Unlock();

	INDEX16* pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	list<INDEX16>::iterator iter_idx = m_listIndex.begin();
	for (size_t i = 0; i < m_listIndex.size(); ++i, ++iter_idx)
	{
		pIndex[i] = (*iter_idx);
	}

	m_pIB->Unlock();
	return S_OK;
}

void CVICustom::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CVICustom * CVICustom::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVICustom*	pInstance = new CVICustom(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CVICustom * CVICustom::Create(LPDIRECT3DDEVICE9 pGraphicDev, list<VTXCOL> _listVertex, list<INDEX16> _listIndex)
{
	CVICustom*	pInstance = new CVICustom(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(_listVertex,_listIndex)))
		Safe_Release(pInstance);

	return pInstance;
}

CVICustom * CVICustom::Create(LPDIRECT3DDEVICE9 pGraphicDev, LPCTSTR _address)
{
	CVICustom*	pInstance = new CVICustom(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(_address)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CVICustom::Clone(void)
{
	return new CVICustom(*this);
}

void CVICustom::Free(void)
{
	CVIBuffer::Free();
}

void CVICustom::Load_VI(LPCTSTR _address)
{
	HANDLE hFile = CreateFile(_address, GENERIC_READ, 0,0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	DWORD dwByte = 0;
	int	  iVtxCnt;
	int	  iIdxCnt;

	ReadFile(hFile, &iVtxCnt, sizeof(int), &dwByte, nullptr);

	for (int i = 0; i < iVtxCnt; ++i)
	{
		VTXCOL tempVertex;
		ReadFile(hFile, &tempVertex, sizeof(VTXCOL), &dwByte, nullptr);
		m_listVertex.emplace_back(tempVertex);
	}

	ReadFile(hFile, &iIdxCnt, sizeof(int), &dwByte, nullptr);

	for (int i = 0; i < iIdxCnt; ++i)
	{
		INDEX16 tempIndex;
		ReadFile(hFile, &tempIndex, sizeof(INDEX16), &dwByte, nullptr);
		m_listIndex.emplace_back(tempIndex);
	}

	CloseHandle(hFile);
}
