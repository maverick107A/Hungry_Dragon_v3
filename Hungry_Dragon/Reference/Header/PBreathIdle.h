#ifndef PBreathIdle_h__
#define PBreathIdle_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPBreathIdle : public CPlayerState
{
private:
	explicit CPBreathIdle(void);
	explicit CPBreathIdle(const CPBreathIdle& rhs);
	virtual ~CPBreathIdle(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	float					m_fAngle = 0.f;

public:
	static CPBreathIdle*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PBreathIdle_h__
