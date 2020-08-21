#include "Animator.h"

#include "Export_Function.h"

USING(Engine)

CAnimator::CAnimator(void)
{
}

CAnimator::CAnimator(const CAnimator & rhs)
{
	m_arrFrame = rhs.m_arrFrame;
	m_arrMaxFrame = rhs.m_arrMaxFrame;
	m_maxFrame = rhs.m_maxFrame;
	m_movementList = rhs.m_movementList;
}

CAnimator::~CAnimator(void)
{
}

_int CAnimator::Update_Component(const _float & fTimeDelta)
{
	return 0;
}

//월드 프레임을 애니메이터 프레임 단위로 가공
void CAnimator::Update_Frame(_float _addFrame)
{
	for (size_t i = 0; i < m_arrFrame.size(); ++i)
	{
		m_arrFrame[i] += _addFrame;
		while (m_arrFrame[i] >= m_arrMaxFrame[i] + 1.f)
		{
			m_arrFrame[i] -= m_arrMaxFrame[i] + 1.f;
		}
	}
}

void CAnimator::Insert_Scale(_int _targetIndex, _int _targetFrame, _vec3 _vecScale)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find!=m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecScale = _vecScale;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecScale = _vecScale;
		tempMovement.vecTrans = _vec3(0.f,0.f,0.f);
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
		
	}
}

void CAnimator::Insert_Rotate(_int _targetIndex, _int _targetFrame, _vec3 _vecRot)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecRot = _vecRot;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vecRot;
		tempMovement.vecScale = _vec3(1.f,1.f,1.f);
		tempMovement.vecTrans = _vec3(0.f, 0.f, 0.f);
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

void CAnimator::Insert_Trans(_int _targetIndex, _int _targetFrame, _vec3 _vecTrans)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecTrans = _vecTrans;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vec3(0.f,0.f,0.f);
		tempMovement.vecScale = _vec3(1.f, 1.f, 1.f);
		tempMovement.vecTrans = _vecTrans;
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

void CAnimator::Insert_Revolute(_int _targetIndex, _int _targetFrame, _vec3 _vec3Parent, _vec3 _vecRev)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}
	
	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecParent = _vec3Parent;
		iter_find->vecRevolution = _vecRev;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vecRev;
		tempMovement.vecRevParent = _vec3Parent;
		tempMovement.vecRot = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecScale = _vec3(1.f, 1.f, 1.f);
		tempMovement.vecTrans = _vec3(0.f,0.f,0.f);
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

void CAnimator::Insert_Idle(_int _targetIndex,_int _targetFrame)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();

	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	MOVEMENT idleMove;
	idleMove.tFrame = _targetFrame;
	idleMove.vecScale = _vec3(1.f, 1.f, 1.f);
	idleMove.vecRot = _vec3(0.f, 0.f, 0.f);
	idleMove.vecTrans = _vec3(0.f, 0.f, 0.f);
	idleMove.vecRevParent = _vec3(0.f, 0.f, 0.f);
	idleMove.vecRevolution = _vec3(0.f, 0.f, 0.f);
	idleMove.vecParent = _vec3(0.f, 0.f, 0.f);

	if (iter_find != m_movementList[_targetIndex].end())
	{
		(*iter_find) = idleMove;
	}
	else
	{
		m_movementList[_targetIndex].emplace_back(idleMove);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}

	
}

void CAnimator::Add_Scale(_int _targetIndex, _int _targetFrame, _vec3 _vecScale)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecScale += _vecScale;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecScale = _vecScale;
		tempMovement.vecTrans = _vec3(0.f, 0.f, 0.f);
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

void CAnimator::Add_Rotate(_int _targetIndex, _int _targetFrame, _vec3 _vecRot)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame = _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecRot += _vecRot;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vecRot;
		tempMovement.vecScale = _vec3(1.f, 1.f, 1.f);
		tempMovement.vecTrans = _vec3(0.f, 0.f, 0.f);
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

void CAnimator::Add_Trans(_int _targetIndex, _int _targetFrame, _vec3 _vecTrans)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	if (m_maxFrame < _targetFrame)
	{
		m_maxFrame += _targetFrame;
	}

	vector<MOVEMENT>::iterator iter_find = m_movementList[_targetIndex].begin();
	for (; iter_find != m_movementList[_targetIndex].end(); ++iter_find)
	{
		if ((*iter_find).tFrame == _targetFrame)
		{
			break;
		}
	}

	if (iter_find != m_movementList[_targetIndex].end())
	{
		iter_find->vecTrans = _vecTrans;
	}
	else
	{
		MOVEMENT tempMovement;
		tempMovement.tFrame = _targetFrame;
		tempMovement.vecParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecRot = _vec3(0.f, 0.f, 0.f);
		tempMovement.vecScale = _vec3(1.f, 1.f, 1.f);
		tempMovement.vecTrans = _vecTrans;
		m_movementList[_targetIndex].emplace_back(tempMovement);
		m_arrMaxFrame[_targetIndex] = _targetFrame;
	}
}

CAnimator* CAnimator::Create(void)
{
	CAnimator* pInstance = new CAnimator;

	return pInstance;
}

CComponent * CAnimator::Clone(void)
{
	return new CAnimator(*this);
}

void CAnimator::Free(void)
{
}

_int CAnimator::Get_FrameArraySize(_int _frame)
{
	return (int)m_movementList[_frame].size();
}

_float CAnimator::Get_NowFrame(_int _targetIndex)
{
	if ((size_t)_targetIndex >= m_arrFrame.size())
		return 0.f;
	return m_arrFrame[_targetIndex];
}

_int CAnimator::Get_MaxFrame(_int _targetIndex)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return -1;

	return m_movementList[_targetIndex].back().tFrame;
}

MOVEMENT CAnimator::Get_Movement(_int _targetIndex)
{
	//없는거 찾지 마라.
	if ((size_t)_targetIndex >= m_movementList.size())
		return MOVEMENT();

	if (m_movementList[_targetIndex].size() == (size_t)1)
	{
		return m_movementList[_targetIndex].front();
	}

	if (m_movementList[_targetIndex].back().tFrame == (int)m_arrFrame[_targetIndex])
	{
		return m_movementList[_targetIndex].front();
	}

	for (vector<MOVEMENT>::iterator iter = m_movementList[_targetIndex].begin(); iter != m_movementList[_targetIndex].end(); ++iter)
	{
		if (iter->tFrame > m_arrFrame[_targetIndex])
		{
			return (*iter);
		}
	}

	return m_movementList[_targetIndex].back();
}

_int CAnimator::Get_TotalMaxFrame()
{
	return m_maxFrame;
}

_int CAnimator::Get_PartsCnt()
{
	return (_int)m_movementList.size();
}

void CAnimator::Set_PartsSize(_int _partSize)
{
	if (_partSize <= 0)
	{
		return;
	}

	m_movementList.reserve(_partSize);

	for (int i = 0; i < _partSize; ++i)
	{
		vector<MOVEMENT> tempMoveVector;
		m_movementList.emplace_back(tempMoveVector);
		m_arrMaxFrame.emplace_back(0);
		m_arrFrame.emplace_back(0.f);
		Insert_Idle(i, 0);
	}
}

void CAnimator::Set_SpecificFrame(_int _partsIndex)
{
	if ((size_t)_partsIndex >= m_arrFrame.size())
		return;

	m_arrFrame[_partsIndex] = 0.f;
}
