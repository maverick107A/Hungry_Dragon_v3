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

			// ������ ��
			pIndex[dwTriCnt]._0 = (_ushort)(dwIndex + dwCntX);
			pIndex[dwTriCnt]._1 = (_ushort)(dwIndex + dwCntX + 1);
			pIndex[dwTriCnt]._2 = (_ushort)(dwIndex + 1);
			dwTriCnt++;

			// ���� �Ʒ�
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
		char _b;		// Ʋ������
	}IDX24;

	//IDX24*		pPixel = new IDX24[m_ih.biWidth * m_ih.biHeight];
	_uint*		pPixel = new _uint[m_ih.biWidth * m_ih.biHeight];

	const int iSize = m_dwVtxCnt;

	m_vecHeight.resize(iSize);

	// 24��Ʈ��;;
	//ReadFile(m_hFile, pPixel, sizeof(IDX24) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);
	ReadFile(m_hFile, pPixel, sizeof(_uint) * m_ih.biWidth * m_ih.biHeight, &dwByte, NULL);

	CloseHandle(m_hFile);


	// ������� �б�
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
			int iIndex = i * 129 + j;			// 1���� -> 2���� �迭 ��ȯ������ �ε��� ���
			
			//m_vecHeight[iIndex] = (_uint)((pPixel[iIndex]._b));
			m_vecHeight[iIndex] = (_uint)((pPixel[iIndex] & 0x000000ff));

			float fHeight255 = (float)m_vecHeight[iIndex];
			float fHeightRate = fHeight255 / (float)255.f;
			float fHeightLerp = 0;//(float)(m_vecHeight[iIndex] % 51)/51.f;

			// ������1

			_uint uColorR[6] = { 0,124,0,25,0,128 };
			_uint uColorG[6] = { 146,157,166,223,200,222 };
			_uint uColorB[6] = { 81,118,81,148,87,81 };

			_uint uColor[6] = { 0 };

			for (int k = 0; k < 6; ++k)
			{
				fHeightRate[k] = fHeight255[k] / (float)255.f;
				fHeightLerp[k] = 0;// (float)(m_vecHeight[k] % 51) / 51.f;

				// ���� ����
				pVertex[dwIdx+k].vPosition.y = fHeightRate[k] * 2560.f;

	
				// �ϴ� ���� ���� ������ ���� �ϳ��θ� ����
				
				if ((fHeight255[k]) == 0.f)			uColor[k] = D3DCOLOR_XRGB(uColorR[0], uColorG[0], uColorB[0]);
				else if ((fHeight255[k]) < 51.f) 	uColor[k] = D3DCOLOR_XRGB(uColorR[0] + (int)((uColorR[1] - uColorR[0])*fHeightLerp[k]), uColorG[0] + (int)((uColorG[1] - uColorG[0])*fHeightLerp[k]), uColorB[0] + (int)((uColorB[1] - uColorB[0])*fHeightLerp[k]));
				else if ((fHeight255[k]) < 102.f)	uColor[k] = D3DCOLOR_XRGB(uColorR[1] + (int)((uColorR[2] - uColorR[1])*fHeightLerp[k]), uColorG[1] + (int)((uColorG[2] - uColorG[1])*fHeightLerp[k]), uColorB[1] + (int)((uColorB[2] - uColorB[1])*fHeightLerp[k]));
				else if ((fHeight255[k]) < 153.f)	uColor[k] = D3DCOLOR_XRGB(uColorR[2] + (int)((uColorR[3] - uColorR[2])*fHeightLerp[k]), uColorG[2] + (int)((uColorG[3] - uColorG[2])*fHeightLerp[k]), uColorB[2] + (int)((uColorB[3] - uColorB[2])*fHeightLerp[k]));
				else if ((fHeight255[k]) < 204.f)	uColor[k] = D3DCOLOR_XRGB(uColorR[3] + (int)((uColorR[4] - uColorR[3])*fHeightLerp[k]), uColorG[3] + (int)((uColorG[4] - uColorG[3])*fHeightLerp[k]), uColorB[3] + (int)((uColorB[4] - uColorB[3])*fHeightLerp[k]));
				else								uColor[k] = D3DCOLOR_XRGB(uColorR[4] + (int)((uColorR[5] - uColorR[4])*fHeightLerp[k]), uColorG[4] + (int)((uColorG[5] - uColorG[4])*fHeightLerp[k]), uColorB[4] + (int)((uColorB[5] - uColorB[4])*fHeightLerp[k]));

				pVertex[dwIdx + k].dwColor = uColor[k];

			}
			
			//�ϴ� ����
			//if (fHeightRate == 0.f)	pVertex[iIndex * 6].vPosition.y = -100.f;

			// ���� ���⿡ ���� ����ŷ �غ�
			_vec3 vLightDirection = { 0.f,-1.f,0.f };

			// �� �븻 ���
			_vec3 vVertexU = pVertex[dwIdx + 1].vPosition - pVertex[dwIdx].vPosition;
			_vec3 vVertexV = pVertex[dwIdx + 2].vPosition - pVertex[dwIdx+1].vPosition;
			_vec3 vVertexN;
			D3DXVec3Cross(&vVertexN, &vVertexU, &vVertexV);
			D3DXVec3Normalize(&vVertexN, &vVertexN);
			float fCosR = -D3DXVec3Dot(&vVertexN, &vLightDirection);

			vVertexU = pVertex[dwIdx + 4].vPosition - pVertex[dwIdx + 3].vPosition;
			vVertexV = pVertex[dwIdx + 5].vPosition - pVertex[dwIdx + 4].vPosition;
			D3DXVec3Cross(&vVertexN, &vVertexU, &vVertexV);
			D3DXVec3Normalize(&vVertexN, &vVertexN);
			float fCosL = -D3DXVec3Dot(&vVertexN, &vLightDirection);
			
			// �� ��� ���� + ���� ����
			_uint uIdxColorR = (((pVertex[dwIdx].dwColor & 0x00ff0000) >> 16) + ((pVertex[dwIdx + 1].dwColor & 0x00ff0000) >> 16) + ((pVertex[dwIdx + 2].dwColor & 0x00ff0000) >> 16))/3.f;
			_uint uIdxColorG = (((pVertex[dwIdx].dwColor & 0x0000ff00) >> 8) + ((pVertex[dwIdx + 1].dwColor & 0x0000ff00) >> 8) + ((pVertex[dwIdx + 2].dwColor & 0x0000ff00) >> 8))/3.f;
			_uint uIdxColorB = ((pVertex[dwIdx].dwColor & 0x000000ff) + (pVertex[dwIdx + 1].dwColor & 0x000000ff) + (pVertex[dwIdx + 2].dwColor & 0x000000ff))/3.f;
			
			// ���� Į�� �޾Ƽ� ���� ���� �� ����ؼ� �����ֱ� (���� ����)
			D3DXCOLOR tColorR(pVertex[dwIdx].dwColor);
			tColorR *= fCosR;
			pVertex[dwIdx].dwColor = D3DCOLOR_XRGB((_uint)(tColorR.r * 255.f), (_uint)(tColorR.g* 255.f), (_uint)(tColorR.b* 255.f));


			//pVertex[dwIdx].dwColor = D3DCOLOR_XRGB((_uint)(uIdxColorR*fCosR), (_uint)(uIdxColorG*fCosR), (_uint)(uIdxColorB*fCosR));
			


			uIdxColorR = (((pVertex[dwIdx+3].dwColor & 0x00ff0000) >> 16) + ((pVertex[dwIdx + 4].dwColor & 0x00ff0000) >> 16) + ((pVertex[dwIdx + 5].dwColor & 0x00ff0000) >> 16)) / 3.f;
			uIdxColorG = (((pVertex[dwIdx+3].dwColor & 0x0000ff00) >> 8) + ((pVertex[dwIdx + 4].dwColor & 0x0000ff00) >> 8) + ((pVertex[dwIdx + 5].dwColor & 0x0000ff00) >> 8)) / 3.f;
			uIdxColorB = ((pVertex[dwIdx+3].dwColor & 0x000000ff) + (pVertex[dwIdx + 4].dwColor & 0x000000ff) + (pVertex[dwIdx + 5].dwColor & 0x000000ff)) / 3.f;
			
			// ���� Į�� �޾Ƽ� ���� ���� �� ����ؼ� �����ֱ� (���� ����)
			D3DXCOLOR tColorL(pVertex[dwIdx+3].dwColor);
			tColorL *= fCosL;
			pVertex[dwIdx+3].dwColor = D3DCOLOR_XRGB((_uint)(tColorL.r * 255.f), (_uint)(tColorL.g* 255.f), (_uint)(tColorL.b* 255.f));

			
			//pVertex[dwIdx+3].dwColor = D3DCOLOR_XRGB((_uint)(uIdxColorR*fCosL), (_uint)(uIdxColorG*fCosL), (_uint)(uIdxColorB*fCosL));

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

