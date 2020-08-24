#include "stdafx.h"
#include "Export_Function.h"

#include "Terrain_Locater.h"
#include "Jump_Monster.h"

CJump_Monster::CJump_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CMonsterMain(pGraphicDev)
{
}

CJump_Monster::~CJump_Monster(void)
{
}

HRESULT CJump_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 100.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 5.f;
	m_fMaxScale = 5.f;
	m_fDamaged = 5.f;
	m_eState = MONSTER_REBORN;
	m_tDeadColor = D3DXCOLOR(0.96f, 0.96f, 0.86f, 1.f);

	return S_OK;
}

int CJump_Monster::Update_Object(const float & fTimeDelta)
{

	m_ptempTerrain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerrain->Get_TerrainArrEntry();

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		m_pTransform->Set_Scale(m_fMaxScale);

		m_fMonster_HP = 100.f;
		m_fScale = 10.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	if (m_eState == MONSTER_ACTIVATE)
	{
		D3DXVECTOR3 vPos;
		m_vPlayerPos = { m_vPlayerPos.x , 0 , m_vPlayerPos.z };

		m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);

		m_vBodyPos = { m_vBodyPos.x , 0 , m_vBodyPos.z };

		m_vPos = m_vPlayerPos - m_vBodyPos;
		vPos = m_vPlayerPos - m_vBodyPos;
		D3DXVec3Normalize(&vPos, &vPos);
		m_vLookPos = { 0.f, 0.f ,1.f };

		m_fAngle = acosf(D3DXVec3Dot(&vPos, &m_vLookPos));
		
		if (vPos.x < 0)
			m_fAngle *= -1;

		m_pTransform->m_vAngle.y = m_fAngle;

		if(!m_bJump_check)
		{
			m_vChasePos = { m_vPlayerPos.x ,  0.f , m_vPlayerPos.z };
			m_fJumpSpeed = m_fJumpPower;
			m_bJump_check = true;
		}
	
	}


	if (m_bJump_check)
	{
		m_pTransform->Chase_Target(&m_vChasePos, (fTimeDelta * m_fSpeed));
		Jump(fTimeDelta);
	}

	return m_iEvent;
}

void CJump_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CJump_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	//

	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_RABBIT"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"BUFFER_RABBIT", pComponent);

	return S_OK;
}


void CJump_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}



CJump_Monster * CJump_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CJump_Monster*		pInstance = new CJump_Monster(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}





void CJump_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}





void CJump_Monster::Jump(const float& fTimeDelta)
{
	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	m_fJumpSpeed -= m_fAccel;

	if (m_fJumpSpeed < -m_fJumpPower)
	{
		m_fJumpSpeed = -m_fJumpPower;
	}
	D3DXVECTOR3	vMovePos = { 0.f, m_fJumpSpeed, 0.f };

	m_pTransform->Add_Trans(&vMovePos);

	m_fFirstY = Ride_Terrain();

	if (vMonsterPos.y < m_fFirstY)
	{
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		m_bJump_check = false;
	}

}
