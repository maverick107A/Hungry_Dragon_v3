#ifndef Accel_Torus_h__
#define Accel_Torus_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CTorus;

END

USING(Engine)

class CAccel_Torus :public Engine::CGameObject {
private:
	explicit CAccel_Torus(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CAccel_Torus(void);

public:
	virtual HRESULT Ready_Object(void)override;
	virtual void Initialize_Object()override;
	virtual _int Update_Object(const _float& fTimeDelta)override;
	virtual void Render_Object(void)override;

public:
	void Set_Transe(_vec3& _vPos);

private:
	HRESULT		Add_Component(void);

public:
	static CAccel_Torus* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void)override;

private:
	Engine::CTorus*		m_pTorus=nullptr;
	Engine::CTransform*	m_pTransform;


};
#endif // !Accel_Torus_h__
