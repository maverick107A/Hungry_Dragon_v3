#ifndef RedSkySphere_h__
#define RedSkySphere_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CSkyCube;
class CTexture;
class CTransform;
class CRenderer;
class CCameraMain;

END
class CRedSky : public Engine::CGameObject
{
private:
	explicit CRedSky(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRedSky(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void	Initialize_Object(void);
	virtual Engine::_int Update_Object(const Engine::_float& fTimeDelta) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);

private:
	Engine::CSkyCube*		m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CCameraMain*	m_pPlayerCamera = nullptr;

public:
	static CRedSky*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // SkyBox_h__
