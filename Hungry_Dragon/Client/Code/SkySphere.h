#ifndef SkySphere_h__
#define SkySphere_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CSkyCube;
class CTexture;
class CTransform;
class CRenderer;

END
class CSkySphere : public Engine::CGameObject
{
private:
	explicit CSkySphere(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSkySphere(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual Engine::_int Update_Object(const Engine::_float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);

private:
	Engine::CSkyCube*		m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

public:
	static CSkySphere*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // SkyBox_h__
