#include "stdafx.h"

#include "Bullet.h"

#include "Export_Function.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

CBullet::~CBullet(void)
{
}

HRESULT CBullet::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int CBullet::Update_Object(const float & fTimeDelta)
{

	D3DXVECTOR3	vBulletPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vBulletPos);
	D3DXVECTOR3 Dir = vBulletPos - m_vPlayerPos;
	m_fDistance = D3DXVec3Length(&Dir);

	Engine::CGameObject::Update_Object(fTimeDelta);


	if (m_iEvent == BULLET_DEAD)
	{
		return -1;
	}


	return m_iEvent;
}

void CBullet::Render_Object(void)
{
}

void CBullet::Dead_Bullet(void)
{
	m_iEvent = BULLET_DEAD;
}

void CBullet::Set_Pos(D3DXVECTOR3 _Pos)
{
	m_pTransform->m_vInfo[Engine::INFO_POS].x = _Pos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = _Pos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = _Pos.z;
}

HRESULT CBullet::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CCubeTex*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_BoxHead"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	//m_pBufferCom

	return S_OK;
}

void CBullet::Key_Input(const float & fTimeDelta)
{
}

CBullet * CBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBullet*		pInstance = new CBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CBullet::Free(void)
{
	Engine::CGameObject::Free();
}
