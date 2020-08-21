#include "stdafx.h"
#include "Terrain_Parts.h"
#include "Export_Function.h"
#include "HeightCol.h"


CTerrain_Parts::CTerrain_Parts(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CTerrain_Parts::~CTerrain_Parts(void)
{

}

HRESULT CTerrain_Parts::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTerrain_Parts::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CTerrain_Parts::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	
	m_pBufferCom->Render_Buffer();
}

void CTerrain_Parts::Set_HeightMap(const _tchar * _pPath)
{
	m_pBufferCom->Set_Height(_pPath);
}

void CTerrain_Parts::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

vector<int> CTerrain_Parts::Get_HeightVector()
{
	return m_pBufferCom->Get_TerrainHeight();
}


// 용접 행위 일단 129X129 상수화만 되어있음
void CTerrain_Parts::Weld_Edge(CTerrain_Parts * _Dst, bool _bHorizontal)
{
	_float fJoinPoint[129] = { 0 };
	int iPivot = 127 * 128;

	vector<float>& rSrcHeightMap = m_pBufferCom->Get_AdvanceHeight();
	vector<float>& rDstHeightMap = _Dst->Get_BufferCom()->Get_AdvanceHeight();

	if (_bHorizontal)	// 오른쪽이랑 접합
	{
		VTXCOL* pLeft = m_pBufferCom->Get_EntryVB();
		VTXCOL* pRight = _Dst->Get_BufferCom()->Get_EntryVB();

		for (int i = 0; i < 128; ++i)
		{
			fJoinPoint[i + 1] = (pLeft[(i * 128 + 127) * 6 + 1].vPosition.y + pRight[i * 128 * 6].vPosition.y)*0.5f;
		}
		fJoinPoint[0] = (pLeft[(127) * 6 + 2].vPosition.y + pRight[5].vPosition.y)*0.5f;

		for (int i = 0; i < 128; ++i)
		{
			// 1 2=4 <-> 0=3 5
			//fJoinPoint = (pLeft[(i * 128 + 127)* 6+1].vPosition.y + pRight[i * 128 * 6].vPosition.y)*0.5f;
			pLeft[(i * 128 + 127) * 6 + 1].vPosition.y = fJoinPoint[i + 1];
			pRight[i * 128 * 6].vPosition.y = fJoinPoint[i + 1];
			pRight[i * 128 * 6 + 3].vPosition.y = fJoinPoint[i + 1];

			//fJoinPoint = (pLeft[(i * 128 + 127) * 6+2].vPosition.y + pRight[i * 128 * 6 + 5].vPosition.y)*0.5f;
			pLeft[(i * 128 + 127) * 6 + 2].vPosition.y = fJoinPoint[i];
			pLeft[(i * 128 + 127) * 6 + 4].vPosition.y = fJoinPoint[i];
			pRight[i * 128 * 6 + 5].vPosition.y = fJoinPoint[i];

			// 높이맵 갱신

			//구버전 잘못된 버전
			//rSrcHeightMap[(127 - i) * 129 + 128] = fJoinPoint[i + 1];
			//rDstHeightMap[(127 - i) * 129] = fJoinPoint[i + 1];
			//rSrcHeightMap[(128 - i) * 129 + 128] = fJoinPoint[i];
			//rDstHeightMap[(128 - i) * 129] = fJoinPoint[i];

			rSrcHeightMap[(i) * 129 + 128] = fJoinPoint[i];
			rDstHeightMap[(i) * 129] = fJoinPoint[i];
		}

	}
	else                // 아래쪽이랑 접합
	{
		VTXCOL* pUp = m_pBufferCom->Get_EntryVB();
		VTXCOL* pDown = _Dst->Get_BufferCom()->Get_EntryVB();

		_uint uPivot = 129 * 128;

		for (int i = 0; i < 128; ++i)
		{
			fJoinPoint[i] = (pUp[(i) * 6 + 5].vPosition.y + pDown[(i + iPivot) * 6].vPosition.y)*0.5f;
		}
		fJoinPoint[128] = (pUp[(127) * 6 + 2].vPosition.y + pDown[(127 + iPivot) * 6 + 1].vPosition.y)*0.5f;

		for (int i = 0; i < 128; ++i)
		{
			// 5 2=4 <-> 0=3 1
			//fJoinPoint = (pUp[iPivot + i].vPosition.y + pDown[i].vPosition.y)*0.5f;
			//pUp[iPivot + i].vPosition.y = fJoinPoint;
			//pDown[i].vPosition.y = fJoinPoint;

			//fJoinPoint = (pUp[(i * 128 + 127) * 6 + 5].vPosition.y + pDown[i * 128 * 6].vPosition.y)*0.5f;
			pUp[(i) * 6 + 5].vPosition.y = fJoinPoint[i];
			pDown[(i + iPivot) * 6].vPosition.y = fJoinPoint[i];
			pDown[(i + iPivot) * 6 + 3].vPosition.y = fJoinPoint[i];

			//fJoinPoint = (pUp[(i * 128 + 127) * 6 + 2].vPosition.y + pDown[i * 128 * 6 + 1].vPosition.y)*0.5f;
			pUp[(i) * 6 + 2].vPosition.y = fJoinPoint[i + 1];
			pUp[(i) * 6 + 4].vPosition.y = fJoinPoint[i + 1];
			pDown[(i + iPivot) * 6 + 1].vPosition.y = fJoinPoint[i + 1];

			// 높이맵 갱신
			//구버전 잘못된 버전
			/*rSrcHeightMap[uPivot + i + 1] = fJoinPoint[i + 1];
			rDstHeightMap[i + 1] = fJoinPoint[i + 1];
			rSrcHeightMap[uPivot + i] = fJoinPoint[i];
			rDstHeightMap[i] = fJoinPoint[i];*/

			rSrcHeightMap[i] = fJoinPoint[i];
			rDstHeightMap[uPivot + i] = fJoinPoint[i];
		}
	}

}

void CTerrain_Parts::Free(void)
{

	Engine::CGameObject::Free();

	Safe_Release(m_pBufferCom);
}


HRESULT CTerrain_Parts::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	m_pBufferCom = CHeightCol::Create(m_pGraphicDev, 129, 129, 100);
	//FAILED_CHECK(Clone_Component<CHeightCol>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CTerrain_Parts* CTerrain_Parts::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain_Parts*		pInstance = new CTerrain_Parts(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

