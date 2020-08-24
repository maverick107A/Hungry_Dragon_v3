#ifndef Compass_h__
#define Compass_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END
class CCompass : public Engine::CGameObject
{
private:
	explicit CCompass(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCompass(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
public:


private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture*		m_pTexture = nullptr;

public:
	static CCompass*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
