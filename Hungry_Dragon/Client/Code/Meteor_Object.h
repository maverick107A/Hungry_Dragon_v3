#ifndef Meteor_Object_h__
#define Meteor_Object_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END

USING(Engine)

class CMeteor_Object : public Engine::CGameObject {
protected:
	explicit CMeteor_Object(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor_Object(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	_bool	Get_Active() { return m_bActive; }
	void	Set_Active(bool _bActive) { m_bActive = _bActive; }		// ¾÷µ«
	void	Set_Trans(_vec3& _vPos);
	void	Set_Speed(float _fSpeed) { m_fForwardSpeed = _fSpeed; }

protected:
	HRESULT		Add_Component(void);

protected:
	Engine::CTexture_Square*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTexture*		m_pTextureBoom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;

	Engine::_uint m_uTexFrame = 0;

	_vec3					m_vPosOrigin;
	_bool					m_bActive = false;
	_bool					m_bBoom = false;
	_uint					m_uSpriteTick = 0;
	float					m_fForwardSpeed = 10000.f;

public:
	static CMeteor_Object*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
protected:
	virtual void Free(void) override;

};

#endif // BackGround_h__
