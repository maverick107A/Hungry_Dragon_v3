#ifndef BackGroundLogo_h__
#define BackGroundLogo_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END



class CBackGround_Logo : public Engine::CGameObject {
private:
	explicit CBackGround_Logo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBackGround_Logo(void);

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

private:
	static Engine::_uint m_uBgNum;

public:
	static CBackGround_Logo*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static CBackGround_Logo*	Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::_uint _uNum);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
