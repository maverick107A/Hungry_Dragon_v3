#ifndef ParticleMgr_h__
#define ParticleMgr_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CResources;
class CAtkPart;

class ENGINE_DLL CParticleMgr : public CBase
{
	DECLARE_SINGLETON(CParticleMgr)

private:
	explicit CParticleMgr(void);
	virtual ~CParticleMgr(void);
public:
	void Particle_Update(const float& fTimeDelta);
	void Particle_Render();
	void Particle_Create(Engine::CResources* _tempParticle);

private:
	list<Engine::CResources*>  m_arrParticle;

public:
	virtual void Free(void) override;
};

END

#endif