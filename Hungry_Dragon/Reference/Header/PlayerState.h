#ifndef PlayerState_h__
#define PlayerState_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CPlayerState : public CComponent
{
private:
	explicit CPlayerState(void);
	explicit CPlayerState(const CPlayerState& rhs);
	virtual ~CPlayerState(void);

public:
	void			Get_Info(INFO eType, _vec3* pInfo);

public:
	HRESULT			Ready_State(void);
	virtual _int	Update_State(const _float& fTimeDelta);
	void			Set_State(LPDIRECT3DDEVICE9& pGraphicDev);

public:
	void			Rotation(ROTATION eType, const _float& fAngle);
	const _matrix*	Compute_LookAtTarget(const _vec3* pTargetPos);
	void			Chase_Target(const _vec3* pTargetPos, const _float& fSpeed);


public:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale; 
	_vec3		m_vAngle;
	_vec3		m_vTrans;
	_matrix		m_matWorld;

public:
	static CPlayerState*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // PlayerState_h__
