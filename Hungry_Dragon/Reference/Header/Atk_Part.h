#ifndef AtkPart_h__
#define AtkPart_h__

#include "Particle.h"

#include "TimerMgr.h"

BEGIN(Engine)
class ENGINE_DLL CAtk_Part :public CParticle {
public:
	explicit CAtk_Part(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAtk_Part(const CAtk_Part& rhs);
	explicit CAtk_Part(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize);
	virtual ~CAtk_Part(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int	Update_Component(const _float& _fTimeDelta);

public:
	static CAtk_Part* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize=0.25f);
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
