#include "stdafx.h"
#include "NormalBullet.h"
#include "Export_Function.h"

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

	m_pTransform->m_vScale.x *=  5.f;
	m_pTransform->m_vScale.y *=  5.f;
	m_pTransform->m_vScale.z *=  5.f;

//	Dead_Bullet();

	return S_OK;
}

int CNormal_Bullet::Update_Object(const float & fTimeDelta)
{
	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_bFirst = false;
	}
	D3DXVECTOR3	vBulletPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vBulletPos);

	CBullet::Update_Object(fTimeDelta);

	m_pTransform->Chase_Target(&m_vPlayerPos, (fTimeDelta * 100.f));


	D3DXVECTOR3 Dir = vBulletPos - m_vPlayerPos;

	float fDistance = D3DXVec3Length(&Dir);
	if (fDistance < 11)
	{
		m_bFirst = true;
		return BULLET_DEAD;
	}
	

	return 0;
}

void CNormal_Bullet::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}

HRESULT CNormal_Bullet::Add_Component(void)
{
	return S_OK;
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
