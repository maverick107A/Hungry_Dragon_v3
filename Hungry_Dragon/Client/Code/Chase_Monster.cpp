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
	m_fSpeed = 50.f;

	return S_OK;
}

int CChase_Monster::Update_Object(const float & fTimeDelta)
{

	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(1);  
		m_bFirst = false;	
		m_bDead = false;
		m_iEvent = 0;
	}

	CMonster::Update_Object(fTimeDelta);


	if (m_bActivate && !m_bDead)
	{
		vPlayerPos = { m_vPlayerPos.x  , 0.f  , m_vPlayerPos.z };
		m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * m_fSpeed));
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();
		
	}
	else
	{
		
		m_pTransform->m_vInfo[Engine::INFO_POS].y = Ride_Terrain();

	}

	return m_iEvent;
}

void CChase_Monster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferCom->Render_Buffer();
	CMonster::Render_Object();
}

HRESULT CChase_Monster::Add_Component(void)
{
	return E_FAIL;
}

void CChase_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	CMonster::LateUpdate_Object(fTimeDelta);
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
