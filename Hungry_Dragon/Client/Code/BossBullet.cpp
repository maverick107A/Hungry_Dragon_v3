#include "stdafx.h"
#include "BossBullet.h"
#include "Export_Function.h"
#include "Export_Function.h"
#include "BulletMain.h"


CBoss_Bullet::CBoss_Bullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CBulletMain(pGraphicDev)
{
}

CBoss_Bullet::~CBoss_Bullet(void)
{
}

HRESULT CBoss_Bullet::Ready_Object(void)
{

	Engine::CBulletMain::Ready_Object();
	Add_Component();

	m_pTransform->m_vInfo[Engine::INFO_POS].x = m_vFirstPos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = m_vFirstPos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = m_vFirstPos.z;

	m_tFrame.fStartFrame = 0.f;
	m_tFrame.fMaxFrame = 12.f;
	m_tFrame.fFrameSpeed = 1.5f;

	m_eState = IDLE_BULLET;
	m_preState = IDLE_BULLET;
	m_pTransform->m_vAngle.x += D3DX_PI;


	return S_OK;
}

int CBoss_Bullet::Update_Object(const float & fTimeDelta)
{
	Engine::CBulletMain::Update_Object(fTimeDelta);


	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(1500.f);
		m_bFirst = false;
		m_iEvent = 0;
		m_eState = IDLE_BULLET;
		

		CGameObject* pPlayer = ((Engine::CLayer*)(Get_Parent()))->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
		Engine::CTransform* pPlayerTransformCom = static_cast<Engine::CTransform*>(pPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));

		pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);
		
		m_FirstPos = m_vPlayerPos - m_pTransform->m_vInfo[Engine::INFO_POS];

		m_pTransform->Compute_LookAtTarget(&m_vPlayerPos);
	}

	

	if (m_eState == IDLE_BULLET)
	{
		m_pTransform->Dir_Fly(&m_FirstPos, (fTimeDelta * 1500.f));
		m_pTransform->Chase_Rotaion(&m_vPlayerPos);	
	}
	else if (m_eState == DEAD_BULLET)
	{
		m_bFirst = true;
		Dead_Bullet();
	}


	D3DXVECTOR3 Dir = m_pTransform->m_vInfo[Engine::INFO_POS] - m_vPlayerPos;
	m_fDistance = D3DXVec3Length(&Dir);


	if (m_fDistance < 5)
	{
		m_eState = DEAD_BULLET;
	}



	State_Change();
	return m_iEvent;
}

void CBoss_Bullet::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferMeshCom->Render_Buffer();

}

HRESULT CBoss_Bullet::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_RIGHTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"RIGHTHAND_Buffer", pComponent);



	return S_OK;
}

void CBoss_Bullet::State_Change()
{
	if (m_preState != m_eState && m_preState != DEAD_BULLET)
	{
		m_preState = m_eState;
	}

}

CBoss_Bullet * CBoss_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBoss_Bullet*		pInstance = new CBoss_Bullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


void CBoss_Bullet::Free(void)
{
	Engine::CBulletMain::Free();
}
