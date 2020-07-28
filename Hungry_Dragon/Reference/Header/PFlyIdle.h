#ifndef PFlyIdle_h__
#define PFlyIdle_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPFlyIdle : public CPlayerState
{
private:
	explicit CPFlyIdle(void);
	explicit CPFlyIdle(const CPFlyIdle& rhs);
	virtual ~CPFlyIdle(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	float					m_fAngle = 0.f;

public:
	static CPFlyIdle*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PFlyIdle_h__
