#ifndef PLandIdle_h__
#define PLandIdle_h__

#include "PlayerState.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CPLandIdle : public CPlayerState
{
private:
	explicit CPLandIdle(void);
	explicit CPLandIdle(const CPLandIdle& rhs);
	virtual ~CPLandIdle(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer);
	virtual void Update_State(const float& fTimeDelta);
	virtual void Out_State();
	virtual void LateUpdate_State();

public:
	static CPLandIdle*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PLandIdle_h__
