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
	D3DXMatrixIdentity(&idleMovement.matScale);
	D3DXMatrixIdentity(&idleMovement.matRot);
	D3DXMatrixIdentity(&idleMovement.matTrans);
	D3DXMatrixIdentity(&idleMovement.matRevolution);
	
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

	D3DXMatrixScaling(&m_moventList[_targetIndex][_targetFrame].matScale, _vecScale.x,_vecScale.y,_vecScale.z);
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

	D3DXMatrixRotationYawPitchRoll(&m_moventList[_targetIndex][_targetFrame].matRot, _vecRot.y, _vecRot.x, _vecRot.z);
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

	D3DXMatrixTranslation(&m_moventList[_targetIndex][_targetFrame].matTrans, _vecTrans.x, _vecTrans.y, _vecTrans.z);
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

	D3DXMatrixTranslation(&matParent, _vec3Parent.x, _vec3Parent.y, _vec3Parent.z);
	D3DXMatrixRotationYawPitchRoll(&matRevolution, _vecRev.y, _vecRev.x, _vecRev.z);

	m_moventList[_targetIndex][_targetFrame].matRevolution = matParent*matRevolution;
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
				D3DXMatrixIdentity(&idleMove.matScale);
				D3DXMatrixIdentity(&idleMove.matRot);
				D3DXMatrixIdentity(&idleMove.matTrans);
				D3DXMatrixIdentity(&idleMove.matRevolution);

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

_int CAnimator::Get_TotalMaxFrame()
{
	return m_maxFrame;
}

_matrix CAnimator::Get_MoveResult(LPDIRECT3DDEVICE9 pGraphicDev, _matrix _matTarget, _int _index)
{
	_matrix  matWorld;
	_matrix  matWorldInverse;

	pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixInverse(&matWorldInverse, nullptr,&matWorld);

	_matTarget = _matTarget*matWorldInverse;

	MOVEMENT nowMovement = m_moventList[_index][(int)m_nowFrame];
	_matrix	 matMovement = nowMovement.matScale*nowMovement.matRot*nowMovement.matTrans*nowMovement.matRevolution;
	_matTarget = _matTarget*matMovement*matWorld;

	return _matTarget;
}
