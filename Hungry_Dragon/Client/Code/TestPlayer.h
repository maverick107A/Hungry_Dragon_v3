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

END
class CTestPlayer : public Engine::CPlayerMain
{
private:
	explicit CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	


private:
	virtual void	State_Change() override;
	virtual HRESULT	Add_Component(void) override;
	void		Key_Input(const float& fTimeDelta);
	void		Ride_Terrain();

public:
	static CTestPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

#endif // TestPlayer_h__
