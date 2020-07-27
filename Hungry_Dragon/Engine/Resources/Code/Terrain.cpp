#include "Terrain.h"
#include <iostream>
#include <fstream>

USING(Engine)

Engine::CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CTerrain::CTerrain(const CTerrain& rhs)
	: CVIBuffer(rhs)
{
	m_vecHeight = rhs.m_vecHeight;
	m_pTex = rhs.m_pTex;
}

Engine::CTerrain::~CTerrain(void)
{

}

HRESULT Engine::CTerrain::Ready_Buffer(void)
{	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Terrain/ColorHeight.bmp",
		&m_pTex);

	//∏ ¿–±‚
	FILE* FilePtr = nullptr;
	fopen_s(&FilePtr, "../Bin/Resource/Texture/Terrain/ColorHeight.bmp", "rb");
	BITMAPFILEHEADER bitmapFileHeader;
	fread(&bitmapFileHeader, sizeof(bitmapFileHeader), 1, FilePtr);

	const int iSize = 129 * 129;

	m_vecHeight.resize(iSize);

	unsigned char* imgInfo = new unsigned char[iSize*4];

	fseek(FilePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	fread(imgInfo, 1, iSize*4, FilePtr);
	fclose(FilePtr);

	int iTemp = 0;
	for (int i = 0; i < iSize; ++i)
	{
		m_vecHeight[i] = imgInfo[iTemp];
		iTemp += 4;
	}
	delete[] imgInfo;


	//∏ ¬Ô±‚
	m_dwVtxCnt = 129*129;
	m_dwTriCnt = 128*128*2;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	
	for (int i = 0; i < 129; ++i)
	{
		for (int j = 0; j < 129; ++j)
		{
			pVertex[j + i * 129].vPosition = _vec3(float(j), m_vecHeight[(j + i * 129)]*0.05f, float(i));
			pVertex[j + i * 129].vTexUV = {j / 128.f, 1- i / 128.f };
			//pVertex[j + i * 129].vPosition = _vec3(float(j), m_vecHeight[(j + (128 - i) * 129) * 4] * 0.05f, -float(i));
			//pVertex[j + i * 129].vTexUV = { j / 128.f,i / 128.f };
		}
	}

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);



	int iPoint = 0;
	for (int j = 0; j < 128; ++j)
	{
		for (int i = 0; i < 128; ++i)
		{
			iPoint = i + j * 129;
			pIndex[(i + j * 128) * 2]._0 = iPoint;
			pIndex[(i + j * 128) * 2]._2 = iPoint + 1;
			pIndex[(i + j * 128) * 2]._1 = iPoint + 129;
						
			pIndex[(i + j * 128) * 2 + 1]._0 = iPoint + 129;
			pIndex[(i + j * 128) * 2 + 1]._2 = iPoint + 1;
			pIndex[(i + j * 128) * 2 + 1]._1 = iPoint + 1 + 129;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CTerrain::Render_Buffer(void)
{

	m_pGraphicDev->SetTexture(0, m_pTex);

	CVIBuffer::Render_Buffer();
}

void Engine::CTerrain::Free(void)
{

		m_pTex->Release();
	CVIBuffer::Free();
}

const vector<int>& CTerrain::Get_TerrainHeight()
{
	return m_vecHeight;
}

CTerrain* Engine::CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain*	pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CTerrain::Clone(void)
{
	return new CTerrain(*this);
}

