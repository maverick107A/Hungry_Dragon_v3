#include "Export_Utility.h"
// Management


// Set
HRESULT		Set_Scene(CScene* pScene) {
	return CManagement::GetInstance()->Set_Scene(pScene);
}

// General
HRESULT	Create_Management(CManagement** ppManagement)
{
	CManagement*	pManagement = CManagement::GetInstance();

	if (nullptr == pManagement)
		return E_FAIL;

	*ppManagement = pManagement;

	return S_OK;
}

inline void	Initialize()
{
	CManagement::GetInstance()->Initialize();
}

// Renderer
// Get
CRenderer*		Get_Renderer(void)
{
	return CRenderer::GetInstance();
}
// Set
// General
void	Add_RenderGroup(RENDERID eType, CGameObject* pGameObject)
{
	CRenderer::GetInstance()->Add_RenderGroup(eType, pGameObject);
}
void	Render_GameObject(void)
{
	CRenderer::GetInstance()->Render_GameObject();
}
void	Clear_RenderGroup(void)
{
	CRenderer::GetInstance()->Clear_RenderGroup();
}

//Object_Pool

HRESULT		Add_Object_Layer(OBJID _Type, _int iCnt)
{
	return CObjectPool::GetInstance()->Add_Object_Layer(_Type, iCnt);
}
HRESULT Add_Object_Pool(CGameObject * pGameObject, OBJID _Type)
{
	return CObjectPool::GetInstance()->Add_Object_Pool(pGameObject, _Type);
}

HRESULT Set_Bullet_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Bullet_LayerMap(_Type, iCnt, _Pos);
}

inline HRESULT Set_Monster_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Monster_LayerMap(_Type, iCnt, _Pos);
}

inline HRESULT Set_Monster_CaveMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Monster_CaveMap(_Type, iCnt, _Pos);
}

inline HRESULT	Set_Monster_HorizonCaveMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Monster_HorizonCaveMap(_Type, iCnt, _Pos);
}
inline HRESULT		Set_Monster_HorizonCaveRedMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Monster_HorizonCaveRedMap(_Type, iCnt, _Pos);

}

inline HRESULT Set_Monster_CloudMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Monster_CloudMap(_Type, iCnt, _Pos);
}

void		Set_Object_LayerMap(CLayer *  _Layer)
{
	return CObjectPool::GetInstance()->Set_Object_LayerMap(_Layer);

}

HRESULT		Clear_ObjectPool()
{
	return CObjectPool::GetInstance()->Clear_ObjectPool();
}



//Particle
void Ready_ParticleMgr(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	Engine::CParticleMgr::GetInstance()->Ready_ParticleMgr(_pGraphicDev);
}

void Particle_Update(const float& fTimeDelta)
{
	Engine::CParticleMgr::GetInstance()->Particle_Update(fTimeDelta);
}

inline void Particle_LateUpdate(const float & fTimeDelta)
{
	Engine::CParticleMgr::GetInstance()->Particle_LateUpdate(fTimeDelta);
}

void Particle_Render()
{
	Engine::CParticleMgr::GetInstance()->Particle_Render();
}

inline bool Set_ParticleTrans(Engine::CResources* _particle, Engine::_vec3 _pos)
{
	return Engine::CParticleMgr::GetInstance()->Set_ParticleTrans(_particle, _pos);
}

inline bool Set_StaticParticleTrans(CResources * _particle, _vec3 _pos)
{
	return Engine::CParticleMgr::GetInstance()->Set_StaticParticleTrans(_particle, _pos);
}

inline Engine::CResources* Particle_Create(Engine::PARTICLEID _eID, const Engine::_vec3 _pos)
{
	return CParticleMgr::GetInstance()->Particle_Create(_eID,_pos);
}

inline CResources * Particle_Create_Static(Engine::PARTICLEID _eID, const _vec3 _pos)
{
	return CParticleMgr::GetInstance()->Particle_Create_Static(_eID, _pos);
}

inline bool Find_First(CGameObject * _caller, CGameObject * _callee)
{
	return Engine::CCollisionMgr::Find_First(_caller,_callee);
}

// Release
void		Release_Utility(void)
{
	CCollisionMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();
	CRenderer::GetInstance()->DestroyInstance();
	CObjectPool::GetInstance()->DestroyInstance();
	CParticleMgr::GetInstance()->DestroyInstance();
	CEngineEventMgr::GetInstance()->DestroyInstance();
}