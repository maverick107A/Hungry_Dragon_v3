#include "stdafx.h"
#include "NormalBullet.h"
#include "Export_Function.h"
#include <time.h>

CNormal_Bullet::CNormal_Bullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBullet(pGraphicDev)
{
}

CNormal_Bullet::~CNormal_Bullet(void)
{
}

HRESULT CNormal_Bullet::Ready_Object(void)
{

	CBullet::Ready_Object();

	m_pTransform->m_vInfo[Engine::INFO_POS].x = m_vFirstPos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = m_vFirstPos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = m_vFirstPos.z;



	m_eState = IDLE_BULLET;
	m_preState = IDLE_BULLET;



	return S_OK;
}

int CNormal_Bullet::Update_Object(const float & fTimeDelta)
{
	CBullet::Update_Object(fTimeDelta);


	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_bFirst = false;
		m_iEvent = 0;
		m_eState = IDLE_BULLET;
		
		Engine::CTransform*		pPlayerTransformCom;
		pPlayerTransformCom = dynamic_cast<Engine::CTransform*>
		(Engine::Get_Component(L"GameLogic",
			L"TestPlayer",
			L"Com_Transform",
			Engine::ID_DYNAMIC));

		pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);

		m_FirstPos = m_vPlayerPos - m_pTransform->m_vInfo[Engine::INFO_POS];
	}

	

	if (m_eState == IDLE_BULLET)
	{
		m_pTransform->Dir_Fly(&m_FirstPos, (fTimeDelta * 100.f));
	}
	else if (m_eState == DEAD_BULLET)
	{
		m_bFirst = true;
		Dead_Bullet();
	}


	//else if (m_eState == REFLECT_BULLET)
	//{

	//	//D3DXVec3Normalize(&Dir, &Dir);
	//	m_pTransform->Add_Trans(&m_vReflDir);
	//	m_pTransform->m_vScale.x *= 0.99f;
	//	m_pTransform->m_vScale.y *= 0.99f;
	//	m_pTransform->m_vScale.z *= 0.99f;

	//if (m_fDistance < 5 || m_pTransform->m_vScale.x < 0)
	//{
	//	m_eState = DEAD_BULLET;
	//}

	//}

	//if (m_fDistance < 13)
	//{
	//	m_eState = REFLECT_BULLET;
	//	m_vReflDir = { (float(rand() % 10) - 5.f)     , (float(rand() % 10) - 5.f)  , (float(rand() % 10) - 5.f) };
	//	m_vReflDir *= 0.5f;
	//}


	D3DXVECTOR3 Dir = m_pTransform->m_vInfo[Engine::INFO_POS] - m_vPlayerPos;
	m_fDistance = D3DXVec3Length(&Dir);



	if (m_fDistance > 5000)
	{
		m_eState = DEAD_BULLET;
	}
	else if (m_fDistance < 5)
	{
		m_eState = DEAD_BULLET;
	}

	State_Change();

	return m_iEvent;
}

void CNormal_Bullet::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();
}

HRESULT CNormal_Bullet::Add_Component(void)
{
	return E_NOTIMPL;
}

void CNormal_Bullet::State_Change()
{
	if (m_preState != m_eState && m_preState != DEAD_BULLET)
	{


		m_preState = m_eState;
	}

}

CNormal_Bullet * CNormal_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNormal_Bullet*		pInstance = new CNormal_Bullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CNormal_Bullet::Free(void)
{
	CBullet::Free();
}
