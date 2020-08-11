#ifndef PlayerUI_h__
#define PlayerUI_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CPlayerMain;

END

class CPlayerUI : public Engine::CGameObject
{
private:
	explicit CPlayerUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerUI(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object(void);
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
private:
	HRESULT		Add_Component(void);

private:
	Engine::CPlayerMain*		m_pPlayer = nullptr;
	IDirect3DTexture9*	m_pRedTex;
	IDirect3DTexture9*	m_pGreenTex;
	IDirect3DTexture9*	m_pYellowTex;

public:
	static CPlayerUI*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // PlayerUI_h__
