#ifndef GiantGolem_h__
#define GiantGolem_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;
class CAnimation_Controller;

END

class  CGiantGolem : public Engine::CMonsterMain
{


public:
	enum BOSSPATTERN { PAT_IDLE, PAT_APEAR , PAT_PUNCH , PAT_STOMP , PAT_CICLE , PAT_FIREBALL , PAT_END };

private:
	explicit CGiantGolem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGiantGolem(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
	void Shooting(void);
private:
	HRESULT		Add_Component(void);
	void		Preset_Animation();

	void Animation_Render();

public:
	static CGiantGolem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXVECTOR3 m_vBodyPos;
	float		m_fAngle = 0;

	float		m_fPatternTime = 0;
	float		m_fPatternDelay = 4;

	int		m_iMaxPatternNum = 6;
	int		m_iPatternNum	 = 0;

	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vShootPos;

	D3DXVECTOR3 m_vLookPos;


	int			m_f = 0;
	bool		m_b = false;
	float		m_fShotingLate = 0;
	float		m_fShotingDelay = 1.8;


	Engine::CAnimation_Controller* m_pAnimationController;
	BOSSPATTERN						m_ePattern = PAT_IDLE;

private:
	virtual void Free(void) override;

};


#endif // GiantGolem_h__
