#include "stdafx.h"
#include "Cloud_Parts.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Ingame_Flow.h"

CCloud_Parts::CCloud_Parts(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CCloud_Parts::~CCloud_Parts(void)
{

}

HRESULT CCloud_Parts::Ready_Object(void)
{
	m_uVerCntX = 129;
	m_uVerCntZ = 129;
	m_uLength = 100;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CCloud_Parts::Initialize_Object()
{

}

_int CCloud_Parts::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;


	return 0;
}

void CCloud_Parts::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);


	m_pBufferCom->Render_Buffer();
		
}

void CCloud_Parts::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
	m_pTransform->Update_Component(0);
}

void CCloud_Parts::Set_RotationReverse()
{
	m_pTransform->Rotation(ROTATION::ROT_Z, D3DX_PI);
	m_pTransform->Rotation(ROTATION::ROT_X, D3DX_PI);
}

void CCloud_Parts::Set_Height(_float _fHeight, _uint _uContrast)
{
	m_pBufferCom->Set_RandomHeight(_fHeight, _uContrast);
}

// 용접 행위 일단 129X129 상수화만 되어있음
void CCloud_Parts::Weld_Edge(CCloud_Parts * _Dst, bool _bHorizontal)
{
	_float fJoinPoint[129] = { 0 };
	int iPivot = 127 * 128;

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
		}

	}
	else                // 아래쪽이랑 접합
	{
		VTXCOL* pUp = m_pBufferCom->Get_EntryVB();
		VTXCOL* pDown = _Dst->Get_BufferCom()->Get_EntryVB();


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
		}
	}

}



void CCloud_Parts::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/


	Engine::CGameObject::Free();

	
	Safe_Release(m_pBufferCom);

}


HRESULT CCloud_Parts::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	m_pBufferCom = CHeightCol::Create(m_pGraphicDev, m_uVerCntX, m_uVerCntZ, m_uLength);

	return S_OK;
}

CCloud_Parts* CCloud_Parts::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCloud_Parts*		pInstance = new CCloud_Parts(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

