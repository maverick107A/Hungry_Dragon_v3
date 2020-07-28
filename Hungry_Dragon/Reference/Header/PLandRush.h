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
	virtual void Out_State();

private:
	float			m_fSpeed = 10.f;

public:
	static CPLandRush*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PLandRush_h__
