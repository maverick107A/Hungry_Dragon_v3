#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "FlyChaseGolem.h"


CFlyChaseGolem::CFlyChaseGolem(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CFlyChaseGolem::~CFlyChaseGolem(void)
{
}

HRESULT CFlyChaseGolem::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 150.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 15.f;
	m_fMaxScale = 15.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CFlyChaseGolem::Update_Object(const float & fTimeDelta)
{

	m_ptempTerain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerain->Get_Terrain();

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + 1000.f;
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
		m_pTransform->Chase_Fly_Target(&m_vPlayerPos, (fTimeDelta * m_fSpeed));
	}

	if (m_fDistance < 50)
	{
		m_eState = MONSTER_SUICIDE;
		State_Change();
	}

	return m_iEvent;
}

void CFlyChaseGolem::Render_Object(void)
{
	if(m_eState != MONSTER_SUICIDE)
	{ 
		m_fAngle += 0.5f;

		if (m_fAngle > 6.28319)
		{
			m_fAngle = 0;
		}



		// ��ü
		m_pTransform->Set_Scale(8);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferChrystalMeshCom->Render_Buffer();

		if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
		{
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vLeftArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vRightArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);
		}


		// ������
		m_pTransform->Set_Scale(5);
		m_vLeftArmPos = { m_vLeftArmPos.x + (sinf(m_fAngle) * 10)  ,m_vLeftArmPos.y - 5.f , m_vLeftArmPos.z + (cosf(m_fAngle) * 10) };
		m_pTransform->Set_Trans(&m_vLeftArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferChrystalMeshCom->Render_Buffer();

		// ��? ��
		m_pTransform->Set_Scale(5);
		m_vRightArmPos = { m_vRightArmPos.x - (sinf(m_fAngle) * 10)  ,m_vRightArmPos.y - 5.f , m_vRightArmPos.z - (cosf(m_fAngle) * 10) };
		m_pTransform->Set_Trans(&m_vRightArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferChrystalMeshCom->Render_Buffer();

		//// ��ź
		if (m_eState == MONSTER_DEACTIVATE || m_fMonster_HP < 0)
		{
			m_vBombPos = { m_vBombPos.x ,m_vBombPos.y - 20.f ,m_vBombPos.z };
		}
		else
		{
			m_vBombPos = { m_vBodyPos.x ,m_vBodyPos.y - 20.f ,m_vBodyPos.z };
		}
		m_pTransform->Set_Trans(&m_vBombPos);
		m_pTransform->Set_Scale(8);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);

		m_pBufferMeshCom->Render_Buffer();

		m_pTransform->Set_Trans(&m_vBodyPos);
	}
	
	Engine::CMonsterMain::Render_Object();
}

HRESULT CFlyChaseGolem::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_ROCKMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);


	// buffer
	pComponent = m_pBufferChrystalMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_CHRYSTAL"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Chrystal_Buffer", pComponent);
	


	return S_OK;
}

void CFlyChaseGolem::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CFlyChaseGolem * CFlyChaseGolem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFlyChaseGolem*		pInstance = new CFlyChaseGolem(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CFlyChaseGolem::Free(void)
{

	Engine::CMonsterMain::Free();
}