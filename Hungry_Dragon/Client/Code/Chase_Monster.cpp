#include "stdafx.h"
#include "Export_Function.h"

#include "Chase_Monster.h"


CChase_Monster::CChase_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CChase_Monster::~CChase_Monster(void)
{
}

HRESULT CChase_Monster::Ready_Object(void)
{
	CMonster::Ready_Object();
	m_pTransform->m_vInfo[Engine::INFO_POS].x = m_vFirstPos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = m_vFirstPos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = m_vFirstPos.z;
	m_pTransform->Set_Scale(0.5f);

	return S_OK;
}

int CChase_Monster::Update_Object(const float & fTimeDelta)
{
	CMonster::Update_Object(fTimeDelta);
	Ride_Terrain();

	if (m_bActivate)
	{
		if (fDistance < 3 || m_bDead)
		{
			m_pTransform->Set_Trans(&m_vPlayerPos);
			Dead_Monster(fTimeDelta);
			m_bDead = true;
		}
		else if (!m_bDead)
		{
			vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
			m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * 50.f));	
		}
	}


	return m_iEvent;
}

void CChase_Monster::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

HRESULT CChase_Monster::Add_Component(void)
{
	return E_NOTIMPL;
}



CChase_Monster * CChase_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev, D3DXVECTOR3 _pos)
{
	CChase_Monster*		pInstance = new CChase_Monster(pGraphicDev);

	pInstance->Set_Pos(_pos);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CChase_Monster::Free(void)
{
	CMonster::Free();
}


float CChase_Monster::Move_Terrain(void)
{
	return 0;
}