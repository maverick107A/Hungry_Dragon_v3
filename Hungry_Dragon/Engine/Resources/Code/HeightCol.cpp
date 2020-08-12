#include "HeightCol.h"

USING(Engine)

Engine::CHeightCol::CHeightCol(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBaseLand(pGraphicDev)
{

}

Engine::CHeightCol::CHeightCol(const CHeightCol& rhs)
	: CBaseLand(rhs)
{
	m_vecHeight = rhs.m_vecHeight;
	m_dwVtxCnt = rhs.m_dwVtxCnt;
	m_dwCntZ = rhs.m_dwCntZ;
	m_dwCntX = rhs.m_dwCntX;
}

Engine::CHeightCol::~CHeightCol(void)
{

}

HRESULT Engine::CHeightCol::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	m_dwVtxCnt = dwCntX * dwCntZ;
	m_dwCntZ = dwCntZ;
	m_dwCntX = dwCntX;
	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	_ulong		dwByte = 0;

	VTXCOL*		pVertex = nullptr;

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
			pVertex[dwIndex].dwColor = D3DCOLOR_XRGB(255,255,255);

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
			pIndex[dwTriCnt]._0 = (_ushort)(dwIndex + dwCntX);
			pIndex[dwTriCnt]._1 = (_ushort)(dwIndex + dwCntX + 1);
			pIndex[dwTriCnt]._2 = (_ushort)(dwIndex + 1);
			dwTriCnt++;

			// 왼쪽 아래
			pIndex[dwTriCnt]._0 = (_ushort)(dwIndex + dwCntX);
			pIndex[dwTriCnt]._1 = (_ushort)dwIndex + 1;
			pIndex[dwTriCnt]._2 = (_ushort)dwIndex;
			dwTriCnt++;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CHeightCol::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CHeightCol::Set_Height(const _tchar* _pPath)
{
	_ulong		dwByte = 0;

	m_hFile = CreateFile(_pPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(m_hFile, &m_fh, sizeof(BITMAPFILEHEADER), &dwByte, NULL);
	ReadFile(m_hFile, &m_ih, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	typedef struct tagIdx24
	{
		char _r;
		char _g;
		char _b;		// 틀릴수도
	}IDX24;

	//IDX24*		pPixel = new IDX24[m_ih.biWidth * m_ih.biHeight];
	_uint*		pPixel = new _uint[m_ih.biWidth * m_ih.biHeight];

	const int iSize = m_dwVtxCnt;

	m_vecHeight.resize(iSize);

	// 24비트라;;
	//ReadFile(m_hFile, pPixel, sizeof(IDX24) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);
	ReadFile(m_hFile, pPixel, sizeof(_uint) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);

	CloseHandle(m_hFile);


	// 윈도우식 읽기
	int startX = -128 / 2;
	int startZ = -256 / 2;
	int endX = 128 / 2;
	int endZ = 256 / 2;



	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);



	int i = 0;
	for (int z = startZ; z <= endZ; z += 2)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += 1)
		{
			int iIndex = i * 129 + j;			// 1차원 -> 2차원 배열 변환식으로 인덱스 계산
			
			//m_vecHeight[iIndex] = (_uint)((pPixel[iIndex]._b));
			m_vecHeight[iIndex] = (_uint)((pPixel[iIndex] & 0x000000ff));

			float fHeight255 = (float)m_vecHeight[iIndex];
			float fHeightRate = fHeight255 / (float)255.f;
			float fHeightLerp = 0;//(float)(m_vecHeight[iIndex] % 51)/51.f;

			// 프리셋1
			_uint uColorR[6] = {0,124,0,25,0,128};
			_uint uColorG[6] = {166,197,166,223,200,222};
			_uint uColorB[6] = {81,118,81,148,87,81};

			// 일단 여기 다중 프리셋 없이 하나로만 적용
			_uint uColor = 0;
			if((fHeight255)==0.f)			uColor = D3DCOLOR_XRGB(uColorR[0] , uColorG[0] , uColorB[0]);
			else if ((fHeight255) < 51.f) 	uColor = D3DCOLOR_XRGB(uColorR[0] + (int)((uColorR[1] - uColorR[0])*fHeightLerp), uColorG[0] + (int)((uColorG[1] - uColorG[0])*fHeightLerp), uColorB[0] + (int)((uColorB[1] - uColorB[0])*fHeightLerp));
			else if ((fHeight255) < 102.f)	uColor = D3DCOLOR_XRGB(uColorR[1] + (int)((uColorR[2] - uColorR[1])*fHeightLerp), uColorG[1] + (int)((uColorG[2] - uColorG[1])*fHeightLerp), uColorB[1] + (int)((uColorB[2] - uColorB[1])*fHeightLerp));
			else if ((fHeight255) < 153.f)  uColor = D3DCOLOR_XRGB(uColorR[2] + (int)((uColorR[3] - uColorR[2])*fHeightLerp), uColorG[2] + (int)((uColorG[3] - uColorG[2])*fHeightLerp), uColorB[2] + (int)((uColorB[3] - uColorB[2])*fHeightLerp));
			else if ((fHeight255) < 204.f)  uColor = D3DCOLOR_XRGB(uColorR[3] + (int)((uColorR[4] - uColorR[3])*fHeightLerp), uColorG[3] + (int)((uColorG[4] - uColorG[3])*fHeightLerp), uColorB[3] + (int)((uColorB[4] - uColorB[3])*fHeightLerp));
			else							uColor = D3DCOLOR_XRGB(uColorR[4] + (int)((uColorR[5] - uColorR[4])*fHeightLerp), uColorG[4] + (int)((uColorG[5] - uColorG[4])*fHeightLerp), uColorB[4] + (int)((uColorB[5] - uColorB[4])*fHeightLerp));


			pVertex[iIndex].vPosition.y = fHeightRate * 2560.f;
			if(fHeightRate==0.f)
				pVertex[iIndex].vPosition.y = -100.f;

			pVertex[iIndex].dwColor = uColor;

			++j;
		}
		++i;
	}

	m_pVB->Unlock();

	Safe_Delete_Array(pPixel);
}

VTXCOL* CHeightCol::Get_EntryVB()
{
	VTXCOL*		pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	m_pVB->Unlock();
	return pVertex;
}

void Engine::CHeightCol::Free(void)
{
	CVIBuffer::Free();
}

CHeightCol* Engine::CHeightCol::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	CHeightCol*	pInstance = new CHeightCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CHeightCol::Clone(void)
{
	return new CHeightCol(*this);
}

