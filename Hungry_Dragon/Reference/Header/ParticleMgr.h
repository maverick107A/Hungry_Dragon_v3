#ifndef ParticleMgr_h__
#define ParticleMgr_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CResources;
class CTransform;
class CAtkPart;

class ENGINE_DLL CParticleMgr : public CBase
{
	DECLARE_SINGLETON(CParticleMgr)

private:
	explicit CParticleMgr(void);
	virtual ~CParticleMgr(void);

public:
	void Ready_ParticleMgr(LPDIRECT3DDEVICE9 _pGraphicDev);
	void Particle_Update(const float& fTimeDelta);
	void Particle_LateUpdate(const float& fTimeDelta);
	void Particle_Render();
	CResources* Particle_Create(Engine::PARTICLEID _eID, const _vec3 _pos);

public:
	bool Set_ParticleTrans(CResources* _particle,_vec3 _pos);

private:
	list<Engine::CResources*>	m_arrParticle;
	list<Engine::_vec3>			m_arrTrans;
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	CTransform*					m_pParticleTrans;
	size_t						m_iParticleLimite  = 30;

public:
	virtual void Free(void) override;
};

END

#endif