#ifndef PartFragile_h__
#define PartFragile_h__

#include "Particle.h"

#include "TimerMgr.h"

BEGIN(Engine)
class ENGINE_DLL CPart_Fragile : public CParticle
{
public:
	explicit CPart_Fragile(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPart_Fragile(const CPart_Fragile& rhs);
	explicit CPart_Fragile(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox* boundingBox, int numParticle, float _fSize);
	virtual ~CPart_Fragile(void);

public:
	void Set_BoundingBox(BoundingBox _boundingBox);
	void Set_Origin(_vec3 _origin);
	void Set_TexArray();
	void Set_TexArrayMFC();

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute);
	virtual _int	Update_Component(const _float& _fTimeDelta);
	virtual void Render_Buffer(void);

public:
	static CPart_Fragile* Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize = 0.25f);
	virtual CResources*	Clone(_vec3 _origin, BoundingBox _boundingBox);
	virtual void Free(void);

private:
	_vec3 m_MoveDirection;
	IDirect3DTexture9* m_arrTex[DIR_END][10];
};

END

#endif
