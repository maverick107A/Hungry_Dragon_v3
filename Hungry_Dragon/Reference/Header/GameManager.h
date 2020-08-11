#ifndef GameManager_h__
#define GameManager_h__

#include "GameObject.h"
#include "GameManager.h"


BEGIN(Engine)

class CLayer;

class ENGINE_DLL CGameManager : public CBase
{
	DECLARE_SINGLETON(CGameManager)

private:
	explicit	CGameManager(void);
	virtual		~CGameManager(void);

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
#endif // GameManager_h__
