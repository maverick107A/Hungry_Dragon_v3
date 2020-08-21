#include "Animation_Controller.h"

#include "Export_Function.h"

USING(Engine)

CAnimation_Controller::CAnimation_Controller(void)
{
}

CAnimation_Controller::CAnimation_Controller(const CAnimation_Controller& rhs)
{
	for (size_t i = 0; i < rhs.m_arrAnimatior.size(); ++i) {
		CAnimator* tempAnimator=rhs.m_arrAnimatior[i];
		m_arrAnimatior.emplace_back(static_cast<CAnimator*>(tempAnimator->Clone()));
	}

	m_iAnimatorCnt = rhs.m_iAnimatorCnt;
	m_fNowFrame = rhs.m_fNowFrame;
	m_iMaxFrame = rhs.m_iMaxFrame;
	m_fFrameSpeed = rhs.m_fFrameSpeed;
}

CAnimation_Controller::~CAnimation_Controller(void)
{
}

MOVEMENT CAnimation_Controller::Get_Movement(_int _animatorIndex, _int _partIndex)
{
	if (_animatorIndex >= m_iAnimatorCnt) {
		return MOVEMENT();
	}

	if (_partIndex >= m_arrAnimatior[_animatorIndex]->Get_PartsCnt()) {
		return MOVEMENT();
	}

	return m_arrAnimatior[_animatorIndex]->Get_Movement(_partIndex);
}

void CAnimation_Controller::Set_FrameSpeed(_float _fSpeed)
{
	m_fFrameSpeed = _fSpeed;
}

_int CAnimation_Controller::Update_Component(const _float & fTimeDelta)
{
	m_fNowFrame += fTimeDelta*m_fFrameSpeed;
	while (m_fNowFrame >= (_float)m_iMaxFrame + 1) {
		m_fNowFrame -= (_float)m_iMaxFrame + 1.f;
	}

	return 0;
}

void CAnimation_Controller::Add_Animator(_int _clonedAnimationPos)
{
}

void CAnimation_Controller::Insert_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale)
{
}

void CAnimation_Controller::Add_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale)
{
}

void CAnimation_Controller::Insert_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate)
{
}

void CAnimation_Controller::Add_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate)
{
}

void CAnimation_Controller::Insert_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans)
{
}

void CAnimation_Controller::Add_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans)
{
}

void CAnimation_Controller::Insert_Revolute(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 vecParent, _vec3 _vecRevolution)
{
}

void CAnimation_Controller::Insert_Idle(_int animatorIndex, _int _partIndex, _int _frameIndex)
{
}

CAnimation_Controller * CAnimation_Controller::Create(void)
{
	return nullptr;
}

CComponent * CAnimation_Controller::Clone(void)
{
	return nullptr;
}

void CAnimation_Controller::Free(void)
{
	for (vector<CAnimator*>::iterator iter_Ani = m_arrAnimatior.begin(); iter_Ani != m_arrAnimatior.end(); ++iter_Ani) {
		Safe_Release((*iter_Ani));
	}
	m_arrAnimatior.clear();
}
