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
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 128.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 0.0f;


	m_pTransform->m_vScale.x *= 10.1f;
	m_pTransform->m_vScale.y *= 10.1f;
	m_pTransform->m_vScale.z *= 10.1f;

	return S_OK;
}

int CJump_Monster::Update_Object(const float & fTimeDelta)
{
	CMonster::Update_Object(fTimeDelta);

	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);
	D3DXVECTOR3 Dir = vMonsterPos - m_vPlayerPos;
	float fDistance = D3DXVec3Length(&Dir);

	if (fDistance < 15)
	{
		Dead_Monster();
	}
	else
	{
		m_pTransform->Chase_Target(&m_vPlayerPos, (fTimeDelta * 20.f));

		if (!m_bJump_check)
		{
			D3DXVECTOR3	vMonsterPos;
			m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);
			// ÂøÁö ÁöÁ¡
			m_fFirstY = vMonsterPos.y;
			m_bJump_check = true;
			m_fJumpSpeed = 3.f;
		}
		else
		{
			Jump(fTimeDelta);


			return 0;
		}
	}

	return m_iEvent;
}

void CJump_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
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

	if (m_fJumpSpeed < -3)
	{
		m_fJumpSpeed = -3;
	}
	D3DXVECTOR3	vMovePos = { 0.f, m_fJumpSpeed, 0.f };

	m_pTransform->Add_Trans(&vMovePos);



	if (vMonsterPos.y < m_fFirstY)
	{
		m_bJump_check = false;
		vMonsterPos = { vMonsterPos.x , m_fFirstY , vMonsterPos.z };
		m_pTransform->Set_Trans(&vMonsterPos);

	}

}
