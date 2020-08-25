#ifndef MonsterMain_h__
#define MonsterMain_h__

#include "GameObject.h"

class CTerrain_Locater;

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CMonsterBoard;
class CTransform;
class CResources;
class CTerrain;
class CBaseLand;
class CAtkPart;
class CVICustom;
class CHeightCol;
class CAnimationTransform;

class ENGINE_DLL CMonsterMain : public Engine::CGameObject
{

public:
	enum MONSTERSTATE { MONSTER_IDLE, MONSTER_REBORN , MONSTER_ACTIVATE, MONSTER_SUICIDE, MONSTER_LAYDEAD , MONSTER_DEACTIVATE, MONSTER_DYING , MONSTER_DIG, MONSTER_END };
	enum MONSTERTYPE { BUFF_HP, BUFF_MP , BUFF_SP, BUFF_EXP, BUFF_NONE, BUFF_END };
	enum BOSSPARTS { PART_HEAD, PART_BODY, PART_LEFTARM, PART_RIGHTARM ,  PART_LEFTHAND , PART_RIGHTHAND, PARTS_END };
	enum MONSTERPARTS { MOB_BODY, MOB_LEFTWING, MOB_RIGHTWING, MOB_END };
	enum MONSTERVARIATION { MONSTER_JUMP, MONSTER_CHASE, MONSTER_FLY, MONSTER_RUN, MONSTER_RANDGOLEM, MONSTER_BAT, MONSTER_FLYGOLEM, MONSTER_FLYCHASEGOLEM, MONSTER_FLYRUNGOLEM, MONSTER_BOSSGOLEM, MONSTER_CAVEBAT , MONSTER_HORIZONBAT, MONSTER_VARIEND };


protected:
	explicit CMonsterMain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonsterMain(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
	virtual void State_Change();

public:
	void		 Dead_Monster();
	virtual float		Ride_Terrain();

	//가의묵이 추가한 충돌확인용 임시 함수
	void		Kill_Monster(const float& fTimeDelta);
	void		Kill_Lay_Monster(const float & fTimeDelta);


public:
	void Set_State(MONSTERSTATE _State) { m_eState = _State ; }
	MONSTERSTATE Get_State() { return m_eState; }
	CBaseLand*	Get_Terrain(_uint _uNum);

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);
public:
	Engine::CTransform* Get_Transform() { return m_pTransform; }
protected:
	Engine::CTexture_Cube*		m_pBufferCubeCom = nullptr;
	Engine::CMonsterBoard*		m_pBufferBoradCom = nullptr;
	Engine::CVICustom*			m_pBufferMeshCom = nullptr;
	Engine::CVICustom*			m_pBufferBodyMeshCom = nullptr;
	Engine::CVICustom*			m_pBufferHeadMeshCom = nullptr;
	Engine::CVICustom*			m_pBufferChrystalMeshCom = nullptr;

	CAnimationTransform*		m_pPartsTrans[PARTS_END];
	CAnimationTransform*		m_pMobPartsTrans[MOB_END];


	CTransform*					m_pAuraTransform = nullptr;
	Engine::CTexture*			m_pAuraTextureCom = nullptr;

	Engine::CTexture*			m_pTextureCom = nullptr;
	Engine::CHeightCol**		m_pTerrain = nullptr;
	CTerrain_Locater*			m_ptempTerrain = nullptr;
	Engine::CResources*			m_pParticle = nullptr;
	Engine::CTransform*			 m_pPlayerTransformCom = nullptr;

	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					vPlayerPos;
	D3DXVECTOR3					m_vAuraPos;
	int							m_iEvent = 0;

	FRAME						m_tFrame;
	MONSTERSTATE				m_preState;
	MONSTERSTATE				m_eState;
	MONSTERTYPE					m_eType = BUFF_NONE;
	MONSTERVARIATION			m_eVariation = MONSTER_BOSSGOLEM;
	float						m_fPlayerDistance;
	float						m_fDistance;
	float						m_fSpeed;
	float						m_fHeight;
	float						m_fDetect_Range;
	float						m_fDead_Range;


	
	float						m_fMonster_HP;
	float						m_fMonster_MaxHP;
	float						m_fScale;
	float						m_fMaxScale;
	float						m_fDamaged;
	D3DXCOLOR					m_tDeadColor;

	float						m_fParticleLifeTime=1.f;

public:
	static CMonsterMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;

};

END
#endif // MonsterMain_h__