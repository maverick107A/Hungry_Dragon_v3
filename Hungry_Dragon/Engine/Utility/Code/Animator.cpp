#include "Animator.h"

#include "Export_Function.h"

USING(Engine)

CAnimator::CAnimator(void)
{
}

CAnimator::CAnimator(const CAnimator & rhs)
{
	m_nowFrame = m_nowFrame;
	m_maxFrame = m_maxFrame;

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
void CAnimator::Update_Frame(_float _nowFrame)
{
	m_nowFrame = _nowFrame;
	while (m_nowFrame < (_float)m_maxFrame+1.f) {
		m_nowFrame -= (_float)m_maxFrame + 1.f;
	}
}

_int CAnimator::Register_MoveTarget()
{
	//지금 등록하는 트랜스폼이 저장될 위치==벡터의 마지막
	_int tempIndex = (_int)m_movementList.size();

	//기본 위치
	MOVEMENT idleMovement;
	idleMovement.tFrame = 0;
	idleMovement.vecScale=_vec3(1.f,1.f,1.f);
	idleMovement.vecRot=_vec3(0.f,0.f,0.f);
	idleMovement.vecTrans = _vec3(0.f, 0.f, 0.f);
	idleMovement.vecRevParent = _vec3(0.f, 0.f, 0.f);
	idleMovement.vecRevolution = _vec3(0.f, 0.f, 0.f);
	idleMovement.vecParent = _vec3(0.f, 0.f, 0.f);
	
	//움직임을 저장할 벡터
	vector<MOVEMENT> tempVector;
	tempVector.emplace_back(idleMovement);

	//만든 벡터를 멤버 변수 벡터에 삽입
	m_movementList.emplace_back(tempVector);

	return tempIndex;
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
	}
}

void CAnimator::Insert_Revolute(LPDIRECT3DDEVICE9& pGraphicDev,_int _targetIndex, _int _targetFrame, _vec3 _vec3Parent, _vec3 _vecRev)
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
	}
}

void CAnimator::Insert_Idle(_int _targetIndex,_int _targetFrame)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return;

	MOVEMENT idleMove;
	idleMove.tFrame = _targetFrame;
	idleMove.vecScale = _vec3(1.f, 1.f, 1.f);
	idleMove.vecRot = _vec3(0.f, 0.f, 0.f);
	idleMove.vecTrans = _vec3(0.f, 0.f, 0.f);
	idleMove.vecRevParent = _vec3(0.f, 0.f, 0.f);
	idleMove.vecRevolution = _vec3(0.f, 0.f, 0.f);
	idleMove.vecParent = _vec3(0.f, 0.f, 0.f);

	m_movementList[_targetIndex].emplace_back(idleMove);
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

_float CAnimator::Get_NowFrame()
{
	return m_nowFrame;
}

_int CAnimator::Get_MaxFrame(int _targetIndex)
{
	if ((size_t)_targetIndex >= m_movementList.size())
		return -1;

	return m_movementList[_targetIndex].back().tFrame;
}

_matrix CAnimator::Get_MoveResult(LPDIRECT3DDEVICE9 pGraphicDev, _matrix _matTarget, _int _index)
{
	/*_matrix  matWorld;
	_matrix  matWorldInverse;
	_matrix  matParent = _matTarget;

	pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixInverse(&matWorldInverse, nullptr,&matWorld);

	_matTarget = _matTarget*matWorldInverse;

	MOVEMENT nowMovement = m_movementList[_index][(int)m_nowFrame];
	_matrix	 matMovement = nowMovement.matScale*nowMovement.matRot*nowMovement.matTrans*nowMovement.matRevolution*matParent;
	_matTarget = _matTarget*matMovement*matWorld;*/

	return _matTarget;
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

	if (m_movementList[_targetIndex].back().tFrame == (int)m_nowFrame)
	{
		return m_movementList[_targetIndex].front();
	}
	else if (m_movementList[_targetIndex].back().tFrame < (int)m_nowFrame)
	{
		int tempFrame = ((int)m_nowFrame) % m_movementList[_targetIndex].back().tFrame;
		
		for (vector<MOVEMENT>::iterator iter = m_movementList[_targetIndex].begin(); iter != m_movementList[_targetIndex].end(); ++iter)
		{
			if (iter->tFrame > tempFrame)
			{
				return (*iter);
			}
		}
	}

	for (vector<MOVEMENT>::iterator iter = m_movementList[_targetIndex].begin(); iter != m_movementList[_targetIndex].end(); ++iter)
	{
		if (iter->tFrame > m_nowFrame)
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
		Insert_Idle(i, 0);
	}
}
