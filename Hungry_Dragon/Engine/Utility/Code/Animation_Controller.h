#ifndef Animation_Controller_h__
#define Animation_Controller_h__

#include "Component.h"
#include "Animator.h"

BEGIN(Engine)

class ENGINE_DLL CAnimation_Controller :public CComponent {
private:
	explicit CAnimation_Controller(void);
	explicit CAnimation_Controller(const CAnimation_Controller& rhs);
	virtual ~CAnimation_Controller(void);

public:
	MOVEMENT Get_Movement(_int _animatorIndex,_int _partIndex);
	void Set_FrameSpeed( _float _fSpeed);

public:
	virtual _int Update_Component(const _float& fTimeDelta);

public:
	void Add_Animator(_int _clonedAnimationPos);

	//Add는 합연산임.
	void Insert_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale);
	void Add_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale);
	void Insert_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate);
	void Add_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate);
	void Insert_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans);
	void Add_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans);
	void Insert_Revolute(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 vecParent,_vec3 _vecRevolution);
	void Insert_Idle(_int animatorIndex, _int _partIndex, _int _frameIndex);

public:
	static CAnimation_Controller* Create(void);
	virtual CComponent* Clone(void);

private:
	virtual void Free(void)override;

private:
	vector<CAnimator*>	m_arrAnimatior;
	_int				m_iAnimatorCnt;
	_float				m_fNowFrame;
	_int				m_iMaxFrame;
	_float				m_fFrameSpeed;
};
END

#endif // !Animation_Controller_h__
