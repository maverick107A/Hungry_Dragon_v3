#ifndef Static_Behavior_h__
#define Static_Behavior_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CStatic_Behavior : public CComponent
{
private:
	explicit CStatic_Behavior(void);
	explicit CStatic_Behavior(const CStatic_Behavior& rhs);
	virtual ~CStatic_Behavior(void);

public:
	void			Get_Info(INFO eType, _vec3* pInfo);

	void			Add_Trans(const _vec3* const pDir);
	void			Add_Trans(const _float _x, const _float _y, const _float _z);

public:
	HRESULT			Ready_Transform(void);
	virtual _int	Update_Component(const _float& fTimeDelta);
	void			Set_Transform(LPDIRECT3DDEVICE9& pGraphicDev);

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
	static CStatic_Behavior*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // Transform_h__
