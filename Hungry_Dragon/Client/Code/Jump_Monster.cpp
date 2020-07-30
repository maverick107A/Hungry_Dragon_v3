#include "stdafx.h"
#include "Export_Function.h"


#include "Jump_Monster.h"

CJump_Monster::CJump_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CJump_Monster::~CJump_Monster(void)
{
}

HRESULT CJump_Monster::Ready_Object(void)
{

	CMonster::Ready_Object();
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 1000.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 800.0f;

	m_pTransform->Set_Scale(0.5f);

	return S_OK;
}

int CJump_Monster::Update_Object(const float & fTimeDelta)
{
	CMonster::Update_Object(fTimeDelta);


	if (m_bActivate)
	{
		if (fDistance < 3 || m_bDead)
		{
			m_pTransform->Set_Trans(&m_vPlayerPos);
			Dead_Monster(fTimeDelta);
		}
		else
		{
			D3DXVECTOR3 _vPlayerPos = { m_vPlayerPos.x ,  0.f , m_vPlayerPos.z };
			m_pTransform->Chase_Target(&_vPlayerPos, (fTimeDelta * 20.f));

			if (!m_bJump_check)
			{
				m_bJump_check = true;
				m_fJumpSpeed = m_fJumpPower;
			}
			else
			{
				Jump(fTimeDelta);
				return 0;
			}
		}

	}
	else
		Ride_Terrain();



	return m_iEvent;
}

void CJump_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
}

CJump_Monster * CJump_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CJump_Monster*		pInstance = new CJump_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CJump_Monster::Free(void)
{
	CMonster::Free();
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

	if (vMonsterPos.y < 0)
	{
		Ride_Terrain();
		m_bJump_check = false;
	}

}
