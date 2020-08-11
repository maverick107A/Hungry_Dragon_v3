#ifndef MonsterMain_h__
#define MonsterMain_h__

#include "GameObject.h"


BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CMonsterBoard;
class CTransform;
class CResources;
class CTerrain;
class CBaseLand;
class CAtkPart;

class ENGINE_DLL CMonsterMain : public Engine::CGameObject
{
protected:
	enum MONSTERSTATE { MONSTER_IDLE, MONSTER_REBORN , MONSTER_ACTIVATE , MONSTER_DEACTIVATE, MONSTER_END };

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
	void	    Dead_Monster(const float& fTimeDelta);
	float		Ride_Terrain();
public:
	void Set_State(MONSTERSTATE _State) { m_eState = _State ; }
	MONSTERSTATE Get_State() { return m_eState; }


private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);

protected:
	Engine::CTexture_Cube*		m_pBufferCubeCom = nullptr;
	Engine::CMonsterBoard*		m_pBufferBoradCom = nullptr;

	
	Engine::CTexture*			m_pTextureCom = nullptr;
	Engine::CBaseLand*			m_pTerrain = nullptr;
	Engine::CResources*			m_pParticle = nullptr;

	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					vPlayerPos;
	int							m_iEvent = 0;

	FRAME								m_tFrame;
	MONSTERSTATE						m_preState;
	MONSTERSTATE						m_eState;


	float						m_fParticle_Speed = 0;
	float						m_fPlayerDistance;
	float						m_fDistance;
	float						m_fSpeed;
	float						m_fScale;
	float						m_prefScale;

public:
	static CMonsterMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;

};

END
#endif // MonsterMain_h__