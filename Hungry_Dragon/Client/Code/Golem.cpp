#include "stdafx.h"
#include "Export_Function.h"

#include "Golem.h"


CGolem::CGolem(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGolem::~CGolem(void)
{
}

HRESULT CGolem::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 15.f;
	m_fMaxScale = 15.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;
	return S_OK;
}

int CGolem::Update_Object(const float & fTimeDelta)
{
	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		m_pTransform->Set_Scale(m_fMaxScale);

		m_fMonster_HP = 100.f;
		m_fScale = 15.f;

		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}




	if (m_eState == MONSTER_ACTIVATE && m_eState != MONSTER_DEACTIVATE)
	{
		vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
		m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * m_fSpeed));
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
	}

	return m_iEvent;
}

void CGolem::Render_Object(void)
{

	m_pTransform->Get_Info(Engine::INFO_POS, &m_vLeftArmPos);
	m_pTransform->Get_Info(Engine::INFO_POS, &m_vRightArmPos);
	m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);


	if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
	{
		// ¿À¸¥ÆÈ
		m_pTransform->Set_Scale(3);
		m_vLeftArmPos.x += 20;
		m_pTransform->Set_Trans(&m_vLeftArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);	
	}

	m_pBufferMeshCom->Render_Buffer();

	if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
	{	// ¿Þ? ÆÈ
		m_pTransform->Set_Scale(3);
		m_vRightArmPos.x -= 20;
		m_pTransform->Set_Trans(&m_vRightArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);
	}

	m_pBufferMeshCom->Render_Buffer();



	// ¸öÃ¼
	m_pTransform->Set_Trans(&m_vBodyPos);
	m_pTransform->Set_Scale(8);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferMeshCom->Render_Buffer();



	Engine::CMonsterMain::Render_Object();
}

HRESULT CGolem::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_ROCKMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);


	return S_OK;
}

void CGolem::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CGolem * CGolem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGolem*		pInstance = new CGolem(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CGolem::Free(void)
{

	Engine::CMonsterMain::Free();
}
