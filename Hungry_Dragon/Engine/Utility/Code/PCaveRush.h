#ifndef PCaveRush_h__
#define PCaveRush_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPCaveRush : public CPlayerState
{
private:
	explicit CPCaveRush(void);
	explicit CPCaveRush(const CPCaveRush& rhs);
	virtual ~CPCaveRush(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	float					m_fAngle = 0.f;
	float					m_fAngularSpeed = 0.f;
	float					m_fSpeed = 0.f;
	float					m_fMaxSpeed = 10.f;
	float					m_fAccle = 10.f;

public:
	static CPCaveRush*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PCaveRush_h__
