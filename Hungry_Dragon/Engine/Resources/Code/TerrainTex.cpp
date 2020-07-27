#include "TerrainTex.h"
USING(Engine)

Engine::CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CTerrainTex::CTerrainTex(const CTerrainTex& rhs)
	: CVIBuffer(rhs)
{
}

Engine::CTerrainTex::~CTerrainTex(void)
{

}

HRESULT Engine::CTerrainTex::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	m_dwVtxCnt = dwCntX * dwCntZ;
	m_dwCntZ = dwCntZ;
	m_dwCntX = dwCntX;
	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;
	m_Terrain_Interval = 1;
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	_ulong		dwByte = 0;

	m_hFile = CreateFile(L"../Bin/Resource/Texture/Terrain/Height2.bmp", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(m_hFile, &m_fh, sizeof(BITMAPFILEHEADER), &dwByte, NULL);
	ReadFile(m_hFile, &m_ih, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	m_pHight = new _ulong[m_ih.biWidth * m_ih.biHeight];

	ReadFile(m_hFile, m_pHight, sizeof(_ulong) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);

	CloseHandle(m_hFile);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	_ulong	dwIndex = 0;

	for (_ulong i = 0; i < dwCntZ; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPosition = _vec3(_float(j) * dwVtxItv,
				(m_pHight[dwIndex] & 0x000000ff) / 20.f,
				_float(i) * dwVtxItv);
			pVertex[dwIndex].vTexUV = _vec2(_float(j) / (dwCntX - 1), _float(i) / (dwCntZ - 1));

		}
	}

	m_pVB->Unlock();

	

	INDEX32*		pIndex = nullptr;

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

	return S_OK;
}

void Engine::CTerrainTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

_ulong CTerrainTex::Get_Height(const _float & _X, const _float & _Z)
{

	_float _Index_X =  0;
	_float _Index_Y = 0;
	_int _TriPoint = 0;

	Piking_Terrain(_X, _Z , _Index_X , _Index_Y , _TriPoint );
	
	int iIndex = (int)(_Index_Y * m_dwCntZ) + (int)_Index_X;

	return m_pHight[iIndex];
}

void CTerrainTex::Piking_Terrain(const _float  & _x, const _float & _z  ,  _float  & _Index_X,  _float &_Index_Y , _int  & _TriPoint)
{
	// 간격으로 나눠서 인덱스 피킹하는곳
	_Index_X = _x / m_Terrain_Interval;
	_Index_Y = _z / m_Terrain_Interval;


	// 현재 있는 사각형의 좌하단 우화단 좌상단 우상단인지를 판별하지 위한 위치값 구하는곳
	// 현재 속해있는 사각형의 경계들
	_float fStandard = m_Terrain_Interval * 0.5f;
	
	_float fTri_PosX = fmodf(_x , m_Terrain_Interval);
	_float fTri_PosZ = fmodf(_z, m_Terrain_Interval);



	if (fStandard > fTri_PosX)
	{

		if (fStandard > fTri_PosZ)
		{
			_TriPoint = 1;
		}
		
		else if (fStandard < fTri_PosZ)
		{
				_TriPoint = 3;
		}



	}
		
		
	else if (fStandard < fTri_PosX)
	{
		if (fStandard > fTri_PosZ)
		{
			_TriPoint = 2;
		}

		else if (fStandard < fTri_PosZ)
		{
			_TriPoint = 4;
		}
	}


	
}




CTerrainTex* Engine::CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	CTerrainTex*	pInstance = new CTerrainTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CTerrainTex::Clone(void)
{
	return new CTerrainTex(*this);
}

void Engine::CTerrainTex::Free(void)
{
	Safe_Delete_Array(m_pHight);
	CVIBuffer::Free();
}

