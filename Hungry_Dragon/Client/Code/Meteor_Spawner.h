#ifndef Meteor_Spawner_h__
#define Meteor_Spawner_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CBaseLand;

END

class CMeteor_Object;

USING(Engine)

class CMeteor_Spawner : public Engine::CGameObject
{
private:
	explicit CMeteor_Spawner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor_Spawner(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Instantiate_Meteor(_vec3& vPos);


private:
	HRESULT		Add_Component(void);
	

private:
	Engine::CTransform*		m_pTransform;
	Engine::CTransform*		m_pPlayerTrans = nullptr;
	vector<CMeteor_Object*>	m_vecObjectPool;
	vector<CMeteor_Object*>::iterator	m_iterFinder;		// ¼øÈ¸ÀÚ
	CMeteor_Object*				m_pMeteor;
	_bool					m_bActive = true;
	_float					m_fSummonTick = 0.f;
	_float					m_fSummonTime = 0.25f;
public:
	static CMeteor_Spawner*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
