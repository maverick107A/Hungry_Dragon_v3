#include "stdafx.h"
#include "Meteor_Spawner.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "Meteor_Object.h"

CMeteor_Spawner::CMeteor_Spawner(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CMeteor_Spawner::~CMeteor_Spawner(void)
{

}

HRESULT CMeteor_Spawner::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fSummonTime = 0.25f;
	m_fSummonTick = 0.f;

	m_vecObjectPool.reserve(50);
	for (int i = 0; i < 50; ++i)
	{
		m_pMeteor = CMeteor_Object::Create(m_pGraphicDev);
		m_vecObjectPool.emplace_back(m_pMeteor);
		m_pMeteor->Set_Active(false);
	}
	m_iterFinder = m_vecObjectPool.begin();
	return S_OK;
}

void CMeteor_Spawner::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CMeteor_Spawner::Update_Object(const _float& fTimeDelta)
{
	if (!m_bActive)
	{
		return 0;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	if (fTimeDelta > 1.f)
	{
		return 0;
	}

	m_fSummonTick += fTimeDelta;
	if (m_fSummonTick >= m_fSummonTime)
	{
		m_fSummonTick -= m_fSummonTime;

 		Instantiate_Meteor(_vec3(rand()%384000, 10000.f, rand()%384000));

	}

	for (auto& pObj : m_vecObjectPool)
	{
		if (pObj->Get_Active())
			pObj->Update_Object(fTimeDelta);
	}


	return 0;
}

void CMeteor_Spawner::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pGraphicDev->SetTexture(0, 0);

	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	for (auto& pObj : m_vecObjectPool)
	{
		if(pObj->Get_Active())
			pObj->Render_Object();
	}


}

void CMeteor_Spawner::Instantiate_Meteor(_vec3 & vPos)
{
	for (; m_iterFinder != m_vecObjectPool.end(); ++m_iterFinder)
	{
		if ((*m_iterFinder)->Get_Active())
		{
			continue;
		}
		break;
	}
	if (m_iterFinder == m_vecObjectPool.end())		// 풀 1프레임 지연 기준 전부 사용중
	{
		m_iterFinder = m_vecObjectPool.begin();
		return;
	}
	else
	{
		m_pMeteor = *m_iterFinder;
	}

	m_pMeteor->Set_Active(true);
	m_pMeteor->Set_Trans(vPos);
}

void CMeteor_Spawner::Free(void)
{

	Engine::CGameObject::Free();

	for (auto& pObj : m_vecObjectPool)
	{
		Safe_Release(pObj);
	}

}


HRESULT CMeteor_Spawner::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	// 메테오 세팅
	
	return S_OK;
}

CMeteor_Spawner* CMeteor_Spawner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMeteor_Spawner*		pInstance = new CMeteor_Spawner(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

