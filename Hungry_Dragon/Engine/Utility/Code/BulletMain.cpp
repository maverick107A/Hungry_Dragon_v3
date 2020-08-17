#include "BulletMain.h"

#include "Export_Function.h"

Engine::CBulletMain::CBulletMain(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

Engine::CBulletMain::~CBulletMain(void)
{
}

HRESULT Engine::CBulletMain::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int Engine::CBulletMain::Update_Object(const float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	D3DXVECTOR3	vBulletPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vBulletPos);
	D3DXVECTOR3 Dir = vBulletPos - m_vPlayerPos;
	m_fDistance = D3DXVec3Length(&Dir);



	if (m_iEvent == BULLET_DEAD)
	{
		return -1;
	}


	return m_iEvent;
}

void Engine::CBulletMain::Render_Object(void)
{
}

void Engine::CBulletMain::Dead_Bullet(void)
{
	m_iEvent = BULLET_DEAD;
}

void Engine::CBulletMain::Set_Pos(D3DXVECTOR3 _Pos)
{
	m_pTransform->m_vInfo[Engine::INFO_POS].x = _Pos.x;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = _Pos.y;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = _Pos.z;
}

HRESULT Engine::CBulletMain::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	pComponent = m_pTransformX = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_TransformX", pComponent);
	
	return S_OK;
}

void Engine::CBulletMain::Key_Input(const float & fTimeDelta)
{
}

Engine::CBulletMain * Engine::CBulletMain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletMain*		pInstance = new CBulletMain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CBulletMain::Free(void)
{
	Engine::CGameObject::Free();
}
