#ifndef Animator_h__
#define Animator_h__

#include "Component.h"

BEGIN(Engine)

class CTransform;


//뒤집어서 실행하는거에 대한 방법 고안 필요
class ENGINE_DLL CAnimator :public CComponent
{	
private:
	explicit CAnimator(void);
	explicit CAnimator(const CAnimator& rhs);
	virtual ~CAnimator(void);

public:
	_int	Get_FrameArraySize(_int _frame);
	_int	Get_TotalMaxFrame();
	_matrix	Get_MoveResult(LPDIRECT3DDEVICE9 pGraphicDev, _matrix _matTarget,_int _index);

public:
	virtual _int Update_Component(const _float& fTimeDelta);

public:
	_int	Register_MoveTarget();
	void	Insert_Scale(_int _targetIndex,_int _targetFrame,_vec3 _vecScle);
	void	Insert_Ratate(_int _targetIndex, _int _targetFrame,_vec3 _vecRot);
	void	Insert_Trans(_int _targetIndex, _int _targetFrame,_vec3 _vecTrans);
	void	Insert_Revolute(LPDIRECT3DDEVICE9& pGraphicDev,_int _targetIndex, _int _targetFrame,_vec3 _vec3Parent,_vec3 _vecRev);
	void	Insert_Idle(_int exceptTarget);
	void	Set_FrameSpeed(float _fSpeed)
	{
		m_fFrmaeSpeed = _fSpeed;
	}

public:
	static CAnimator* Create(void);
	virtual CComponent* Clone(void);

private:
	virtual void Free(void) override;

private:
	vector<vector<MOVEMENT>>	m_moventList;
	_int						m_maxFrame=0;
	_float						m_nowFrame = 0;
	bool						m_bFlow = true;
	float						m_fFrmaeSpeed = 1.f;
};

END
#endif
