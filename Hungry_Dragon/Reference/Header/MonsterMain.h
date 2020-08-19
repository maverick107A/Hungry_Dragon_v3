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

class ENGINE_DLL CMonsterMain : public Engine::CGameObject
{
protected:
	enum MONSTERSTATE { MONSTER_IDLE, MONSTER_REBORN , MONSTER_ACTIVATE, MONSTER_SUICIDE, MONSTER_LAYDEAD , MONSTER_DEACTIVATE, MONSTER_DYING , MONSTER_END };

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
	CBaseLand*	Get_Terrain() { return m_pTerrain; }

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);

protected:
	Engine::CTexture_Cube*		m_pBufferCubeCom = nullptr;
	Engine::CMonsterBoard*		m_pBufferBoradCom = nullptr;
	Engine::CVICustom*			m_pBufferMeshCom = nullptr;
	Engine::CVICustom*			m_pBufferBodyMeshCom = nullptr;
	Engine::CVICustom*			m_pBufferHeadMeshCom = nullptr;

	Engine::CVICustom*			m_pBufferChrystalMeshCom = nullptr;

	Engine::CTexture*			m_pTextureCom = nullptr;
	Engine::CBaseLand*			m_pTerrain = nullptr;
	CTerrain_Locater*			m_ptempTerain = nullptr;
	Engine::CResources*			m_pParticle = nullptr;

	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					vPlayerPos;
	int							m_iEvent = 0;

	FRAME						m_tFrame;
	MONSTERSTATE				m_preState;
	MONSTERSTATE				m_eState;


	float						m_fPlayerDistance;
	float						m_fDistance;
	float						m_fSpeed;
	float						m_fHeight;


	float						m_fMonster_HP;
	float						m_fMonster_MaxHP;
	float						m_fScale;
	float						m_fMaxScale;
	float						m_fDamaged;



public:
	static CMonsterMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;

};

END
#endif // MonsterMain_h__