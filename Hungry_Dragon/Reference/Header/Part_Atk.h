#ifndef PartAtk_h__
#define PartAtk_h__

#include "Particle.h"

#include "TimerMgr.h"

BEGIN(Engine)
class ENGINE_DLL CPart_Atk :public CParticle {
public:
	explicit CPart_Atk(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPart_Atk(const CPart_Atk& rhs);
	explicit CPart_Atk(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize);
	virtual ~CPart_Atk(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int	Update_Component(const _float& _fTimeDelta);

public:
	static CPart_Atk* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize=0.25f);
	virtual CResources*	Clone(_vec3 _origin,BoundingBox _boundingBox);
	virtual void Free(void);

private:
	//파티클 가로폭
	_float m_fWidth;

	//파티클 세로폭
	_float m_fHeight;
};

END
#endif
