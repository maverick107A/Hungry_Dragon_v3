#ifndef PLandRush_h__
#define PLandRush_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPLandRush : public CPlayerState
{
private:
	explicit CPLandRush(void);
	explicit CPLandRush(const CPLandRush& rhs);
	virtual ~CPLandRush(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void LateUpdate_State();
	virtual void Out_State();

private:
	float			m_fSpeed = 200.f;
	float			m_fBoostMulti = 10.f;
	float			m_fAngleSpeed = 0.1f;
	float			m_fDamping = 0.85f;
	_vec3			m_vSpeed = { 0.f,0.f,0.f };

public:
	static CPLandRush*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PLandRush_h__
