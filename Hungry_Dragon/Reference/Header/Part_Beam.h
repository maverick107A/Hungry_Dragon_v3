#ifndef PartBeam_h__
#define PartBeam_h__

#include "Particle.h"

#include "TimerMgr.h"

BEGIN(Engine)

class CPlayerMain;

class ENGINE_DLL CPart_Beam :public CParticle {
public:
	explicit CPart_Beam(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPart_Beam(const CPart_Beam& rhs);
	explicit CPart_Beam(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox * boundingBox, int numParticle, float _fSize);
	virtual ~CPart_Beam(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);
	void Set_Player(CPlayerMain* _pPlayer);

public:
	virtual void Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int Update_Component(const _float& fTimeDelta);

public:
	void Manual_Reset_Particle();

public:
	static CPart_Beam* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize = 0.25f);
	virtual CResources* Clone(_vec3 _origin, BoundingBox _boundingBox);
	virtual void Free(void);

private:
	//브레스 파티클 깊이
	_float			m_fDepth;
	_float			m_fRadius;
	CPlayerMain*	m_pPlayer;
};

END

#endif