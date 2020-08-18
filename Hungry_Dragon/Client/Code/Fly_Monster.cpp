 #include "stdafx.h"
#include "Fly_Monster.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
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

	return S_OK;
}

int CFly_Monster::Update_Object(const float & fTimeDelta)
{

	m_ptempTerain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerain->Get_Terrain();

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + m_fHeight; ;
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
			m_fShotingLate += fTimeDelta;
			if (m_fShotingLate > 0.3f)
			{
				m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + m_fHeight;
				Shooting();
				m_fShotingLate = 0;
			}
		
	}
	else
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain() + m_fHeight;

	return m_iEvent;
}

void CFly_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(2);
	m_pBufferCubeCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CFly_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCubeCom = dynamic_cast<Engine::CTexture_Cube*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_BoxHead"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);


	return S_OK;
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
