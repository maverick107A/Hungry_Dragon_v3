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
	float			m_fSpeed = 10.f;
	float			m_fAngleSpeed = 0.05f;

public:
	static CPFly*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PFly_h__
