#include "stdafx.h"
#include "AshCloud_Locater.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "Cloud_Parts.h"

CAshCloud_Locater::CAshCloud_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CAshCloud_Locater::~CAshCloud_Locater(void)
{

}

HRESULT CAshCloud_Locater::Ready_Object(void)
{
	m_uVerCntX = 129;
	m_uVerCntZ = 129;
	m_uLength = 1000;		// 생성자 통해서 파츠에 넘겨주는부분이 없음, 그냥 상수 때려박은것
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

void CAshCloud_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CAshCloud_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;


	return 0;
}

void CAshCloud_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);

	
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	for (int i = 0; i < 16; ++i)
	{
		m_pCloudRoof[i]->Render_Object();
	}
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CAshCloud_Locater::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/


	Engine::CGameObject::Free();

	for (int i = 0; i < 16; ++i)
	{
		Safe_Release(m_pCloudRoof[i]);
	}

}


HRESULT CAshCloud_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	for (int i = 0; i < 16; ++i)
	{
		m_pCloudRoof[i] = CCloud_Parts::Create(m_pGraphicDev);
		m_pCloudRoof[i]->Set_Height(1000.f, 64);
		//m_pCloudRoof[i]->Set_RotationReverse();
		m_pCloudRoof[i]->Set_Trans(_vec3(-256000.f + (i%4)*128000.f, 10000.f, -256000.f + (i / 4)*128000.f));
	}

	for (int i = 0; i < 4; ++i)
	{
		m_pCloudRoof[i]->Weld_Edge(m_pCloudRoof[((i + 1) % 4)], true);
		m_pCloudRoof[4 + i]->Weld_Edge(m_pCloudRoof[(4 + ((i + 1) % 4))], true);
		m_pCloudRoof[8 + i]->Weld_Edge(m_pCloudRoof[(8 + ((i + 1) % 4))], true);
		m_pCloudRoof[12 + i]->Weld_Edge(m_pCloudRoof[(12 + ((i + 1) % 4))], true);

		m_pCloudRoof[((i + 1) % 4) * 4]->Weld_Edge(m_pCloudRoof[i * 4], false);
		m_pCloudRoof[(1 + ((i + 1) % 4) * 4)]->Weld_Edge(m_pCloudRoof[1 + i * 4], false);
		m_pCloudRoof[(2 + ((i + 1) % 4) * 4)]->Weld_Edge(m_pCloudRoof[2 + i * 4], false);
		m_pCloudRoof[(3 + ((i + 1) % 4) * 4)]->Weld_Edge(m_pCloudRoof[3 + i * 4], false);
	}

	return S_OK;
}

CAshCloud_Locater* CAshCloud_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAshCloud_Locater*		pInstance = new CAshCloud_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

