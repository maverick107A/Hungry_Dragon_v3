#ifndef TestPlayer_h__
#define TestPlayer_h__

#include "Define.h"
#include "PlayerMain.h"

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTransform;
class CCamera;
class CTerrain;
class CPart_Atk;
class CResources;

END
class CTestPlayer : public Engine::CPlayerMain
{
private:
	explicit CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object(void);
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	


private:
	virtual void	State_Change() override;
	virtual HRESULT	Add_Component(void) override;
	void		Animation_Render();

	float m_vAngle = 0.f;
	float m_fSpeed = 0.05f;

	D3DXMATRIX m_matOld1;
	D3DXMATRIX m_matOld2;
	D3DXMATRIX m_matOld3;

public:
	static CTestPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

public:
	list<Engine::CResources*>  m_arrParticle;

};

#endif // TestPlayer_h__
