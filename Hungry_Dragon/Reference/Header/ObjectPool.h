#ifndef ObjectPool_h__
#define ObjectPool_h__

#include "GameObject.h"
#include "ObjectPool.h"


BEGIN(Engine)

class CLayer;

class ENGINE_DLL CObjectPool : public CBase
{
	DECLARE_SINGLETON(CObjectPool)

private:
	explicit	CObjectPool(void);
	virtual		~CObjectPool(void);

public:
	HRESULT		Add_Object_Pool(CGameObject* pGameObject, OBJID _Type);
	HRESULT		Add_Object_Layer(OBJID _Type, _int iCnt);
	void		Set_Object_LayerMap(CLayer *  _Layer);
	HRESULT		Set_Bullet_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos);
	HRESULT		Set_Monster_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos);
private:
	CLayer*		m_Layer;
	list<CGameObject*>  m_listObject[OBJID::OBJ_END];
public:
	virtual void	Free(void);
};

END
#endif // ObjectPool_h__
