#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem_Head.h"


CGiantGolem_Head::CGiantGolem_Head(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem_Head::~CGiantGolem_Head(void)
{
}

HRESULT CGiantGolem_Head::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 200.f;
	m_fMaxScale = 200.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CGiantGolem_Head::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_BodyParts->Get_Transform()->Get_Info(Engine::INFO_POS , &m_vBodyPos);
		m_vAddPos = { 100.f , 700.f , 100.f };
		m_vBodyPos += m_vAddPos;
		m_pTransform->Set_Trans(&m_vBodyPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = 100.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	
	m_BodyParts->Get_Transform()->Get_Info(Engine::INFO_POS, &m_vBodyPos);
	m_vAddPos = { 100.f , 700.f , 100.f };
	m_vBodyPos += m_vAddPos;
	m_pTransform->Set_Trans(&m_vBodyPos);
	


	return m_iEvent;
}

void CGiantGolem_Head::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferHeadMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();


	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

}

HRESULT CGiantGolem_Head::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferHeadMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_ROCKMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Head_Buffer", pComponent);
	
	return S_OK;
}



void CGiantGolem_Head::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}



CGiantGolem_Head * CGiantGolem_Head::Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CMonsterMain* pObject)
{
	CGiantGolem_Head*		pInstance = new CGiantGolem_Head(pGraphicDev);
	pInstance->Set_Parent_Parts(pObject);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CGiantGolem_Head::Free(void)
{

	Engine::CMonsterMain::Free();
}
