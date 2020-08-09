#include "stdafx.h"
#include "Export_Function.h"


#include "Jump_Monster.h"

CJump_Monster::CJump_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CMonsterMain::(pGraphicDev)
{
}

CJump_Monster::~CJump_Monster(void)
{
}

HRESULT CJump_Monster::Ready_Object(void)
{

	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 20.f;
	m_eState = MONSTER_REBORN;

	return S_OK;
}

int CJump_Monster::Update_Object(const float & fTimeDelta)
{

	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		m_pTransform->Set_Scale(1);
		//m_bFirst = false;	
		//m_bDead = false;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;

	}

	Engine::CMonsterMain::Update_Object(fTimeDelta);

	if (m_eState == MONSTER_ACTIVATE)
	{
		if(!m_bJump_check)
		{
			m_vChasePos = { m_vPlayerPos.x ,  0.f , m_vPlayerPos.z };
			m_fJumpSpeed = m_fJumpPower;
			m_bJump_check = true;
		}

		if(m_bJump_check)
		{
			m_pTransform->Chase_Target(&m_vChasePos, (fTimeDelta * m_fSpeed));
			Jump(fTimeDelta);
		}		
	}
	else
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();

	return m_iEvent;
}

void CJump_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(5);
	m_pBufferCom->Render_Buffer();
	Engine::CMonsterMain::Render_Object();
}

HRESULT CJump_Monster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Cube*>
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
void CJump_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}
CJump_Monster * CJump_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev, D3DXVECTOR3 _pos)
{
	CJump_Monster*		pInstance = new CJump_Monster(pGraphicDev);

	pInstance->Set_Pos(_pos);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CJump_Monster::Free(void)
{
	Engine::CMonsterMain::Free();
}

void CJump_Monster::Jump(const float& fTimeDelta)
{
	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	m_fJumpSpeed -= m_fAccel;

	if (m_fJumpSpeed < -m_fJumpPower)
	{
		m_fJumpSpeed = -m_fJumpPower;
	}
	D3DXVECTOR3	vMovePos = { 0.f, m_fJumpSpeed, 0.f };

	m_pTransform->Add_Trans(&vMovePos);

	m_fFirstY = Ride_Terrain();

	if (vMonsterPos.y < m_fFirstY)
	{
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		m_bJump_check = false;
	}

}
