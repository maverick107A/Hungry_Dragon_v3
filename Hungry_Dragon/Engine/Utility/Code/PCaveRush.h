#ifndef PCaveRush_h__
#define PCaveRush_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPCaveRush : public CPlayerState
{
	enum PHASE {PHASE_ZERO, PHASE_ONE, PHASE_TWO};

private:
	explicit CPCaveRush(void);
	explicit CPCaveRush(const CPCaveRush& rhs);
	virtual ~CPCaveRush(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();

private:
	void Phase_0(const float& fTimeDelta);
	void Phase_1(const float& fTimeDelta);

public:
	void Switch_Phase(int _iPhase);
	
private:
	float					m_fAngle = 0.f;
	float					m_fAngularSpeed = 0.f;
	float					m_fSpeed = 0.f;
	float					m_fUpSpeed = 0.f;
	float					m_fMaxSpeed = 10.f;
	float					m_fAccle = 10.f;
	float					m_fPosZ = 0.f;
	float					m_fPosY = -9.f;
	PHASE					m_ePhase = PHASE::PHASE_ZERO;

public:
	static CPCaveRush*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PCaveRush_h__
