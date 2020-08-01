#include "Texture_Plane.h"

USING(Engine)

Engine::CTexture_Plane::CTexture_Plane(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CTexture_Plane::CTexture_Plane(const CTexture_Plane& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CTexture_Plane::~CTexture_Plane(void)
{

}

HRESULT Engine::CTexture_Plane::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	m_dwVtxCnt = dwCntX * dwCntZ;
	m_dwCntZ = dwCntZ;
	m_dwCntX = dwCntX;
	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	_ulong		dwByte = 0;

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	_ulong	dwIndex = 0;

	for (_ulong i = 0; i < dwCntZ; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPosition = _vec3(_float(j) * dwVtxItv,
				0.f,
				_float(i) * dwVtxItv);
			pVertex[dwIndex].vTexUV = _vec2(_float(j) , _float(i) );

		}
	}

	m_pVB->Unlock();



	INDEX16*		pIndex = nullptr;

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

void Engine::CTexture_Plane::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CTexture_Plane::Set_Height(void * _bitmap)
{

	std::vector<int>* pBit = (std::vector<int>*)(_bitmap);

	// 윈도우식 읽기
	int startX = -128 / 2;
	int startZ = -256 / 2;
	int endX = 128 / 2;
	int endZ = 256 / 2;

	// uv 좌표 지정
	float uCoordIncrementSize = 1.0f / (float)128;
	float vCoordIncrementSize = 1.0f / (float)128;

	VTXUV*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);



	int i = 0;
	for (int z = startZ; z <= endZ; z += 2)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += 1)
		{
			int index = i * 129 + j;			// 1차원 -> 2차원 배열 변환식으로 인덱스 계산

			pVertex[index] = VTXUV(
				(float)x,
				(float)(*pBit)[index]/(float)256.f * 15.f,
				//(float)_heightmap[index],				// 높이맵 적용해야 함
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}




	m_pVB->Unlock();
}

void Engine::CTexture_Plane::Free(void)
{
	CVIBuffer::Free();
}

CTexture_Plane* Engine::CTexture_Plane::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	CTexture_Plane*	pInstance = new CTexture_Plane(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CTexture_Plane::Clone(void)
{
	return new CTexture_Plane(*this);
}

