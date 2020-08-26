#ifndef PartWind_h__
#define PartWind_h__

#include "Particle.h"

#include "TimerMgr.h"


BEGIN(Engine)

class CPlayerMain;

class ENGINE_DLL CPart_Wind :public CParticle
{
public:
	explicit CPart_Wind(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPart_Wind(const CPart_Wind& rhs);
	explicit CPart_Wind(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox * boundingBox, int numParticle, float _fSize);
	virtual ~CPart_Wind(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);
	void Set_Player(CPlayerMain* _pPlayer);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int	Update_Component(const _float& _fTimeDelta);

public:
	static CPart_Wind* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize = 0.25f);
	virtual CResources*	Clone(_vec3 _origin, BoundingBox _boundingBox);
	virtual void Free(void);

private:
	CPlayerMain*	m_pPlayer;
};


END
#endif
