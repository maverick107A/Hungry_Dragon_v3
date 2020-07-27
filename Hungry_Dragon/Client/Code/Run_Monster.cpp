#include "stdafx.h"
#include "Export_Function.h"

#include "Run_Monster.h"

CRun_Monster::CRun_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CRun_Monster::~CRun_Monster(void)
{
}

HRESULT CRun_Monster::Ready_Object(void)
{
	CMonster::Ready_Object();
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 74.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 74.0f;


	m_pTransform->m_vScale.x *= 10.1f;
	m_pTransform->m_vScale.y *= 10.1f;
	m_pTransform->m_vScale.z *= 10.1f;

	return S_OK;
}

int CRun_Monster::Update_Object(const float & fTimeDelta)
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
		 m_pTransform->Chase_Target(&m_vPlayerPos, -(fTimeDelta * 2.f));

		return 0;
	}


	return m_iEvent;
}

void CRun_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}


CRun_Monster * CRun_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRun_Monster*		pInstance = new CRun_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CRun_Monster::Free(void)
{
	CMonster::Free();
}
