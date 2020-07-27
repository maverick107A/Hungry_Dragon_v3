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
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 30.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 30.0f;


	m_pTransform->m_vScale.x *= 10.f;
	m_pTransform->m_vScale.y *= 10.f;
	m_pTransform->m_vScale.z *= 10.f;

	return S_OK;
}

int CChase_Monster::Update_Object(const float & fTimeDelta)
{

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
	else
	{
		m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * 15.f));
	
		return 0;
	}

	return m_iEvent;
}

void CChase_Monster::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

HRESULT CChase_Monster::Add_Component(void)
{
	return E_NOTIMPL;
}



CChase_Monster * CChase_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChase_Monster*		pInstance = new CChase_Monster(pGraphicDev);

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