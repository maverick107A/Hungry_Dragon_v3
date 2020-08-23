#ifndef Animator_h__
#define Animator_h__

#include "Component.h"

BEGIN(Engine)

class CTransform;


class ENGINE_DLL CAnimator :public CComponent
{	
private:
	explicit CAnimator(void);
	explicit CAnimator(const CAnimator& rhs);
	virtual ~CAnimator(void);

public:
	_int		Get_FrameArraySize(_int _frame);
	_float		Get_NowFrame(_int _targetIndex);
	_int		Get_MaxFrame(_int _targetIndex);
	MOVEMENT	Get_Movement(_int _targetIndex);
	_int		Get_TotalMaxFrame();
	_int		Get_PartsCnt();

	void		Set_PartsSize(_int _partSize);
	void		Set_SpecificFrame(_int _partsIndex);

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	_bool			Update_Frame(_float _addFrame);

public:
	void	Insert_Scale(_int _targetIndex,_int _targetFrame,_vec3 _vecScle);
	void	Insert_Rotate(_int _targetIndex, _int _targetFrame,_vec3 _vecRot);
	void	Insert_Trans(_int _targetIndex, _int _targetFrame,_vec3 _vecTrans);
	void	Insert_Revolute(_int _targetIndex, _int _targetFrame,_vec3 _vec3Parent,_vec3 _vecRev);
	void	Insert_Idle(_int exceptTarget,_int targetFrame);

	void	Add_Scale(_int _targetIndex, _int _targetFrame, _vec3 _vecScle);
	void	Add_Rotate(_int _targetIndex, _int _targetFrame, _vec3 _vecRot);
	void	Add_Trans(_int _targetIndex, _int _targetFrame, _vec3 _vecTrans);

public:
	static CAnimator* Create(void);
	virtual CComponent* Clone(void);

private:
	virtual void Free(void) override;

private:
	vector<vector<MOVEMENT>>		m_movementList;
	vector<_int>					m_arrMaxFrame;
	vector<_float>					m_arrFrame;
	_int							m_maxFrame;
	_bool							m_bFrameNotReset=true;
};

END
#endif
