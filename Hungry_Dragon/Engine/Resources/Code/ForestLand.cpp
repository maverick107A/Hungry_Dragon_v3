#include "ForestLand.h"
#include "ResourcesMgr.h"

USING(Engine)

Engine::CForestLand::CForestLand(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseLand(pGraphicDev)
{

}

Engine::CForestLand::CForestLand(const CForestLand& rhs)
	: CBaseLand(rhs)
{
	m_pTerrainTex = rhs.m_pTerrainTex;
	m_vecHeight = rhs.m_vecHeight;
}

Engine::CForestLand::~CForestLand(void)
{

}

HRESULT Engine::CForestLand::Ready_Buffer(void)
{
	_ulong dwCntX = 129;
	_ulong dwCntZ = 129;
	_ulong dwVtxItv = 200;
	m_dwVtxCnt = dwCntX * dwCntZ;
	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	_ulong		dwByte = 0;

	m_hFile = CreateFile(L"../../Asset/Terrain/TestHeight.bmp", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(m_hFile, &m_fh, sizeof(BITMAPFILEHEADER), &dwByte, NULL);
	ReadFile(m_hFile, &m_ih, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	_ulong*		pPixel = new _ulong[m_ih.biWidth * m_ih.biHeight];

	const int iSize = 129 * 129;

	m_vecHeight.resize(iSize);

	ReadFile(m_hFile, pPixel, sizeof(_ulong) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);

	CloseHandle(m_hFile);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	_ulong	dwIndex = 0;

	for (_ulong i = 0; i < dwCntZ; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			m_vecHeight[dwIndex] = (int)((pPixel[dwIndex] & 0x000000ff)*10.f);

			pVertex[dwIndex].vPosition = _vec3(_float(j) * dwVtxItv,
				_float(m_vecHeight[dwIndex]),
				_float(i) * _float(dwVtxItv));
			pVertex[dwIndex].vTexUV = _vec2(_float(j) / (dwCntX - 1), _float(dwCntZ-1-i) / (dwCntZ - 1));

			
		}
	}

	m_pVB->Unlock();
	Safe_Delete_Array(pPixel);

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	_ulong	dwTriCnt = 0;

	for (_ulong i = 0; i < dwCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			dwIndex = i * dwCntX + j;

			// 오른쪽 위
			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;
			dwTriCnt++;

			// 왼쪽 아래
			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;
			dwTriCnt++;
		}
	}

	m_pIB->Unlock();


	FAILED_CHECK_RETURN(CResourcesMgr::GetInstance()->Ready_Texture(m_pGraphicDev,
		0,
		L"Tex_TestTerrain",
		Engine::TEX_NORMAL,
		L"../../Asset/Terrain/TestTerrain.png"),
		E_FAIL);
	m_pTerrainTex = dynamic_cast<CTexture*>(CResourcesMgr::GetInstance()->Clone(0, L"Tex_TestTerrain"));
	return S_OK;
}

void Engine::CForestLand::Render_Buffer(void)
{
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	m_pTerrainTex->Set_Texture();

	CVIBuffer::Render_Buffer();
}

void Engine::CForestLand::Free(void)
{
	Safe_Release(m_pTerrainTex);
	CVIBuffer::Free();
}

CForestLand* Engine::CForestLand::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CForestLand*	pInstance = new CForestLand(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CForestLand::Clone(void)
{
	return new CForestLand(*this);
}

