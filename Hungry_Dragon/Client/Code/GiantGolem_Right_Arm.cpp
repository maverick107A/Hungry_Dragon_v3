#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem_Right_Arm.h"


CGiantGolem_Right_Arm::CGiantGolem_Right_Arm(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem_Right_Arm::~CGiantGolem_Right_Arm(void)
{
}

HRESULT CGiantGolem_Right_Arm::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 500.f;
	m_fMaxScale = 500.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CGiantGolem_Right_Arm::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_BodyParts->Get_Transform()->Get_Info(Engine::INFO_POS, &m_vBodyPos);
		m_vAddPos = { 1700 , 800.f , 0.f };
		m_pTransform->Set_Trans(&m_vBodyPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = 100.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	m_BodyParts->Get_Transform()->Get_Info(Engine::INFO_POS, &m_vBodyPos);
	m_vBodyPos += m_vAddPos;
	m_pTransform->Set_Trans(&m_vBodyPos);

	return m_iEvent;
}

void CGiantGolem_Right_Arm::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);


	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferBodyMeshCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

}

HRESULT CGiantGolem_Right_Arm::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	pComponent = m_pBufferBodyMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_LEFTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"LEFTHAND_Buffer", pComponent);

	
	return S_OK;
}

void CGiantGolem_Right_Arm::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CGiantGolem_Right_Arm * CGiantGolem_Right_Arm::Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CMonsterMain* pObject)
{
	CGiantGolem_Right_Arm*		pInstance = new CGiantGolem_Right_Arm(pGraphicDev);
	pInstance->Set_Parent_Parts(pObject);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CGiantGolem_Right_Arm::Free(void)
{

	Engine::CMonsterMain::Free();
}
