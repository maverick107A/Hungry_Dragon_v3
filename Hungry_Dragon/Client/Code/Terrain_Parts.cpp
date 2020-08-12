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


// 용접 행위 일단 129X129 상수화만 되어있음
void CTerrain_Parts::Weld_Edge(CTerrain_Parts * _Dst, bool _bHorizontal)
{
	_float fJoinPoint;

	if (_bHorizontal)	// 오른쪽이랑 접합
	{
		VTXCOL* pLeft = m_pBufferCom->Get_EntryVB();
		VTXCOL* pRight = _Dst->Get_BufferCom()->Get_EntryVB();
		for (int i = 0; i < 129; ++i)
		{
			fJoinPoint = (pLeft[i * 129 + 128].vPosition.y + pRight[i * 129].vPosition.y)*0.5f;
			pLeft[i * 129 + 128].vPosition.y = fJoinPoint;
			pRight[i * 129].vPosition.y = fJoinPoint;
		}

	}
	else                // 아래쪽이랑 접합
	{
		VTXCOL* pUp = m_pBufferCom->Get_EntryVB();
		VTXCOL* pDown = _Dst->Get_BufferCom()->Get_EntryVB();
		int iPivot = 128 * 129;

		for (int i = 0; i < 129; ++i)
		{
			fJoinPoint = (pUp[iPivot + i].vPosition.y + pDown[i].vPosition.y)*0.5f;
			pUp[iPivot + i].vPosition.y = fJoinPoint;
			pDown[i].vPosition.y = fJoinPoint;
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

