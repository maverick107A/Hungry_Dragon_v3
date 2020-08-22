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

void CAnimation_Controller::Set_PartsCnt(_int _partsCnt)
{
	m_iPartsCnt = _partsCnt;
}

void CAnimation_Controller::Set_SpecificFrame(_int _animatorIndex, _int _partsIndex)
{
	if (_animatorIndex >= m_iAnimatorCnt)
		return;

	m_arrAnimatior[_animatorIndex]->Set_SpecificFrame(_partsIndex);
}

_int CAnimation_Controller::Update_Component(const _float & fTimeDelta)
{
	m_fNowFrame = fTimeDelta*m_fFrameSpeed;

	for (int i = 0; i < m_iAnimatorCnt; ++i)
	{
		m_arrAnimatior[i]->Update_Frame(m_fNowFrame);
	}

	return 0;
}

void CAnimation_Controller::Add_Animator(_int _clonedAnimationPos)
{
	CAnimator* tempAnimator;
	if (_clonedAnimationPos >= m_iAnimatorCnt||_clonedAnimationPos<0)
	{
		tempAnimator = CAnimator::Create();
		tempAnimator->Set_PartsSize(m_iPartsCnt);
	}
	else
	{
		tempAnimator = static_cast<CAnimator*>(m_arrAnimatior[_clonedAnimationPos]->Clone());
	}

	m_arrAnimatior.emplace_back(tempAnimator);
	++m_iAnimatorCnt;
}

void CAnimation_Controller::Insert_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Insert_Scale(_partIndex, _frameIndex, _vecScale);
}

void CAnimation_Controller::Add_Scale(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecScale)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Add_Scale(_partIndex, _frameIndex, _vecScale);
}

void CAnimation_Controller::Insert_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Insert_Rotate(_partIndex, _frameIndex, _vecRotate);
}

void CAnimation_Controller::Add_Rotate(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecRotate)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Add_Rotate(_partIndex, _frameIndex, _vecRotate);
}

void CAnimation_Controller::Insert_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Insert_Trans(_partIndex, _frameIndex, _vecTrans);
}

void CAnimation_Controller::Add_Trans(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecTrans)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Add_Trans(_partIndex, _frameIndex, _vecTrans);
}

void CAnimation_Controller::Insert_Revolute(_int _animatorIndex, _int _partIndex, _int _frameIndex, _vec3 _vecParent, _vec3 _vecRevolution)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Insert_Revolute(_partIndex, _frameIndex,_vecParent ,_vecRevolution);
}

void CAnimation_Controller::Insert_Idle(_int _animatorIndex, _int _partIndex, _int _frameIndex)
{
	if (_animatorIndex >= m_iAnimatorCnt || _animatorIndex<0)
	{
		return;
	}

	//¾ø´Â ÆÄÃ÷ Ã£À¸¸é Á¿µÊ.
	if (m_iMaxFrame < _frameIndex)
		m_iMaxFrame = _frameIndex;

	m_arrAnimatior[_animatorIndex]->Insert_Idle(_partIndex, _frameIndex);
}

CAnimation_Controller * CAnimation_Controller::Create(_int _partsCnt)
{
	CAnimation_Controller* tempAnimation_Controller;
	tempAnimation_Controller = new CAnimation_Controller();
	tempAnimation_Controller->Set_PartsCnt(_partsCnt);
	return tempAnimation_Controller;
}

CComponent * CAnimation_Controller::Clone(void)
{
	return new CAnimation_Controller(*this);
}

void CAnimation_Controller::Free(void)
{
	for (vector<CAnimator*>::iterator iter_Ani = m_arrAnimatior.begin(); iter_Ani != m_arrAnimatior.end(); ++iter_Ani) {
		Safe_Release((*iter_Ani));
	}
	m_arrAnimatior.clear();
}
