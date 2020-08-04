#ifndef PFly_h__
#define PFly_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPFly : public CPlayerState
{
private:
	explicit CPFly(void);
	explicit CPFly(const CPFly& rhs);
	virtual ~CPFly(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	float			m_fSpeed = 50.f;
	float			m_fBoostMulti = 2.f;
	float			m_fAngleSpeed = 0.1f;
	float			m_fDamping = 0.95f;
	_vec3			m_vSpeed = {0.f,0.f,0.f};

public:
	static CPFly*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PFly_h__
