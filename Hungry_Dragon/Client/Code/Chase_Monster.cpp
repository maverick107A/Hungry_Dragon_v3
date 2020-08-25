#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "Chase_Monster.h"

CChase_Monster::CChase_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CChase_Monster::~CChase_Monster(void)
{
}

HRESULT CChase_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();

	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP    = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 5.f;
	m_fMaxScale = 5.f;
	m_fDamaged		 = 5.f;
	m_eState = MONSTER_REBORN;
	m_eVariation = MONSTER_CHASE;
	m_tDeadColor = D3DXCOLOR(0.97f, 0.63f, 0.58f, 1.f);

	return S_OK;
}

int CChase_Monster::Update_Object(const float & fTimeDelta)
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



	if(MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}




	if (m_eState == MONSTER_ACTIVATE && m_eState != MONSTER_DEACTIVATE)
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



		vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
		m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * m_fSpeed));
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();

	}

	return m_iEvent;
}

void CChase_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CChase_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	//

	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_PIG"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"BUFFER_PIG", pComponent);

	return S_OK;


	return S_OK;
}

void CChase_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}


CChase_Monster * CChase_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChase_Monster*		pInstance = new CChase_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CChase_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}
