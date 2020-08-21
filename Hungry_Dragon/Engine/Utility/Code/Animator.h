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
	_float		Get_NowFrame();
	_int		Get_MaxFrame(int _targetIndex);
	_matrix		Get_MoveResult(LPDIRECT3DDEVICE9 pGraphicDev, _matrix _matTarget,_int _index);
	MOVEMENT	Get_Movement(_int _targetIndex);
	_int		Get_TotalMaxFrame();
	_int		Get_PartsCnt();

	void		Set_PartsSize(_int _partSize);

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	void			Update_Frame(_float _nowFrame);

public:
	_int	Register_MoveTarget();

	void	Insert_Scale(_int _targetIndex,_int _targetFrame,_vec3 _vecScle);
	void	Insert_Rotate(_int _targetIndex, _int _targetFrame,_vec3 _vecRot);
	void	Insert_Trans(_int _targetIndex, _int _targetFrame,_vec3 _vecTrans);
	void	Insert_Revolute(LPDIRECT3DDEVICE9& pGraphicDev,_int _targetIndex, _int _targetFrame,_vec3 _vec3Parent,_vec3 _vecRev);
	void	Insert_Idle(_int exceptTarget,_int targetFrame);

public:
	static CAnimator* Create(void);
	virtual CComponent* Clone(void);

private:
	virtual void Free(void) override;

private:
	vector<vector<MOVEMENT>>		m_movementList;
	_int							m_maxFrame=0;
	_float							m_nowFrame = 0;
};

END
#endif
