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
	//�Լ� �����ͷ� �Ѱ��� _functionPointer�� Ư�� Ŭ������ ��� �Լ��� ��� ����ƽ�̾�� �Ѵ�.
	//GameObject���� �񱳰� �ʿ��� ���(ex) �Ѿ˰��� ������ �浹 ����) _callerObj�� ���� ����� �־� �ָ� �ȴ�.
	CGameObject*	Get_Object(const _tchar* _pObjTag, bool(*_functionPointer)(CGameObject* _caller, CGameObject* _callee), CGameObject* _callerObj);
	CGameObject*	Get_Object(const _tchar* _pObjTag);
	CComponent*		Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
	_vec3			Get_PlayerPos() { return m_vPlayerPos; }

	void			Set_Address(void);
	void			Set_Player(const _vec3 fPlayerPos) { m_vPlayerPos = fPlayerPos; }

	// �¹��̰� ���� �ӽ� �Լ�
	void			Delete_Object(const _tchar* _pObjTag);

	HRESULT			Add_Object(const _tchar* pObjTag, CGameObject* pGameObject);
public:
	HRESULT			Ready_Layer(void);
	void			Initialize_Layer(void);
	_int			Update_Layer(const _float& fTimeDelta);
	void			LateUpdate_Layer(const _float& fTimeDelta);
	void			Render_Layer(void);

private:
	map<const _tchar*, list<CGameObject*>>		m_mapObject;
	_vec3										m_vPlayerPos;

public:
	static CLayer*		Create(void);
	virtual void		Free(void);
};

END
#endif // Layer_h__
