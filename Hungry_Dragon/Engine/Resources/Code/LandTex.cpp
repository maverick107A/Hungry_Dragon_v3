#include "LandTex.h"

USING(Engine)

Engine::CLandTex::CLandTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CLandTex::CLandTex(const CLandTex& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CLandTex::~CLandTex(void)
{

}

HRESULT Engine::CLandTex::Ready_Buffer(void)
{
	m_dwVtxCnt = 129*129;
	m_dwTriCnt = 128*128*2;
	m_dwVtxSize = sizeof(VTXUV);
	m_dwFVF = FVF_UV;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);


	// ������� �б�
	int startX = -128 / 2;
	int startZ = -256 / 2;
	int endX = 128 / 2;
	int endZ = 256 / 2;

	// uv ��ǥ ����
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
			int index = i * 129 + j;			// 1���� -> 2���� �迭 ��ȯ������ �ε��� ���
			 
			pVertex[index] = VTXUV(
				(float)x,
				0.f,
				//(float)_heightmap[index],				// ���̸� �����ؾ� ��
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}



	
	m_pVB->Unlock();

	WORD*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// �簢�� ���� ǥ���ϱ� ���� 6���� �ε����� �������� �ݺ����� ����
	int baseIndex = 0;

	// ������ �ε����� ���
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			pIndex[baseIndex] = i   * 129 + j;
			pIndex[baseIndex + 2] = i   * 129 + j + 1;
			pIndex[baseIndex + 1] = (i + 1) * 129 + j;

			pIndex[baseIndex + 3] = (i + 1) * 129 + j;
			pIndex[baseIndex + 5] = i   * 129 + j + 1;
			pIndex[baseIndex + 4] = (i + 1) * 129 + j + 1;

			// ���� ����
			baseIndex += 6;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CLandTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CLandTex::Set_Height(void * _bitmap)
{

	std::vector<int>* pBit = (std::vector<int>*)(_bitmap);

	// ������� �б�
	int startX = -128 / 2;
	int startZ = -256 / 2;
	int endX = 128 / 2;
	int endZ = 256 / 2;

	// uv ��ǥ ����
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
			int index = i * 129 + j;			// 1���� -> 2���� �迭 ��ȯ������ �ε��� ���

			pVertex[index] = VTXUV(
				(float)x,
				(float)(*pBit)[index]/(float)256.f * 15.f,
				//(float)_heightmap[index],				// ���̸� �����ؾ� ��
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}




	m_pVB->Unlock();
}

void Engine::CLandTex::Free(void)
{
	CVIBuffer::Free();
}

CLandTex* Engine::CLandTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLandTex*	pInstance = new CLandTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CLandTex::Clone(void)
{
	return new CLandTex(*this);
}

