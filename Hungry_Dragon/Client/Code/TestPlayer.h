#ifndef TestPlayer_h__
#define TestPlayer_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CCubeDra;
class CTexture;
class CTransform;
class CCamera;
class CTerrain;

END
class CTestPlayer : public Engine::CGameObject
{
private:
	explicit CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);
	void		Ride_Terrain();

private:
	Engine::CCubeDra*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CCamera*		m_pCamera = nullptr;
	Engine::CTerrain*		m_pTerrain = nullptr;
	D3DXVECTOR3				m_vLook;
	D3DXVECTOR3				m_vUp;
	bool					m_bland = false;
	float					m_fSpeed = 1.f;


public:
	static CTestPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // TestPlayer_h__
