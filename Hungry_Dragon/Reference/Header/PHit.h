#ifndef PHit_h__
#define PHit_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPHit : public CPlayerState
{
private:
	explicit CPHit(void);
	explicit CPHit(const CPHit& rhs);
	virtual ~CPHit(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void LateUpdate_State();
	virtual void Out_State();

private:
	float					m_fAngle = 0.f;
	float					m_fDis = 100.f;
	float					m_fTime = 1.f;

public:
	static CPHit*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PHit_h__
