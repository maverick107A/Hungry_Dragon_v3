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
class CAnimation_Controller;

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
	
	void			Animations(const float& fTimeDelta);
	void			Preset_Animation();

	float m_vAngle = 0.f;
	float m_fSpeed = 0.1f;

	float m_vWAngle = 0.f;
	float m_fWSpeed = 0.03f;

	D3DXMATRIX m_matOld1;
	D3DXMATRIX m_matOld2;
	D3DXMATRIX m_matOld3;

public:
	static CBossPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

public:
	Engine::CParticle*				m_pParticle=nullptr;
	Engine::CAnimation_Controller* m_pAnimationController;

	//�Դ°� ��Ʈ���� �ӽ� ����
	bool						m_bEatFirst=true;
};

#endif // BossPlayer_h__
