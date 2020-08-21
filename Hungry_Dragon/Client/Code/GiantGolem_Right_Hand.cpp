#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem_Right_Hand.h"


CGiantGolem_Right_Hand::CGiantGolem_Right_Hand(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem_Right_Hand::~CGiantGolem_Right_Hand(void)
{
}

HRESULT CGiantGolem_Right_Hand::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 500;
	m_fMaxScale = 500;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CGiantGolem_Right_Hand::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{

		m_ArmParts->Get_Transform()->Get_Info(Engine::INFO_POS, &m_vArmPos);
		m_vAddPos = { 0.f , -1200.f  , 0.f };
		m_vArmPos += m_vAddPos;
		m_pTransform->Set_Trans(&m_vArmPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = 100.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;

	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	m_ArmParts->Get_Transform()->Get_Info(Engine::INFO_POS, &m_vArmPos);
	m_vArmPos += m_vAddPos;
	m_pTransform->Set_Trans(&m_vArmPos);

	return m_iEvent;
}

void CGiantGolem_Right_Hand::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);


	m_pTransform->m_vAngle.y += 2.8f;
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferChrystalMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
	m_pTransform->m_vAngle.y -= 2.8f;
	

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);;

}

HRESULT CGiantGolem_Right_Hand::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferChrystalMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_RIGHTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"RIGHTHAND_Buffer", pComponent);

	return S_OK;
}

void CGiantGolem_Right_Hand::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CGiantGolem_Right_Hand * CGiantGolem_Right_Hand::Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CMonsterMain* pObject)
{
	CGiantGolem_Right_Hand*		pInstance = new CGiantGolem_Right_Hand(pGraphicDev);
	pInstance->Set_Parent_Parts(pObject);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CGiantGolem_Right_Hand::Free(void)
{

	Engine::CMonsterMain::Free();
}
