#include "stdafx.h"

#include "Monster.h"

#include "Export_Function.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

CMonster::~CMonster(void)
{
}

HRESULT CMonster::Ready_Object(void)
{
 	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int CMonster::Update_Object(const float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	return m_iEvent;
}


void CMonster::Render_Object(void)
{

}

void CMonster::Dead_Monster(void)
{

	m_pTransform->Set_Trans(&m_vPlayerPos);

	m_pTransform->m_vScale.x -= 0.4f;
	m_pTransform->m_vScale.y -= 0.4f;
	m_pTransform->m_vScale.z -= 0.4f;


	if (m_pTransform->m_vScale.x < 3.f)
	{
		m_iEvent = MONSTER_DEAD;
	}
}



HRESULT CMonster::Add_Component(void)
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

void CMonster::Key_Input(const float & fTimeDelta)
{
	
}

CMonster * CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster*		pInstance = new CMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CMonster::Free(void)
{
	Engine::CGameObject::Free();
}
