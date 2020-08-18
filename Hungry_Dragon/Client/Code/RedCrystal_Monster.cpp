#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "RedCrystal_Monster.h"


CRedCrystal_Monster::CRedCrystal_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CRedCrystal_Monster::~CRedCrystal_Monster(void)
{
}

HRESULT CRedCrystal_Monster::Ready_Object(void)
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

int CRedCrystal_Monster::Update_Object(const float & fTimeDelta)
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
		m_pParticle = nullptr;
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
		m_pTransform->Chase_Fly_Target(&m_vPlayerPos, -(fTimeDelta * m_fSpeed));
	}

	if (m_fDistance < 30)
	{
		m_eState = MONSTER_SUICIDE;
		State_Change();
	}

	return m_iEvent;
}

void CRedCrystal_Monster::Render_Object(void)
{
	if(m_eState != MONSTER_SUICIDE)
	{ 
		m_fAngle	+= 0.25f;
		m_fLeft_Angle += 0.5f;
		if (m_fAngle > 6.28319f)
		{
			m_fAngle = 0;
		}



		// ¸öÃ¼
		m_pTransform->Set_Scale(8);
		m_pTransform->m_vScale.y += 3;
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferMeshCom->Render_Buffer();

		if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
		{
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vLeftArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vRightArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vUpArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vDownArmPos);
			m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);
		}


		// ¿À¸¥ÆÈ
		m_pTransform->Set_Scale(5);
		m_vLeftArmPos = { m_vLeftArmPos.x + (sinf(m_fAngle) * 10)  ,m_vLeftArmPos.y , m_vLeftArmPos.z + (cosf(m_fAngle) * 10) };
		m_pTransform->Set_Trans(&m_vLeftArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferMeshCom->Render_Buffer();

		// ¿Þ? ÆÈ
		m_pTransform->Set_Scale(5);
		m_vRightArmPos = { m_vRightArmPos.x - (sinf(m_fAngle) * 10)  ,m_vRightArmPos.y, m_vRightArmPos.z - (cosf(m_fAngle) * 10) };
		m_pTransform->Set_Trans(&m_vRightArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferMeshCom->Render_Buffer();


		m_pTransform->Set_Scale(5);
		m_vUpArmPos = { m_vUpArmPos.x + (sinf(m_fAngle + (D3DX_PI * 0.5f)) * 10)  ,m_vUpArmPos.y , m_vUpArmPos.z + (cosf(m_fAngle + (D3DX_PI * 0.5f)) * 10) };
		m_pTransform->Set_Trans(&m_vUpArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferMeshCom->Render_Buffer();


		m_pTransform->Set_Scale(5);
		m_vDownArmPos = { m_vDownArmPos.x - (sinf(m_fAngle + (D3DX_PI * 0.5f)) * 10)  ,m_vDownArmPos.y , m_vDownArmPos.z - (cosf(m_fAngle + (D3DX_PI * 0.5f)) * 10) };
		m_pTransform->Set_Trans(&m_vDownArmPos);
		m_pTransform->Update_Component(0.01f);
		m_pTransform->Set_Transform(m_pGraphicDev);


		m_pBufferMeshCom->Render_Buffer();

		////// ÆøÅº
		//if (m_eState == MONSTER_DEACTIVATE || m_fMonster_HP < 0)
		//{
		//	m_vBombPos = { m_vBombPos.x ,m_vBombPos.y - 20.f ,m_vBombPos.z };
		//}
		//else
		//{
		//	m_vBombPos = { m_vBodyPos.x ,m_vBodyPos.y - 20.f ,m_vBodyPos.z };
		//}
		//m_pTransform->Set_Trans(&m_vBombPos);
		//m_pTransform->Set_Scale(8);
		//m_pTransform->Update_Component(0.01f);
		//m_pTransform->Set_Transform(m_pGraphicDev);

		//m_pBufferMeshCom->Render_Buffer();

		m_pTransform->Set_Trans(&m_vBodyPos);
	}
	
	Engine::CMonsterMain::Render_Object();
}

HRESULT CRedCrystal_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer	
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_DIAMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Chrystal_Buffer", pComponent);


	return S_OK;
}

void CRedCrystal_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CRedCrystal_Monster * CRedCrystal_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRedCrystal_Monster*		pInstance = new CRedCrystal_Monster(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CRedCrystal_Monster::Free(void)
{

	Engine::CMonsterMain::Free();
}
