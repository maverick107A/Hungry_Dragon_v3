#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem.h"


CGiantGolem::CGiantGolem(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem::~CGiantGolem(void)
{
}

HRESULT CGiantGolem::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 100.f;
	m_fMaxScale = 1000.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CGiantGolem::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_vFirstPos = { 19200.f ,  -1500.f  ,  19200.f };
		m_pTransform->Set_Trans(&m_vFirstPos);
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

	if (m_pTransform->m_vInfo[Engine::INFO_POS].y < 3500.f)
	{
		vPlayerPos = { 0.f  , 10.f  , 0.f };
		m_pTransform->Add_Trans(&vPlayerPos);
	}
	//if (m_eState == MONSTER_ACTIVATE && m_eState != MONSTER_DEACTIVATE)
	//{
	//
	//}

	return m_iEvent;
}

void CGiantGolem::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_fAngle += 0.01f;

	if (m_fAngle > 6.28319)
	{
		m_fAngle = 0;
	}


	// ¸öÃ¼
	m_pTransform->Set_Scale(1000);
	m_pTransform->m_vScale.y += 300;
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferMeshCom->Render_Buffer();


	if (m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_DYING)
	{

		m_pTransform->Get_Info(Engine::INFO_POS, &m_vLeftArmPos);
		m_pTransform->Get_Info(Engine::INFO_POS, &m_vHeadPos);

		m_pTransform->Get_Info(Engine::INFO_POS, &m_vRightArmPos);
	}


	m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);




	// ¿À¸¥ÆÈ
	m_pTransform->Set_Scale(500);
	m_vLeftArmPos = { m_vLeftArmPos.x + 1700  ,m_vLeftArmPos.y + 800.f , m_vLeftArmPos.z };

	m_pTransform->Set_Trans(&m_vLeftArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferBodyMeshCom->Render_Buffer();


	m_pTransform->Set_Scale(500);
	m_vLeftArmPos = { m_vLeftArmPos.x - 3400  ,m_vLeftArmPos.y , m_vLeftArmPos.z };
	m_pTransform->m_vAngle.y += D3DX_PI;
	m_pTransform->Set_Trans(&m_vLeftArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTransform->m_vAngle.y -= D3DX_PI;

	m_pBufferBodyMeshCom->Render_Buffer();

	// ¿Þ? ÆÈ

	// ¿Þ? ÆÈ
	m_pTransform->Set_Scale(500);
	m_vRightArmPos = { m_vRightArmPos.x + 1700 ,m_vRightArmPos.y - 400.f  , m_vRightArmPos.z };
	m_pTransform->m_vAngle.y += 2.8f;
	m_pTransform->Set_Trans(&m_vRightArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTransform->m_vAngle.y -= 2.8f;

	m_pBufferChrystalMeshCom->Render_Buffer();

	m_pTransform->Set_Scale(500);
	m_vRightArmPos = { m_vRightArmPos.x - 3400 ,m_vRightArmPos.y  , m_vRightArmPos.z };
	m_pTransform->m_vAngle.y += 5.9f;
	m_pTransform->Set_Trans(&m_vRightArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTransform->m_vAngle.y -= 5.9f;

	m_pBufferChrystalMeshCom->Render_Buffer();

	// ¸Ó¸®
	m_pTransform->Set_Scale(200);
	m_vRightArmPos = { m_vHeadPos.x + 100.f ,m_vHeadPos.y + 700.f , m_vHeadPos.z + 100.f };
	m_pTransform->Set_Trans(&m_vRightArmPos);
	m_pTransform->Update_Component(0.01f);
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pBufferHeadMeshCom->Render_Buffer();

	m_pTransform->Set_Trans(&m_vBodyPos);


	Engine::CMonsterMain::Render_Object();
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

}

HRESULT CGiantGolem::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_GOLEMBODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);


	// buffer
	pComponent = m_pBufferChrystalMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_RIGHTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"RIGHTHAND_Buffer", pComponent);
	

	pComponent = m_pBufferBodyMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_LEFTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"LEFTHAND_Buffer", pComponent);


	// buffer
	pComponent = m_pBufferHeadMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_ROCKMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Head_Buffer", pComponent);

	

	return S_OK;
}

void CGiantGolem::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

CGiantGolem * CGiantGolem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGiantGolem*		pInstance = new CGiantGolem(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);




	return pInstance;
}

void CGiantGolem::Free(void)
{

	Engine::CMonsterMain::Free();
}
