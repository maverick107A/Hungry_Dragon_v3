#include "stdafx.h"
#include "BackGround.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "ForestLand.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CBackGround::~CBackGround(void)
{

}

HRESULT CBackGround::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int CBackGround::Update_Object(const float& fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CBackGround::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pBufferCom->Render_Buffer();
}

void CBackGround::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CBackGround::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CForestLand*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_TERRAIN"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround*		pInstance = new CBackGround(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

