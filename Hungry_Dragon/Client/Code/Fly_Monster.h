#ifndef Fly_Monster_h__
#define Fly_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CTerrainTex;
class CAnimation_Controller;


END

class  CFly_Monster  : public Engine::CMonsterMain
{

public:
	enum MOBPATTERN { MOBPATTERN_IDLE, MOBPATTERN_END };
private:
	explicit CFly_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFly_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);	
	void		Preset_Animation();
	void Animation_Render();
	void LateUpdate_Object(const float & fTimeDelta);
public:
	void Shooting(void);

public:
	static CFly_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

private:

	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vLookPos;
	D3DXVECTOR3 m_vBodyPos;

	float m_fShotingLate = 0.f;
	float m_fShotingDelay = 0.9f;

	float m_fHeight = 0;
	float		m_fAngle = 0;
	Engine::CAnimation_Controller* m_pAnimationController;
	MOBPATTERN						m_ePattern = MOBPATTERN_IDLE;
};


#endif // Fly_Monster_h__
