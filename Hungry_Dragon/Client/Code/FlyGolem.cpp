#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "FlyGolem.h"


CFlyGolem::CFlyGolem(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CFlyGolem::~CFlyGolem(void)
{
}

HRESULT CFlyGolem::Ready_Object(void)
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

int CFlyGolem::Update_Object(const float & fTimeDelta)
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





	//if (m_eState == MONSTER_ACTIVATE && m_eState != MONSTER_DEACTIVATE)
	//{
	//	vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
	//	m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * m_fSpeed));
	//	m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
	//}

	return m_iEvent;
}

void CFlyGolem::Render_Object(void)
{
	m_fAngle += 0.5f;

	if (m_fAngle > 6.28319)
	{
		m_fAngle = 0;
	}

	if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
	{
		m_pTransform->Get_Info(Engine::INFO_POS, &m_vLeftArmPos);
		m_pTransform->Get_Info(Engine::INFO_POS, &m_vRightArmPos);
	}


	m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);



	// ¿À¸¥ÆÈ
	m_pTransform->Set_Scale(5);
	m_vLeftArmPos = { m_vLeftArmPos.x + (sinf(m_fAngle) * 10)  ,m_vLeftArmPos.y - 5.f , m_vLeftArmPos.z + (cosf(m_fAngle) * 10) };
	m_pTransform->Set_Trans(&m_vLeftArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferChrystalMeshCom->Render_Buffer();

	// ¿Þ? ÆÈ
	m_pTransform->Set_Scale(5);
	m_vRightArmPos = { m_vRightArmPos.x - (sinf(m_fAngle) * 10)  ,m_vRightArmPos.y - 5.f , m_vRightArmPos.z - (cosf(m_fAngle) * 10) };
	m_pTransform->Set_Trans(&m_vRightArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferChrystalMeshCom->Render_Buffer();



	// ¸öÃ¼
	m_pTransform->Set_Trans(&m_vBodyPos);
	m_pTransform->Set_Scale(8);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferChrystalMeshCom->Render_Buffer();

	// ¸öÃ¼
	m_vBombPos = { m_vBodyPos.x ,m_vBodyPos.y - 20.f ,m_vBodyPos.z };
	m_pTransform->Set_Trans(&m_vBombPos);
	m_pTransform->Set_Scale(8);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTransform->Set_Trans(&m_vBodyPos);

	m_pBufferMeshCom->Render_Buffer();


	Engine::CMonsterMain::Render_Object();
}

HRESULT CFlyGolem::Add_Component(void)
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

void CFlyGolem::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CFlyGolem * CFlyGolem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFlyGolem*		pInstance = new CFlyGolem(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CFlyGolem::Free(void)
{

	Engine::CMonsterMain::Free();
}
