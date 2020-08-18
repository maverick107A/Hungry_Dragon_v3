#ifndef MovingObject_h__
#define MovingObject_h__

#include "GameObject.h"

#include "Export_Function.h"

BEGIN(Engine)

class CVICustom;
class CTransform;
class CAnimator;

class ENGINE_DLL CMovingObject :public Engine::CGameObject
{
protected:
	explicit CMovingObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMovingObject(void);

public:
	virtual HRESULT Ready_Object(void);
	virtual void Initialize_Object(void);
	virtual int Update_Object(const float& fTimeDelta);
	virtual void LateUpdate_Object(const _float& fTimeDelta);
	virtual void Render_Object(void);

public:
	static CMovingObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	vector<CVICustom*>	m_pMeshArray;
	vector<CTransform*>	m_pMeshTransform;
	CAnimator*			m_pAnimator;
};

END
#endif
