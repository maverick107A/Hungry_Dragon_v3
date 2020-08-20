#ifndef AnimationTransform_h__
#define AnimationTransform_h__

#include "Component.h"
BEGIN(Engine)

class ENGINE_DLL CAnimationTransform : public CComponent
{
private:
	explicit CAnimationTransform(void);
	explicit CAnimationTransform(const CAnimationTransform& rhs);
	virtual ~CAnimationTransform(void);

public:
	HRESULT			Ready_Transform(void);
	virtual _int	Update_Component(const _float& fTimeDelta);
	void			Set_Transform(LPDIRECT3DDEVICE9& pGraphicDev, _matrix _matWorld);

public:
	void			Rotation(ROTATION eType, const _float& fAngle);

public:
	static CAnimationTransform*		Create(void);
	virtual CComponent*		Clone(void);

private:
	_vec3		m_vAngle = { 0.f,0.f,0.f };
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vRevAngle = { 0.f,0.f,0.f };
	_vec3		m_vMovePos = { 0.f,0.f,0.f };

public:
	_vec3		m_vScale;
	_vec3		m_vAfterAngle = { 0.f,0.f,0.f };
	_vec3		m_vAfterRevAngle = { 0.f,0.f,0.f };
	_vec3		m_vAfterPos = { 0.f,0.f,0.f };
	_matrix		m_matWorld;

	float		m_fDamping = 0.3f;

private:
	virtual void Free(void);

private:
	_matrix nowFrame;
	_matrix nextFrame;
	float tFrame;

};
END
#endif // AnimationTransform_h__
