#ifndef PartLeaf_h__
#define PartLeaf_h__

#include "Particle.h"

#include "TimerMgr.h"

BEGIN(Engine)
class ENGINE_DLL CPart_Leaf :public CParticle {
public:
	explicit CPart_Leaf(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPart_Leaf(const CPart_Leaf& rhs);
	explicit CPart_Leaf(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize);
	virtual ~CPart_Leaf(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int	Update_Component(const _float& _fTimeDelta);

public:
	static CPart_Leaf* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize=0.25f);
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
