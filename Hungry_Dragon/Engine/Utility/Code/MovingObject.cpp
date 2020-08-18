#include "MovingObject.h"

USING(Engine)

CMovingObject::CMovingObject(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMovingObject::~CMovingObject(void)
{
}

HRESULT CMovingObject::Ready_Object(void)
{
	m_pAnimator = Engine::CAnimator::Create();

	Engine::Ready_Buffer(m_pGraphicDev, 2, L"Buffer_Body_Upper", Engine::BUFFER_DIAMOB_UPPER);
	CVICustom* tempBuffer = static_cast<CVICustom*>(Engine::Clone(0,L"Buffer_Body_Upper"));
	m_pMeshArray.emplace_back(tempBuffer);
	m_mapComponent[0].emplace(L"Com_Buffer_Upper", tempBuffer);
	m_pMeshTransform.emplace_back(Engine::CTransform::Create());
	m_mapComponent[2].emplace(L"Com_Transform_Upper", m_pMeshTransform.front());
	m_pAnimator->Register_MoveTarget();

	Engine::Ready_Buffer(m_pGraphicDev, 2, L"Buffer_Body_Under", Engine::BUFFER_DIAMOB_UNDER);
	tempBuffer = static_cast<CVICustom*>(Engine::Clone(0, L"Buffer_Body_Under"));
	m_pMeshArray.emplace_back(tempBuffer);
	m_mapComponent[0].emplace(L"Com_Buffer_Under", tempBuffer);
	m_pMeshTransform.emplace_back(Engine::CTransform::Create());
	m_mapComponent[2].emplace(L"Com_Transform_Under", m_pMeshTransform.back());
	m_pAnimator->Register_MoveTarget();

	m_pAnimator->Insert_Scale(0, 1, _vec3(2.f, 2.f, 2.f));
	m_pAnimator->Insert_Scale(1, 1, _vec3(0.5f, 0.5f, 0.5f));
	return S_OK;
}

void CMovingObject::Initialize_Object(void)
{
	vector<CTransform*>::iterator iter = m_pMeshTransform.begin();
	for (; iter != m_pMeshTransform.end(); ++iter)
	{
		//위치 잡아줍시다.
		(*iter)->Set_Trans(&_vec3(0.f,0.f,0.f));
	}
}

int CMovingObject::Update_Object(const float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	return 0;
}

void CMovingObject::LateUpdate_Object(const _float & fTimeDelta)
{
	CGameObject::LateUpdate_Object(fTimeDelta);
}

void CMovingObject::Render_Object(void)
{
	_matrix matWorld,matOriginWorld;

	matWorld = matOriginWorld = m_pMeshTransform[0]->m_matWorld;
	matWorld = m_pAnimator->Get_MoveResult(m_pGraphicDev, matWorld, 0);
	m_pMeshTransform[0]->Set_Transform(m_pGraphicDev);
	m_pMeshArray[0]->Render_Buffer();
	m_pMeshTransform[0]->m_matWorld = matOriginWorld;

	matWorld = matOriginWorld = m_pMeshTransform[1]->m_matWorld;
	matWorld = m_pAnimator->Get_MoveResult(m_pGraphicDev, matWorld, 1);
	m_pMeshTransform[1]->Set_Transform(m_pGraphicDev);
	m_pMeshArray[1]->Render_Buffer();
	m_pMeshTransform[1]->m_matWorld = matOriginWorld;

	//CGameObject::Render_Object();
}

CMovingObject * CMovingObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return new CMovingObject(pGraphicDev);
}
