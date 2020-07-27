#ifndef Layer_h__
#define Layer_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer(void);
	virtual ~CLayer(void);

public:
	CComponent*			Get_Component(const _tchar* pObjTag,
										const _tchar* pComponentTag, 
										COMPONENTID eID);

public:
	HRESULT		Add_Object(const _tchar* pObjTag, CGameObject* pGameObject);
	HRESULT		Add_Bullet_Object(CGameObject * pGameObject, _vec3 _pos);

	HRESULT		Ready_Layer(void);
	_int		Update_Layer(const _float& fTimeDelta);
	void		Render_Layer(void);
	void		Set_Player(const _vec3 fPlayerPos) { m_vPlayerPos = fPlayerPos; }

private:
	map<const _tchar*, CGameObject*>		m_mapObject;
	list<CGameObject*>					m_listBullet;
	//list<CGameObject*>					m_listItem;
	//list<CGameObject*>					m_listNull;



	_vec3			m_vPlayerPos;
public:
	static CLayer*		Create(void);
	virtual void		Free(void);
};

END
#endif // Layer_h__
