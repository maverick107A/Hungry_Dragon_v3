#ifndef Cliff_Object_h__
#define Cliff_Object_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CBaseLand;
class CCliffCylinder;

END


USING(Engine)

class CCliff_Object : public Engine::CGameObject
{
private:
	explicit CCliff_Object(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCliff_Object(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Trans(_vec3& _vPos);

private:
	HRESULT		Add_Component(void);
	
	

private:
	Engine::CTransform*		m_pTransform;
	_uint					m_uLength;
	_uint					m_uVerCntX;
	_uint					m_uVerCntZ;
	Engine::CCliffCylinder*		m_pBufferCom = nullptr;

public:
	static CCliff_Object*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
