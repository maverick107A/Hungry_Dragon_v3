#include "Export_Utility.h"
// Management
// Get
CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}
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

void		Set_Object_LayerMap(CLayer *  _Layer)
{
	return CObjectPool::GetInstance()->Set_Object_LayerMap(_Layer);

}

// Release
void		Release_Utility(void)
{
	CManagement::GetInstance()->DestroyInstance();
	CRenderer::GetInstance()->DestroyInstance();
	CObjectPool::GetInstance()->DestroyInstance();
}