#include "stdafx.h"
#include "Cliff_Locater.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "Cliff_Object.h"

CCliff_Locater::CCliff_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CCliff_Locater::~CCliff_Locater(void)
{

}

HRESULT CCliff_Locater::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

void CCliff_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CCliff_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;


	return 0;
}

void CCliff_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	for (auto& pCliff : m_vecCliff)
	{
		pCliff->Render_Object();
	}
	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);

}

void CCliff_Locater::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/


	Engine::CGameObject::Free();

	for (auto& pCliff : m_vecCliff)
	{
		Safe_Release(pCliff);
	}

}


HRESULT CCliff_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	// 절벽 오브젝트 세팅
	for (int i = 0; i < 20; ++i)
	{
		m_vecCliff.emplace_back(CCliff_Object::Create(m_pGraphicDev));
		m_vecCliff[i]->Set_Trans(_vec3(-11400.f ,0.f, 12800.f * (i)));
		m_vecCliff[i]->Update_Object(0);
	}
	for (int i = 50; i < 70; ++i)
	{
		m_vecCliff.emplace_back(CCliff_Object::Create(m_pGraphicDev));
		m_vecCliff[i-30]->Set_Trans(_vec3(11400.f, 0.f, 12800.f * (i-50)));
		m_vecCliff[i-30]->Update_Object(0);
	}

	m_vecCliff.emplace_back(CCliff_Object::Create(m_pGraphicDev));
	m_vecCliff[40]->Set_Trans(_vec3(0.f, 0.f, 112800.f));
	m_vecCliff[40]->Update_Object(0);

	return S_OK;
}

CCliff_Locater* CCliff_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCliff_Locater*		pInstance = new CCliff_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

