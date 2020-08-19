#ifndef AnimationTransform_h__
#define AnimationTransform_h__

#include "Transform.h"
BEGIN(Engine)

class ENGINE_DLL CAnimationTransform : public CTransform
{
private:
	explicit CAnimationTransform(void);
	explicit CAnimationTransform(const CAnimationTransform& rhs);
	virtual ~CAnimationTransform(void);

public:
	HRESULT			Ready_Transform(void);
	virtual _int	Update_Component(const _float& fTimeDelta);
	void			Set_Transform(LPDIRECT3DDEVICE9& pGraphicDev);

public:
	void			Rotation(ROTATION eType, const _float& fAngle);

public:
	static CAnimationTransform*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // AnimationTransform_h__
