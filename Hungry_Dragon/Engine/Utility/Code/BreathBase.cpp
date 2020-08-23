#include "BreathBase.h"
#include "PlayerMain.h"
#include "Transform.h"
#include "Export_Function.h"

USING(Engine)

Engine::CBreathBase::CBreathBase(void)
{
	
}

Engine::CBreathBase::CBreathBase(const CBreathBase& rhs)	
{

}

Engine::CBreathBase::~CBreathBase(void)
{

}

HRESULT Engine::CBreathBase::Ready_BreathBase(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	m_pGraphicDev = _pGraphicDev;
	D3DXCreateCylinder(
		m_pGraphicDev,
		0.7f, // radius at negative z end
		0.7f, // radius at positive z end
		100.f, // length of cylinder
		10,   // slices
		10,   // stacks
		&m_pCylinder,
		0);
	return S_OK;
}

void CBreathBase::Initialize_Component(void)
{
}

_int Engine::CBreathBase::Update_Component(CPlayerMain* _pPlayer)
{
	return 0;
}

void CBreathBase::LateUpdate_Component(const _float & fTimeDelta)
{
}

void CBreathBase::Render_Breath(CPlayerMain* _pPlayer)
{
	//_vec3 vDir = _pPlayer->Get_Camera()->Get_Dir()*100.f;
	_matrix matWorld = _pPlayer->Get_Transform()->Get_World();
	matWorld.m[3][0] += matWorld.m[2][0]*52.f;
	matWorld.m[3][1] += matWorld.m[2][1]*52.f;
	matWorld.m[3][2] += matWorld.m[2][2]*52.f;

	//_matrix matWorld = _pPlayer->Get_Transform()->Get_World();
	//_vec3 vDir = { matWorld.m[2][0], matWorld.m[2][1], matWorld.m[2][2] };
	//D3DXVec3Normalize(&vDir, &vDir);
	//matWorld.m[3][0] += vDir.x*100.f;
	//matWorld.m[3][1] += vDir.y*100.f;
	//matWorld.m[3][2] += vDir.z*100.f;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pCylinder->DrawSubset(0);
	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBreathBase* Engine::CBreathBase::Create(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	CBreathBase*	pInstance = new CBreathBase;

	if (FAILED(pInstance->Ready_BreathBase(_pGraphicDev)))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CBreathBase::Free(void)
{
	m_pCylinder->Release();
}

CComponent* Engine::CBreathBase::Clone(void)
{
	return new CBreathBase(*this);
}