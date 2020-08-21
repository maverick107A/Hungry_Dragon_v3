#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem_Body.h"


CGiantGolem_Body::CGiantGolem_Body(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem_Body::~CGiantGolem_Body(void)
{
}

HRESULT CGiantGolem_Body::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 100.f;
	m_fMaxScale = 1000.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CGiantGolem_Body::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_vFirstPos = { 19200.f ,  -1500.f  ,  19200.f };
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_pTransform->m_vScale.y += 300;
		m_fMonster_HP = 100.f;
		m_fScale = 15.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	if (m_pTransform->m_vInfo[Engine::INFO_POS].y < 3500.f)
	{
		m_vBodyPos = { 0.f  , 10.f  , 0.f };
		m_pTransform->Add_Trans(&m_vBodyPos);
	}


	return m_iEvent;
}

void CGiantGolem_Body::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// ¸öÃ¼
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

}

HRESULT CGiantGolem_Body::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_GOLEMBODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);
	

	return S_OK;
}

void CGiantGolem_Body::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CGiantGolem_Body * CGiantGolem_Body::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGiantGolem_Body*		pInstance = new CGiantGolem_Body(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CGiantGolem_Body::Free(void)
{

	Engine::CMonsterMain::Free();
}
