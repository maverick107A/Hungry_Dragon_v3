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
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 1000.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 600.0f;


	m_pTransform->Set_Scale(0.5f);

	return S_OK;
}

int CRun_Monster::Update_Object(const float & fTimeDelta)
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
			m_pTransform->Chase_Target(&vPlayerPos, -(fTimeDelta * 30.f));
		}
	}


	return m_iEvent;
}

void CRun_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
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
