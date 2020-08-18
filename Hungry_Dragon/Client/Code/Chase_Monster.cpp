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

	return S_OK;
}

int CChase_Monster::Update_Object(const float & fTimeDelta)
{

	m_ptempTerain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerain->Get_Terrain();

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
		vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
		m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * m_fSpeed));
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();

	}
	else
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
	return m_iEvent;
}

void CChase_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferCubeCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CChase_Monster::Add_Component(void)
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
