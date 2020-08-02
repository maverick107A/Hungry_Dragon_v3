#ifndef Layer_h__
#define Layer_h__

#include "UtilBase.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CUtilBase
{
private:
	explicit CLayer(void);
	virtual ~CLayer(void);

public:
	CComponent*	Get_Component(const _tchar* pObjTag,const _tchar* pComponentTag, COMPONENTID eID);
	HRESULT		Add_Object(const _tchar* pObjTag, CGameObject* pGameObject);
	HRESULT		Add_Bullet_Object(CGameObject * pGameObject, _vec3 _pos);
	HRESULT		Add_Monster_Object(CGameObject * pGameObject, _vec3 _pos);
	void		Set_Address(void);

public:
	HRESULT		Ready_Layer(void);
	_int		Update_Layer(const _float& fTimeDelta);
	void		LateUpdate_Layer(const _float& fTimeDelta);
	void		Render_Layer(void);

public:
	void		Set_Player(const _vec3 fPlayerPos) { m_vPlayerPos = fPlayerPos; }

private:
	map<const _tchar*, CGameObject*>		m_mapObject;
	list<CGameObject*>					m_listBullet;
	list<CGameObject*>					m_listMonster;
	_vec3			m_vPlayerPos;

public:
	static CLayer*		Create(void);
	virtual void		Free(void);
};

END
#endif // Layer_h__
