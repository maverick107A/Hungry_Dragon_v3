#ifndef Logo_Loop_h__
#define Logo_Loop_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END



class CLogo_Loop : public Engine::CGameObject {
private:
	explicit CLogo_Loop(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogo_Loop(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;


private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture_Square*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;

	Engine::_uint m_uLogo = 0;

public:
	static CLogo_Loop*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
