#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Engine_Define.h"
#include "Management.h"
#include "ObjectPool.h"
#include "Transform.h"

#include "AnimationTransform.h"
#include "Renderer.h"
#include "Layer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Component.h"
#include "Animator.h"
#include "Animation_Controller.h"
#include "CollisionMgr.h"
#include "ParticleMgr.h"
#include "PlayerMain.h"
#include "EngineEventMgr.h"
BEGIN(Engine)

// Management

// Set
inline HRESULT		Set_Scene(CScene* pScene);
// Get

inline CComponent*	Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}
inline CGameObject*	Get_Object(const _tchar* pLayerTag, const _tchar* pObjTag)
{
	return CManagement::GetInstance()->Get_Object(pLayerTag, pObjTag);
}

// General
inline HRESULT	Create_Management(CManagement** ppManagement);
inline void	Initialize();

// Renderer
// Get
inline CRenderer*		Get_Renderer(void);
// Set
// General
inline void	Add_RenderGroup(RENDERID eType, CGameObject* pGameObject);
inline void	Render_GameObject(void);
inline void	Clear_RenderGroup(void);

// Object_Pool

inline HRESULT		Add_Object_Layer(OBJID _Type, _int iCnt);
inline HRESULT		Add_Object_Pool(CGameObject* pGameObject, OBJID _Type);
inline HRESULT      Set_Bullet_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Set_Monster_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Set_Monster_CaveMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Set_Monster_HorizonCaveMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Set_Monster_HorizonCaveRedMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Set_Monster_CloudMap(OBJID _Type, _int iCnt, _vec3 _Pos);
inline HRESULT		Clear_ObjectPool();
inline  void		Set_Object_LayerMap(CLayer *  _Layer);

//Collision
inline  static bool	Find_First(CGameObject* _caller,CGameObject* _callee);

//Particle
inline void Ready_ParticleMgr(LPDIRECT3DDEVICE9 _pGraphicDev);
inline void Particle_Update(const float& fTimeDelta);
inline void Particle_LateUpdate(const float& fTimeDelta);
inline void Particle_Render();
inline bool Set_ParticleTrans(CResources* _particle, _vec3 _pos);
inline bool Set_StaticParticleTrans(CResources* _particle, _vec3 _pos);
inline CResources* Particle_Create(Engine::PARTICLEID _eID, const _vec3 _pos);
inline CResources* Particle_Create_Static(Engine::PARTICLEID _eID, const _vec3 _pos);

// Event
//Get
inline CEngineEventMgr* Get_EventMgr() { return CEngineEventMgr::GetInstance(); }


// Release
inline void		Release_Utility(void);

#include "Export_Utility.inl"

END
#endif // Export_Utility_h__
