#ifndef BossPlayer_h__
#define BossPlayer_h__

#include "Define.h"
#include "PlayerMain.h"

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTerrain;
class CParticle;
class CResources;

END

class CBossPlayer : public Engine::CPlayerMain
{
private:
	explicit CBossPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBossPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object(void);
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void LateUpdate_Object(const float& fTimeDelta);
	virtual void Render_Object(void) override;
	void			Animation_Render();


private:
	virtual void	State_Change() override;
	virtual HRESULT	Add_Component(void) override;

	void			Preset_Animation();

	float m_vWAngle = 0.f;
	float m_fWSpeed = 0.03f;

public:
	static CBossPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

public:
	Engine::CParticle*				m_pParticle=nullptr;

	//먹는거 컨트롤할 임시 변수
	bool						m_bEatFirst=true;
};

#endif // BossPlayer_h__
