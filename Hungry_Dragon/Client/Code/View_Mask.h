#ifndef View_Mask_h__
#define View_Mask_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;
class CCameraMain;
class CPlayerMain;

END




class CView_Mask : public Engine::CGameObject {
private:
	explicit CView_Mask(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CView_Mask(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:


private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture_Square*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;

	Engine::_uint m_uTexFrame = 0;
	bool					m_bAccel = true;
	Engine::_float	m_fAccel = 1.f;

	Engine::CCameraMain*			m_pCam = nullptr;
	Engine::CPlayerMain*					m_pPlayer = nullptr;

public:
	static CView_Mask*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
