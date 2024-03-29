#include "stdafx.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Horizon_Bat_Monster.h"


CHorizonBat_Monster::CHorizonBat_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CHorizonBat_Monster::~CHorizonBat_Monster(void)
{
}

HRESULT CHorizonBat_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();

	m_eState = MONSTER_REBORN;
	
	
	if (m_RedBat)
	{
		m_tFrame.fFirstFrame = 13.f;
		m_tFrame.fStartFrame = 13.f;
		m_tFrame.fMaxFrame = 25.f;
		m_tFrame.fFrameSpeed = 1.5f;
	}
	else
	{
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fFirstFrame = 0.f;

		m_tFrame.fMaxFrame   = 12.f;
		m_tFrame.fFrameSpeed = 1.5f;
	}
	m_fHeight = 0.f;
	m_fSpeed = 0.3f;
	m_fMonster_MaxHP = 100.f;
	m_fMonster_HP = 100.f;
	m_fScale = 1.f;
	m_fMaxScale = 3.f;
	m_fDamaged = 10.f;
	m_eVariation = MONSTER_HORIZONBAT;

	m_fDead_Range = 5000.f;
	return S_OK;
}

int CHorizonBat_Monster::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = m_fMonster_MaxHP;
		m_fScale = m_fMaxScale;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}

	// 파티클만 취급 안하는 업데이트 만들어
	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta) || CIngame_Flow::GetInstance()->Get_StageID() != CIngame_Flow::STAGE_CAVE_TWO)
	{
		m_eState = MONSTER_REBORN;
		m_iEvent = CAVEHORIZONBAT_DEAD;
		return m_iEvent;
	}

	if (m_eState != MONSTER_DEACTIVATE)
	{		
		D3DXVECTOR3 vCaveDir = { 0.f , 0.f , -m_fSpeed };
		m_pTransform->Add_Trans(&vCaveDir);
	}


	D3DXMatrixIdentity(&matBilboard);
	D3DXMATRIX		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matView *  m_pTransform->m_matWorld;


	Update_Animation(fTimeDelta);
	return m_iEvent;
}

void CHorizonBat_Monster::Render_Object(void)
{	
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);

	m_pTextureCom->Set_Texture((int)m_tFrame.fStartFrame);
	m_pBufferBoradCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();


	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

HRESULT CHorizonBat_Monster::Add_Component(void)
{

	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Buffer", pComponent);

	
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_HrizonBat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);


	return S_OK;
}

void CHorizonBat_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

void CHorizonBat_Monster::Update_Animation(const float & fTimeDelta)
{
	m_tFrame.fStartFrame += m_tFrame.fMaxFrame * fTimeDelta * m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame)
	{
		m_tFrame.fStartFrame = m_tFrame.fFirstFrame;
	}
}

CHorizonBat_Monster * CHorizonBat_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev, bool _bRed)
{
	CHorizonBat_Monster*		pInstance = new CHorizonBat_Monster(pGraphicDev);
	pInstance->Set_Red(_bRed);


	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CHorizonBat_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}
