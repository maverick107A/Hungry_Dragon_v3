#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "Run_Monster.h"

CRun_Monster::CRun_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CRun_Monster::~CRun_Monster(void)
{
}

HRESULT CRun_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 10.f;
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 10.f;
	m_fMaxScale = 10.f;
	m_fDamaged = 5.f;
	m_eState = MONSTER_REBORN;


	switch (rand() % 4)
	{
	case 0:
		m_eType = Engine::CMonsterMain::BUFF_MP; // �Ķ�
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

int CRun_Monster::Update_Object(const float & fTimeDelta)
{

	m_ptempTerrain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	m_pTerrain = m_ptempTerrain->Get_TerrainArrEntry();

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();


		m_vAuraPos = m_pTransform->m_vInfo[Engine::INFO_POS];
		m_pAuraTransform->Set_Trans(&m_vAuraPos);

		m_pTransform->Set_Scale(m_fMaxScale);
		m_pAuraTransform->Set_Scale(m_fMaxScale * 5);
		m_fMonster_HP = m_fMonster_MaxHP;

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

		vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
		m_pTransform->Chase_Target(&vPlayerPos, -(fTimeDelta * m_fSpeed));
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
	}



	if (m_eType != CMonsterMain::BUFF_NONE)
	{
		//m_pAuraTransform->m_matWorld = m_pTransform->m_matWorld;
		m_vAuraPos = m_pTransform->m_vInfo[Engine::INFO_POS];
		m_pAuraTransform->Set_Trans(&m_vAuraPos);

		//���� ������
		D3DXMATRIX		matView;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
		D3DXMatrixInverse(&matView, NULL, &matView);
		m_pAuraTransform->m_matWorld = matView *  m_pAuraTransform->m_matWorld;

	}

	Update_Animation(fTimeDelta);
	return m_iEvent;
}

void CRun_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(4);
	m_pBufferCubeCom->Render_Buffer();


	if (m_eType != CMonsterMain::BUFF_NONE)
	{
		m_pAuraTransform->Set_Transform(m_pGraphicDev);

		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pAuraTextureCom->Set_Texture((int)m_tFrame.fStartFrame);
		m_pBufferBoradCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	Engine::CMonsterMain::Render_Object();
}

HRESULT CRun_Monster::Add_Component(void)
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

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BoardBuffer", pComponent);


	pComponent = m_pAuraTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Test_Aura"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_AuraTexture", pComponent);

	//pComponent = m_pTransform = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);


	FAILED_CHECK(Register_Component<Engine::CTransform>(&m_pAuraTransform, ID_DYNAMIC, L"Com_AuraTransform"));

	return S_OK;
}

void CRun_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}


void CRun_Monster::Update_Animation(const float & fTimeDelta)
{
	m_tFrame.fStartFrame += m_tFrame.fMaxFrame * fTimeDelta * m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame)
	{
		m_tFrame.fStartFrame = m_tFrame.fFirstFrame;
	}
}

CRun_Monster * CRun_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRun_Monster*		pInstance = new CRun_Monster(pGraphicDev);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CRun_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}
