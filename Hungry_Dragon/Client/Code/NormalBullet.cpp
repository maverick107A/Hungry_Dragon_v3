#include "stdafx.h"
#include "NormalBullet.h"
#include "Export_Function.h"
#include "Export_Function.h"
#include "BulletMain.h"


CNormal_Bullet::CNormal_Bullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CBulletMain(pGraphicDev)
{
}

CNormal_Bullet::~CNormal_Bullet(void)
{
}

HRESULT CNormal_Bullet::Ready_Object(void)
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



	return S_OK;
}

int CNormal_Bullet::Update_Object(const float & fTimeDelta)
{
	Engine::CBulletMain::Update_Object(fTimeDelta);


	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(10.f);
		m_bFirst = false;
		m_iEvent = 0;
		m_eState = IDLE_BULLET;
		

		CGameObject* pPlayer = ((Engine::CLayer*)(Get_Parent()))->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
		Engine::CTransform* pPlayerTransformCom = static_cast<Engine::CTransform*>(pPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));

		pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);

		m_FirstPos = m_vPlayerPos - m_pTransform->m_vInfo[Engine::INFO_POS];
	}

	

	if (m_eState == IDLE_BULLET)
	{
		m_pTransform->Dir_Fly(&m_FirstPos, (fTimeDelta * 300.f));
	}
	else if (m_eState == DEAD_BULLET)
	{
		m_bFirst = true;
		Dead_Bullet();
	}


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

	D3DXMATRIX		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	ZeroMemory(&matView.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld = matView *  m_pTransform->m_matWorld;


	State_Change();
	Update_Animation(fTimeDelta);
	return m_iEvent;
}

void CNormal_Bullet::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pTextureCom->Set_Texture((int)m_tFrame.fStartFrame);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0);

	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pBufferBoradCom->Render_Buffer();


	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

HRESULT CNormal_Bullet::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_Posion"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);



	return S_OK;
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

void CNormal_Bullet::Update_Animation(const float & fTimeDelta)
{
	m_tFrame.fStartFrame += m_tFrame.fMaxFrame * fTimeDelta * m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame)
	{
		m_tFrame.fStartFrame = 0.f;
	}
}

void CNormal_Bullet::Free(void)
{
	Engine::CBulletMain::Free();
}
