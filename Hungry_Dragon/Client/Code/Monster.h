#ifndef Monster_h__
#define Monster_h__

#include "Define.h"
#include "GameObject.h"


BEGIN(Engine)

class CCubeTex;
class CTexture;
class CTransform;
class CResources;
class CTerrain;
class CBaseLand;
END
class CMonster : public Engine::CGameObject
{
	enum STATE { MONSTER_IDLE, MONSTER_MOVE, MONSTER_RUN, MONSTER_ATTACK, MONSTER_JUMP, MONSTER_STAN , MONSTER_END };
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
public:
	void	Dead_Monster(const float& fTimeDelta);
	void		Ride_Terrain();
public:
private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);
protected:
	Engine::CTransform*			m_pTransform = nullptr;
	Engine::CCubeTex*			m_pBufferCom = nullptr;
	Engine::CTexture*			m_pTextureCom = nullptr;
	Engine::CBaseLand*			m_pTerrain = nullptr;
	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					vPlayerPos;
	int							m_iEvent = 0;
	bool						m_bDead = false;
	bool						m_bActivate = false;
	float						fDistance;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;
public:
	list<Engine::CResources*>  m_arrParticle;


};

#endif // Monster_h__