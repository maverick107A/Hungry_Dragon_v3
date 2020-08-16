#include "BeamBase.h"

#include "Export_Function.h"

Engine::CBeamBase::CBeamBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

Engine::CBeamBase::~CBeamBase(void)
{
}

HRESULT Engine::CBeamBase::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int Engine::CBeamBase::Update_Object(const float & fTimeDelta)
{
	return 0;
}

void Engine::CBeamBase::Render_Object(void)
{
}

HRESULT Engine::CBeamBase::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	return S_OK;
}

Engine::CBeamBase * Engine::CBeamBase::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBeamBase*		pInstance = new CBeamBase(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CBeamBase::Free(void)
{
	Engine::CGameObject::Free();
}
