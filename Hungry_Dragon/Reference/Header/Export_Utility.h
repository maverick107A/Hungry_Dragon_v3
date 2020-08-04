#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Engine_Define.h"
#include "Management.h"
#include "ObjectPool.h"
#include "Transform.h"
#include "Renderer.h"
#include "Layer.h"
#include "GameObject.h"
#include "Component.h"

BEGIN(Engine)

// Management
// Get
inline CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag,	COMPONENTID eID);
// Set
inline HRESULT		Set_Scene(CScene* pScene);
// General
inline HRESULT	Create_Management(CManagement** ppManagement);


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
inline  void		Set_Object_LayerMap(CLayer *  _Layer);

// Release
inline void		Release_Utility(void);

#include "Export_Utility.inl"

END
#endif // Export_Utility_h__
