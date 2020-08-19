#include "Animator.h"

#include "Export_Function.h"

USING(Engine)

CAnimator::CAnimator(void)
{
}

CAnimator::CAnimator(const CAnimator & rhs)
{
	m_moventList.clear();
	m_nowFrame = 0;
	m_maxFrame = 0;
	m_fFrmaeSpeed = rhs.m_fFrmaeSpeed;
}

CAnimator::~CAnimator(void)
{
}

_int CAnimator::Update_Component(const _float & fTimeDelta)
{
	m_nowFrame += fTimeDelta;

	if (m_nowFrame >= m_maxFrame+1)
	{
		m_nowFrame = 0;
	}

	return 0;
}

_int CAnimator::Register_MoveTarget()
{
	//지금 등록하는 트랜스폼이 저장될 위치==벡터의 마지막
	_int tempIndex = (_int)m_moventList.size();

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
	m_moventList.emplace_back(tempVector);

	return tempIndex;
}

void CAnimator::Insert_Scale(_int _targetIndex, _int _targetFrame, _vec3 _vecScale)
{
	if ((size_t)_targetIndex >= m_moventList.size())
		return;

	//없는 프레임을 찾으면 그 프레임까지 자동 확장
	if (_targetFrame > m_maxFrame)
	{
		m_maxFrame = _targetFrame;
		Insert_Idle(-1);
	}

	m_moventList[_targetIndex][_targetFrame].vecScale = _vecScale;
}

void CAnimator::Insert_Ratate(_int _targetIndex, _int _targetFrame, _vec3 _vecRot)
{
	if ((size_t)_targetIndex >= m_moventList.size())
		return;

	//없는 프레임을 찾으면 그 프레임까지 자동 확장
	if (_targetFrame > m_maxFrame)
	{
		m_maxFrame = _targetFrame;
		Insert_Idle(-1);
	}

	m_moventList[_targetIndex][_targetFrame].vecRot = _vecRot;
}

void CAnimator::Insert_Trans(_int _targetIndex, _int _targetFrame, _vec3 _vecTrans)
{
	if ((size_t)_targetIndex >= m_moventList.size())
		return;

	//없는 프레임을 찾으면 그 프레임까지 자동 확장
	if (_targetFrame > m_maxFrame)
	{
		m_maxFrame = _targetFrame;
		Insert_Idle(-1);
	}

	m_moventList[_targetIndex][_targetFrame].vecTrans = _vecTrans;
}

void CAnimator::Insert_Revolute(LPDIRECT3DDEVICE9& pGraphicDev,_int _targetIndex, _int _targetFrame, _vec3 _vec3Parent, _vec3 _vecRev)
{
	if ((size_t)_targetIndex >= m_moventList.size())
		return;

	//없는 프레임을 찾으면 그 프레임까지 자동 확장
	if (_targetFrame > m_maxFrame)
	{
		m_maxFrame = _targetFrame;
		Insert_Idle(-1);
	}
	
	_matrix wordlMatrix;
	//주의! 월드 매트릭스를 올바르게 가져오기 위해서는 먼저 그래픽 디바이스를 여기로 옮겨야 함을 주의하자.
	pGraphicDev->GetTransform(D3DTS_WORLD, &wordlMatrix);
	D3DXMatrixInverse(&wordlMatrix, nullptr ,&wordlMatrix);

	D3DXVec3TransformCoord(&_vec3Parent, &_vec3Parent, &wordlMatrix);

	_matrix matParent, matRevolution;

	m_moventList[_targetIndex][_targetFrame].vecRevParent = _vec3Parent;
	m_moventList[_targetIndex][_targetFrame].vecRevolution = _vecRev;
}

void CAnimator::Insert_Idle(_int exceptTarget)
{
	for (size_t i = 0; i < m_moventList.size(); ++i)
	{
		if (i != exceptTarget)
		{
			for (size_t j = m_moventList[i].size(); j <= (size_t)m_maxFrame; ++j)
			{
				MOVEMENT idleMove;
				idleMove.tFrame = j;
				idleMove.vecScale = _vec3(1.f, 1.f, 1.f);
				idleMove.vecRot = _vec3(0.f, 0.f, 0.f);
				idleMove.vecTrans = _vec3(0.f, 0.f, 0.f);
				idleMove.vecRevParent = _vec3(0.f, 0.f, 0.f);
				idleMove.vecRevolution = _vec3(0.f, 0.f, 0.f);
				idleMove.vecParent = _vec3(0.f, 0.f, 0.f);

				m_moventList[i].emplace_back(idleMove);
			}
		}
	}
}

CAnimator * CAnimator::Create(void)
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
	return (int)m_moventList[_frame].size();
}

_float CAnimator::Get_NowFrame()
{
	return m_nowFrame;
}

_int CAnimator::Get_TotalMaxFrame()
{
	return m_maxFrame;
}

_matrix CAnimator::Get_MoveResult(LPDIRECT3DDEVICE9 pGraphicDev, _matrix _matTarget, _int _index)
{
	/*_matrix  matWorld;
	_matrix  matWorldInverse;
	_matrix  matParent = _matTarget;

	pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixInverse(&matWorldInverse, nullptr,&matWorld);

	_matTarget = _matTarget*matWorldInverse;

	MOVEMENT nowMovement = m_moventList[_index][(int)m_nowFrame];
	_matrix	 matMovement = nowMovement.matScale*nowMovement.matRot*nowMovement.matTrans*nowMovement.matRevolution*matParent;
	_matTarget = _matTarget*matMovement*matWorld;*/

	return _matTarget;
}

MOVEMENT CAnimator::Get_Movement(_int _targetIndex, _int _targetFrame)
{
	//없는 오브젝트 찾으면 벡터 범위 넘어가서 터짐.
	//없는 프레임을 찾으면 그 프레임까지 자동 확장
	if (_targetFrame > m_maxFrame)
	{
		m_maxFrame = _targetFrame;
		Insert_Idle(-1);
	}

	return m_moventList[_targetIndex][_targetFrame];
}
