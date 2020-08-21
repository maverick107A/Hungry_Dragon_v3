#ifndef PlayerState_h__
#define PlayerState_h__

#include "Component.h"

BEGIN(Engine)
class CPlayerMain;
class ENGINE_DLL CPlayerState : public CComponent
{
protected:
	explicit CPlayerState(void);
	explicit CPlayerState(const CPlayerState& rhs);
	virtual ~CPlayerState(void);

public:
	virtual void Enter_State(CPlayerMain* _pPlayer) PURE;
	virtual void Update_State(const float& fTimeDelta) PURE;
	virtual void Out_State() PURE;
	virtual void LateUpdate_State() {};

protected:
	CPlayerMain*				m_pPlayer = nullptr;

protected:
	bool Land_Check(float* _fHeight = nullptr, _vec3* _vNorm = nullptr);
	void Aim();

public:
	static CPlayerState*		Create(void) { return nullptr; }
	virtual CComponent*			Clone(void) { return nullptr; }

protected:
	virtual void Free(void);

};
END
#endif // PlayerState_h__
