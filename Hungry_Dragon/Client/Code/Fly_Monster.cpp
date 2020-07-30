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
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 1000.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 600.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 600.0f;


	m_pTransform->Set_Scale(0.f);

	return S_OK;
}

int CFly_Monster::Update_Object(const float & fTimeDelta)
{

	m_fShotingLate += fTimeDelta;
	if (m_fShotingLate > 0.3f)
	{
		Shooting();
		m_fShotingLate = 0;
	}

	CMonster::Update_Object(fTimeDelta);

	if (fDistance < 3)
	{
		Dead_Monster(fTimeDelta);
	}
	else if (fDistance >= 3 && fDistance < 60)
	{
		m_pTransform->Chase_Target(&m_vPlayerPos, -(fTimeDelta * 2.f));
	}


	return m_iEvent;
}

void CFly_Monster::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(2);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CFly_Monster::Shooting(void)
{
	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	Engine::Set_Bullet_LayerMap(Engine::OBJID::NORMAL_BULLET, 1, vMonsterPos);

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
