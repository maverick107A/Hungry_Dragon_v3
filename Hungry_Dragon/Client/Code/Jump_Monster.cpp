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



	// t스케일에 포스를 넣었지 뭐얌 
	m_pTransform->m_vInfo[Engine::INFO_POS].x = m_vFirstPos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = m_vFirstPos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = m_vFirstPos.z;
	m_pTransform->Set_Minus_Scale(0.5f);

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
				Ride_Terrain();
				m_bJump_check = true;
				m_fJumpSpeed = m_fJumpPower;
			}
			else
			{
				m_fFirstY = m_pTransform->m_vInfo[Engine::INFO_POS].y;
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
	m_pTextureCom->Set_Texture(5);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
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

	if (vMonsterPos.y < m_fFirstY)
	{
		Ride_Terrain();
		m_bJump_check = false;
	}

}
