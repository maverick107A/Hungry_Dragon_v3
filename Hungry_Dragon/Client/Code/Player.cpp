#include "stdafx.h"

#include "Player.h"

#include "Export_Function.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

CPlayer::~CPlayer(void)
{
}

HRESULT CPlayer::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pTransform->m_vInfo[Engine::INFO_POS].z = 64.0f;
	m_pTransform->m_vInfo[Engine::INFO_POS].x = 64.0f;


	m_pTransform->m_vScale.x *= 10.1f;
	m_pTransform->m_vScale.y *= 10.1f;
	m_pTransform->m_vScale.z *= 10.1f;

	return S_OK;
}

int CPlayer::Update_Object(const float & fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);



	return 0;
}

void CPlayer::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}

HRESULT CPlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CCubeTex*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);



	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_PlayerBox"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);


	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);


	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*		pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CPlayer::Free(void)
{
	Engine::CGameObject::Free();
}
