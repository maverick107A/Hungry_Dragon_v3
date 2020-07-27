#ifndef GameObject_h__
#define GameObject_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject : public CBase
{ 
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject(void);

public:
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		Render_Object(void);
	void				Set_Player(const _vec3 fPlayerPos) { m_vPlayerPos = fPlayerPos; }
	void				Set_Pos(const _vec3 _Pos) { m_vFirstPos = _Pos; }

protected:
	_vec3			m_vPlayerPos;
	_vec3			m_vFirstPos;

	LPDIRECT3DDEVICE9		m_pGraphicDev;
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];
private:
	CComponent*		Find_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual void	Free(void);

};
END
#endif // GameObject_h__
