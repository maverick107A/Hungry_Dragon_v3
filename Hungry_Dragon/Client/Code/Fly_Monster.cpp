#include "stdafx.h"
#include "Fly_Monster.h"
#include "Export_Function.h"

CFly_Monster::CFly_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CFly_Monster::~CFly_Monster(void)
{
}

HRESULT CFly_Monster::Ready_Object(void)
{
	CMonster::Ready_Object();
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 30.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 100.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 94.0f;


	m_pTransform->m_vScale.x *= 10.f;
	m_pTransform->m_vScale.y *= 10.f;
	m_pTransform->m_vScale.z *= 10.f;

	return S_OK;
}

int CFly_Monster::Update_Object(const float & fTimeDelta)
{
	
	

		Shooting();
	


	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	CMonster::Update_Object(fTimeDelta);

	D3DXVECTOR3	vPlayerPos;
	vPlayerPos = { m_vPlayerPos.x , 0 ,m_vPlayerPos.z };

	D3DXVECTOR3 Dir = vMonsterPos - m_vPlayerPos;

	float fDistance = D3DXVec3Length(&Dir);

	if (fDistance < 15)
	{
		Dead_Monster();
	}
	else if (fDistance >= 15 && fDistance < 60)
	{
		m_pTransform->Chase_Target(&m_vPlayerPos, -(fTimeDelta * 2.f));
	}
	else
	{
		return 0;
	}

	return m_iEvent;
}

void CFly_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}

void CFly_Monster::Shooting(void)
{
	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	Engine::Set_Bullet_LayerMap(Engine::OBJID::NORMAL_BULLET, 1 , vMonsterPos);

}


CFly_Monster * CFly_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFly_Monster*		pInstance = new CFly_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CFly_Monster::Free(void)
{
	CMonster::Free();
}
