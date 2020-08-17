#ifndef PBreathFly_h__
#define PBreathFly_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPBreathFly : public CPlayerState
{
private:
	explicit CPBreathFly(void);
	explicit CPBreathFly(const CPBreathFly& rhs);
	virtual ~CPBreathFly(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	float			m_fSpeed = 40.f;
	float			m_fBoostMulti = 100.f;
	float			m_fAngleSpeed = 0.1f;
	float			m_fDamping = 0.85f;
	_vec3			m_vSpeed = {0.f,0.f,0.f};

public:
	static CPBreathFly*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PBreathFly_h__
