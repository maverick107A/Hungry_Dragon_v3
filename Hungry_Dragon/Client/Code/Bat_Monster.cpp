#include "stdafx.h"
#include "Export_Function.h"

#include "Bat_Monster.h"


CBat_Monster::CBat_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CBat_Monster::~CBat_Monster(void)
{
}

HRESULT CBat_Monster::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();

	m_fSpeed = 50.f;
	m_eState = MONSTER_REBORN;
	
	
	m_tFrame.fStartFrame = 0.f;
	m_tFrame.fMaxFrame   = 6.f;
	m_tFrame.fFrameSpeed = 1.5f;
	m_fHeight = 0.f;


	m_fSpeed = 5.f;
	m_fMonster_MaxHP = 100.f;
	m_fMonster_HP = 100.f;
	m_fScale = 1.f;
	m_fMaxScale = 1.f;
	m_fDamaged = 10.f;

	return S_OK;
}

int CBat_Monster::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = m_fMonster_MaxHP;
		m_fScale = m_fMaxScale;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	if (m_eState != MONSTER_DEACTIVATE)
	{		
		D3DXVECTOR3 vCaveDir = { 0.f , 0.f ,-m_fSpeed };
		m_pTransform->Add_Trans(&vCaveDir);
	}

	// Y ºôº¸µå

	// D3DXMATRIX		matView;
	// m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	// D3DXMatrixInverse(&matView, NULL, &matView);
	// m_pTransform->m_matWorld._11 = matView._11;
	// m_pTransform->m_matWorld._13 = matView._13;
	// m_pTransform->m_matWorld._31 = matView._31;
	// m_pTransform->m_matWorld._33 = matView._33;

	// X ºôº¸µå

	// D3DXMATRIX		matView;
	// m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	// D3DXMatrixInverse(&matView, NULL, &matView);
	// m_pTransform->m_matWorld._22 = matView._22;
	// m_pTransform->m_matWorld._23 = matView._23;
	// m_pTransform->m_matWorld._32 = matView._32;
	// m_pTransform->m_matWorld._33 = matView._33;

	// ¿ùµå ºôº¸µå

	D3DXMatrixIdentity(&matBilboard);
	D3DXMATRIX		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matView *  m_pTransform->m_matWorld;


	Update_Animation(fTimeDelta);
	return m_iEvent;
}

void CBat_Monster::Render_Object(void)
{	
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	m_pTextureCom->Set_Texture((int)m_tFrame.fStartFrame);
	m_pBufferBoradCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
	
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


}

HRESULT CBat_Monster::Add_Component(void)
{

	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Buffer", pComponent);

	
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);


	return S_OK;
}

void CBat_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}

void CBat_Monster::Update_Animation(const float & fTimeDelta)
{
	m_tFrame.fStartFrame += m_tFrame.fMaxFrame * fTimeDelta * m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame)
	{
		m_tFrame.fStartFrame = 0.f;
	}
}

CBat_Monster * CBat_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBat_Monster*		pInstance = new CBat_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CBat_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}
