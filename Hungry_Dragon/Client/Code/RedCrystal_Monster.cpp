#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "RedCrystal_Monster.h"
#include "Ingame_Flow.h"

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

	switch (rand() % 4)
	{
	case 0:
		m_eType = Engine::CMonsterMain::BUFF_MP; // ÆÄ¶û
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fFirstFrame = 0.f;
		m_tFrame.fMaxFrame = 14.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 1:
		m_eType = Engine::CMonsterMain::BUFF_HP;
		m_tFrame.fStartFrame = 16.f;
		m_tFrame.fFirstFrame = 16.f;
		m_tFrame.fMaxFrame = 29.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 2:
		m_eType = Engine::CMonsterMain::BUFF_EXP;
		m_tFrame.fStartFrame = 31.f;
		m_tFrame.fFirstFrame = 31.f;
		m_tFrame.fMaxFrame = 44.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 3:
		m_eType = Engine::CMonsterMain::BUFF_SP;
		m_tFrame.fStartFrame = 46.f;
		m_tFrame.fFirstFrame = 46.f;
		m_tFrame.fMaxFrame = 59.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	}

	return S_OK;
}

int CRedCrystal_Monster::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pAuraTransform->Set_Trans(&m_vFirstPos);

		m_pTransform->Set_Scale(m_fMaxScale);
		m_pAuraTransform->Set_Scale(m_fMaxScale * 5);
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


	if (m_eType != CMonsterMain::BUFF_NONE)
	{
		//m_pAuraTransform->m_matWorld = m_pTransform->m_matWorld;
		m_vAuraPos = m_pTransform->m_vInfo[Engine::INFO_POS];
		m_pAuraTransform->Set_Trans(&m_vAuraPos);

		//¿ùµå ºôº¸µå
		D3DXMATRIX		matView;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
		D3DXMatrixInverse(&matView, NULL, &matView);
		m_pAuraTransform->m_matWorld = matView *  m_pAuraTransform->m_matWorld;		
	}

	Update_Animation(fTimeDelta);

	return m_iEvent;
}

void CRedCrystal_Monster::Render_Object(void)
{
	if (m_eState != MONSTER_SUICIDE)
	{
		m_fAngle += 0.25f;
		m_fLeft_Angle += 0.5f;
		if (m_fAngle > 6.28319f)
		{
			m_fAngle = 0;
		}



		CIngame_Flow::GetInstance()->Set_MaskColor(5);
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


		m_pTransform->Set_Trans(&m_vBodyPos);


		if (m_eType != CMonsterMain::BUFF_NONE)
		{
			m_pAuraTransform->Set_Transform(m_pGraphicDev);
			m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pAuraTextureCom->Set_Texture((int)m_tFrame.fStartFrame);
			m_pBufferBoradCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
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

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BoardBuffer", pComponent);


	pComponent = m_pAuraTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Test_Aura"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_AuraTexture", pComponent);

	FAILED_CHECK(Register_Component<Engine::CTransform>(&m_pAuraTransform, ID_DYNAMIC, L"Com_AuraTransform"));


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

void CRedCrystal_Monster::Update_Animation(const float & fTimeDelta)
{
	m_tFrame.fStartFrame += m_tFrame.fMaxFrame * fTimeDelta * m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame)
	{
		m_tFrame.fStartFrame = m_tFrame.fFirstFrame;
	}
}

void CRedCrystal_Monster::Free(void)
{

	Engine::CMonsterMain::Free();
}
