#include "stdafx.h"
#include "Cloud_Locater.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "Cloud_Parts.h"

CCloud_Locater::CCloud_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CCloud_Locater::~CCloud_Locater(void)
{

}

HRESULT CCloud_Locater::Ready_Object(void)
{
	m_uVerCntX = 129;
	m_uVerCntZ = 129;
	m_uLength = 1000;		// 생성자 통해서 파츠에 넘겨주는부분이 없음, 그냥 상수 때려박은것
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

void CCloud_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CCloud_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;


	return 0;
}

void CCloud_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);

	

	_int iPlayerX = (_int)(m_pPlayerTrans->Get_World()._41 / (m_uLength*(m_uVerCntX - 1)));
	if (0.f > m_pPlayerTrans->Get_World()._41)
	{
		--iPlayerX;
	}
	_int iPlayerZ = (_int)(m_pPlayerTrans->Get_World()._43 / (m_uLength*(m_uVerCntZ-1)));
	if (0.f > m_pPlayerTrans->Get_World()._43)
	{
		--iPlayerZ;
	}

	_int iPivotX = iPlayerX;
	_int iPivotZ = iPlayerZ;
	if (0 > iPlayerX)
	{
		iPivotX = (3 - ((-iPlayerX)%3))%3;
	}
	if (0 > iPlayerZ)
	{
		iPivotZ = (3 - ((-iPlayerZ) % 3))%3;
	}
	int _iIdx = ((iPivotZ)*3)%9;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pCloud[_iIdx]->Set_Trans(_vec3((int)(m_uLength*(m_uVerCntX-1))*(-1+j), 
										-5000, (int)(m_uLength*(m_uVerCntZ - 1))*(iPlayerZ-1+i)));
			m_pCloud[_iIdx]->Render_Object();
			_iIdx = (_iIdx+1)%9;
		}
	}

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pCloud[_iIdx]->Set_Trans(_vec3((int)(m_uLength*(m_uVerCntX - 1))*( - 1 + j),
				5000, (int)(m_uLength*(m_uVerCntZ - 1))*(iPlayerZ - 1 + i)));
			m_pCloud[_iIdx]->Render_Object();
			_iIdx = (_iIdx + 1) % 9;
		}
	}
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CCloud_Locater::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/


	Engine::CGameObject::Free();

	for (int i = 0; i < 9; ++i)
	{
		Safe_Release(m_pCloud[i]);
		Safe_Release(m_pCloudRoof[i]);
	}

}


HRESULT CCloud_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	for (int i = 0; i < 9; ++i)
	{
		m_pCloud[i] = CCloud_Parts::Create(m_pGraphicDev);
		m_pCloud[i]->Set_Height(1000.f, 255);
	}
	for (int i = 0; i < 9; ++i)
	{
		m_pCloudRoof[i] = CCloud_Parts::Create(m_pGraphicDev);
		m_pCloudRoof[i]->Set_Height(1000.f, 255);
		m_pCloudRoof[i]->Set_RotationReverse();
		
	}

	for (int i = 0; i < 3; ++i)
	{
		m_pCloud[i]->Weld_Edge(m_pCloud[((i + 1) % 3)], true);
		m_pCloud[3+i]->Weld_Edge(m_pCloud[(3+((i + 1) % 3))], true);
		m_pCloud[6+i]->Weld_Edge(m_pCloud[(6+((i + 1) % 3))], true);

		m_pCloud[((i + 1) % 3)*3        ]->Weld_Edge(m_pCloud[i*3    ], false);
		m_pCloud[(1 + ((i + 1) % 3) * 3)]->Weld_Edge(m_pCloud[1 + i*3], false);
		m_pCloud[(2 + ((i + 1) % 3) * 3)]->Weld_Edge(m_pCloud[2 + i*3], false);


		m_pCloudRoof[((i + 1) % 3)	    ]->Weld_Edge(m_pCloudRoof[i], true);
		m_pCloudRoof[(3 + ((i + 1) % 3))]->Weld_Edge(m_pCloudRoof[3 + i], true);
		m_pCloudRoof[(6 + ((i + 1) % 3))]->Weld_Edge(m_pCloudRoof[6 + i], true);

		m_pCloudRoof[i * 3]->Weld_Edge(m_pCloudRoof[((i + 1) % 3) * 3], false);
		m_pCloudRoof[1 + i * 3]->Weld_Edge(m_pCloudRoof[(1 + ((i + 1) % 3) * 3)], false);
		m_pCloudRoof[2 + i * 3]->Weld_Edge(m_pCloudRoof[(2 + ((i + 1) % 3) * 3)], false);
	}

	return S_OK;
}

CCloud_Locater* CCloud_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCloud_Locater*		pInstance = new CCloud_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

