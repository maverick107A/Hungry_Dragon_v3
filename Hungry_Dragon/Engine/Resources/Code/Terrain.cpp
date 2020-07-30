#include "Terrain.h"
#include <iostream>
#include <fstream>

USING(Engine)

Engine::CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
	, m_bClone(false)
{

}

Engine::CTerrain::CTerrain(const CTerrain& rhs)
	: CVIBuffer(rhs)
	, m_bClone(true)
	, m_pPos(rhs.m_pPos)
{
	m_vecHeight = rhs.m_vecHeight;
	m_pTex = rhs.m_pTex;
	m_pTex->AddRef();
}

Engine::CTerrain::~CTerrain(void)
{

}

HRESULT Engine::CTerrain::Ready_Buffer(void)
{
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Terrain/ColorHeight.bmp",
		&m_pTex);
	m_pPos = new _vec3[VERTEXSIZE * VERTEXSIZE];
	//∏ ¿–±‚
	FILE* FilePtr = nullptr;
	fopen_s(&FilePtr, "../Bin/Resource/Texture/Terrain/ColorHeight.bmp", "rb");
	BITMAPFILEHEADER bitmapFileHeader;
	fread(&bitmapFileHeader, sizeof(bitmapFileHeader), 1, FilePtr);

	const int iSize = VERTEXSIZE * VERTEXSIZE;

	m_vecHeight.resize(iSize);

	unsigned char* imgInfo = new unsigned char[iSize * 4];

	fseek(FilePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	fread(imgInfo, 1, iSize * 4, FilePtr);
	fclose(FilePtr);

	int iTemp = 0;
	for (int i = 0; i < iSize; ++i)
	{
		m_vecHeight[i] = 0.f;
		iTemp += 4;
	}
	delete[] imgInfo;


	//∏ ¬Ô±‚
	m_dwVtxCnt = VERTEXSIZE *VERTEXSIZE;
	m_dwTriCnt = (VERTEXSIZE - 1)*(VERTEXSIZE - 1) * 2;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (int i = 0; i < VERTEXSIZE; ++i)
	{
		for (int j = 0; j < VERTEXSIZE; ++j)
		{
			pVertex[j + i * VERTEXSIZE].vPosition = _vec3(float(j)*TILECX, m_vecHeight[(j + i * VERTEXSIZE)], float(i)*TILECX);
			m_pPos[j + i * VERTEXSIZE] = pVertex[j + i * VERTEXSIZE].vPosition;
			
			pVertex[j + i * VERTEXSIZE].vTexUV = { j / float(VERTEXSIZE - 1), 1 - i / float(VERTEXSIZE - 1) };
			//pVertex[j + i * VERTEXSIZE].vPosition = _vec3(float(j), m_vecHeight[(j + (128 - i) * 129) * 4] * 0.05f, -float(i));
			//pVertex[j + i * VERTEXSIZE].vTexUV = { j / 128.f,i / 128.f };
		}
	}
	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);



	int iPoint = 0;
	for (int j = 0; j < (VERTEXSIZE - 1); ++j)
	{
		for (int i = 0; i < (VERTEXSIZE - 1); ++i)
		{
			iPoint = i + j * VERTEXSIZE;
			pIndex[(i + j * (VERTEXSIZE - 1)) * 2]._0 = iPoint;
			pIndex[(i + j * (VERTEXSIZE - 1)) * 2]._2 = iPoint + 1;
			pIndex[(i + j * (VERTEXSIZE - 1)) * 2]._1 = iPoint + VERTEXSIZE;

			pIndex[(i + j * (VERTEXSIZE - 1)) * 2 + 1]._0 = iPoint + VERTEXSIZE;
			pIndex[(i + j * (VERTEXSIZE - 1)) * 2 + 1]._2 = iPoint + 1;
			pIndex[(i + j * (VERTEXSIZE - 1)) * 2 + 1]._1 = iPoint + 1 + VERTEXSIZE;
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
	if (false == m_bClone)
		Safe_Delete_Array(m_pPos);


	Safe_Release(m_pTex);
	CVIBuffer::Free();
}

const vector<float>& CTerrain::Get_TerrainHeight()
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

