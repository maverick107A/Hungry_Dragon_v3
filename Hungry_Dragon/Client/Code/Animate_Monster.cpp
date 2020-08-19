#include "stdafx.h"
#include "Animate_Monster.h"

USING(Engine)

CAnimate_Monster::CAnimate_Monster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMovingObject(pGraphicDev)
{
}

CAnimate_Monster::~CAnimate_Monster(void)
{

}

HRESULT CAnimate_Monster::Ready_Object(void)
{
	CMovingObject::Ready_Object();
	if (S_OK != Add_Componenet())
	{
		return E_FAIL;
	}

	m_pTransform->Set_Trans(&_vec3(0.f, 1000.f, 0.f));
	m_pTransform->Update_Component(0.f);
	for (size_t i = 0; i < m_pMeshTransform.size(); ++i)
	{
		m_pMeshTransform[i]->Set_Trans(&_vec3(0.f, 1000.f, 0.f));
		m_pMeshTransform[i]->Update_Component(0.f);
	}

	return S_OK;
}

int CAnimate_Monster::Update_Object(const float & fTimeDelta)
{
	CMovingObject::Update_Object(fTimeDelta);
	
	return 0;
}

void CAnimate_Monster::LateUpdate_Object(const float & fTimeDelta)
{
	CMovingObject::LateUpdate_Object(fTimeDelta);
}

void CAnimate_Monster::Render_Object(void)
{
	CMovingObject::Render_Object();
}

HRESULT CAnimate_Monster::Add_Componenet(void)
{

	m_pAnimator = Engine::CAnimator::Create();
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Mob_Animator", m_pAnimator);
	m_pAnimator->Register_MoveTarget();
	m_pAnimator->Register_MoveTarget();

	Engine::CComponent* pComponenet = nullptr;

	pComponenet = Engine::Clone(RESOURCE_STATIC, L"BUFFER_DIAMOB_UPPER");
	NULL_CHECK_RETURN(pComponenet, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Diamob_Upper", pComponenet);
	m_pMeshArray.emplace_back(static_cast<CVICustom*>(pComponenet));

	pComponenet = Engine::Clone(RESOURCE_STATIC, L"BUFFER_DIAMOB_UNDER");
	NULL_CHECK_RETURN(pComponenet, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Diamob_Under", pComponenet);
	m_pMeshArray.emplace_back(static_cast<CVICustom*>(pComponenet));

	pComponenet = Engine::CTransform::Create();
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Upper_Transform", pComponenet);
	m_pMeshTransform.emplace_back(static_cast<Engine::CAnimationTransform*>(pComponenet));

	pComponenet = Engine::CTransform::Create();
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Under_Transform", pComponenet);
	m_pMeshTransform.emplace_back(static_cast<Engine::CAnimationTransform*>(pComponenet));

	m_pTransform = Engine::CTransform::Create();
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Total_Transform", m_pTransform);

	m_pAnimator->Set_FrameSpeed(10.f);

	for (int i = 0; i < 36; ++i)
	{
		m_pAnimator->Insert_Scale(0, i, _vec3(30.f, 30.f, 30.f));
		m_pAnimator->Insert_Revolute(m_pGraphicDev, 0, i, _vec3(0.f, 990.f, 0.f), _vec3(0.f, 0.f, D3DXToRadian((float)i)));
	}


	return S_OK;
}

CAnimate_Monster * CAnimate_Monster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAnimate_Monster* pInstance = new CAnimate_Monster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CAnimate_Monster::Free(void)
{
	CMovingObject::Free();
}
