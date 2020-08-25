 #include "stdafx.h"
#include "Fly_Monster.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "Ingame_Flow.h"
CFly_Monster::CFly_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CFly_Monster::~CFly_Monster(void)
{
}

HRESULT CFly_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fHeight = 100.f;
	m_fSpeed = 10.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 5.f;
	m_fMaxScale = 5.f;
	m_fDamaged = 5.f;
	m_eState = MONSTER_REBORN;
	m_fDetect_Range = 800.f;
	m_tDeadColor = D3DXCOLOR(0.33f, 0.07f, 0.32f, 1.f);

	return S_OK;
}

int CFly_Monster::Update_Object(const float & fTimeDelta)
{

	m_ptempTerrain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerrain->Get_TerrainArrEntry();

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(m_fMaxScale);

		if (CIngame_Flow::GetInstance()->Get_StageID() != CIngame_Flow::STAGE_SKY)
			m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + m_fHeight; ;

		m_fMonster_HP = 100.f;
		m_fScale = 10.f;
		m_pParticle = nullptr;
		m_pTransform->m_vAngle.x = (D3DX_PI * -0.5f);
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
			m_fShotingLate += fTimeDelta;

			D3DXVECTOR3 vPos;
			m_vPlayerPos = { m_vPlayerPos.x , 0 , m_vPlayerPos.z };

			m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);

			m_vBodyPos = { m_vBodyPos.x , 0 , m_vBodyPos.z };

			m_vPos = m_vPlayerPos - m_vBodyPos;
			vPos = m_vPlayerPos - m_vBodyPos;
			D3DXVec3Normalize(&vPos, &vPos);
			m_vLookPos = { 0.f, 0.f ,1.f };

			m_fAngle = acosf(D3DXVec3Dot(&vPos, &m_vLookPos));
			m_fAngle += D3DX_PI;
			if (vPos.x < 0)
				m_fAngle *= -1;

			m_pTransform->m_vAngle.y = m_fAngle;

			if (m_fShotingLate > m_fShotingDelay)
			{
				if (CIngame_Flow::GetInstance()->Get_StageID() != CIngame_Flow::STAGE_SKY)
					m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + m_fHeight; ;

				Shooting();
				m_fShotingLate = 0;
			}
		
	}


	for (int i = 0; i < MOB_END; ++i)
	{
		MOVEMENT nextFrameMovement = m_pAnimationController->Get_Movement(m_ePattern, i);
		m_pMobPartsTrans[i]->m_vAfterAngle = nextFrameMovement.vecRot;
		m_pMobPartsTrans[i]->m_vAfterPos = nextFrameMovement.vecTrans;
		m_pMobPartsTrans[i]->m_vAfterRevAngle = nextFrameMovement.vecRevolution;
		m_pMobPartsTrans[i]->m_vScale = nextFrameMovement.vecScale;
	}



	return m_iEvent;
}

void CFly_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	CIngame_Flow::GetInstance()->Set_DefaultTex();
	Animation_Render();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CFly_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferChrystalMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"FLYMOB_BODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"FLYMOB_BODY", pComponent);


	pComponent = m_pBufferBodyMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"FLYMOB_WL"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"FLYMOB_WL", pComponent);


	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"FLYMOB_WR"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"FLYMOB_WR", pComponent);


	pComponent = m_pMobPartsTrans[MOB_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LeftHandTransform", pComponent);

	pComponent = m_pMobPartsTrans[MOB_LEFTWING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightArmTransform", pComponent);
	//날개
	pComponent = m_pMobPartsTrans[MOB_RIGHTWING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightHandTransform", pComponent);


	//애니메이션 컨트롤러
	pComponent = m_pAnimationController = Engine::CAnimation_Controller::Create(MOB_END);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_AnimationController", pComponent);
	pComponent->Set_Address(this);

	//애니메이션 설정
	Preset_Animation();
	return S_OK;
}

void CFly_Monster::Preset_Animation()
{
	m_pAnimationController->Add_Animator(-1);

	m_pMobPartsTrans[MOB_RIGHTWING]->m_fDamping = 0.04f;
	m_pAnimationController->Insert_Revolute(MOBPATTERN_IDLE, MOB_RIGHTWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, D3DX_PI*0.7f, 0.f));
	m_pAnimationController->Insert_Revolute(MOBPATTERN_IDLE, MOB_RIGHTWING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, -D3DX_PI*0.7f, 0.f));
	m_pMobPartsTrans[MOB_LEFTWING]->m_fDamping = 0.04f;
	m_pAnimationController->Insert_Revolute(MOBPATTERN_IDLE, MOB_LEFTWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, -D3DX_PI* 0.7f, 0.f));
	m_pAnimationController->Insert_Revolute(MOBPATTERN_IDLE, MOB_LEFTWING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, D3DX_PI* 0.7f, 0.f));

}

void CFly_Monster::Animation_Render()
{
	D3DXMATRIX _matWorld;
	m_pMobPartsTrans[MOB_BODY]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pBufferChrystalMeshCom->Render_Buffer();


	m_pMobPartsTrans[MOB_LEFTWING]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pBufferBodyMeshCom->Render_Buffer();


	m_pMobPartsTrans[MOB_RIGHTWING]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pBufferMeshCom->Render_Buffer();
}

void CFly_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

void CFly_Monster::Shooting(void)
{
	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	Engine::Set_Bullet_LayerMap(Engine::OBJID::NORMAL_BULLET, 1, vMonsterPos);

}


CFly_Monster * CFly_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFly_Monster*		pInstance = new CFly_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CFly_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}
