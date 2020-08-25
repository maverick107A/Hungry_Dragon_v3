#include "Part_Atk.h"

USING(Engine)

CPart_Atk::CPart_Atk(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CParticle(pGraphicDev)
{
}

CPart_Atk::CPart_Atk(const CPart_Atk & rhs)
	:CParticle(rhs)
{
	m_arrParticle = rhs.m_arrParticle;

	m_fWidth = 5.f;
	m_fHeight = 10.f;
	m_fZero = 30.f;
}

CPart_Atk::CPart_Atk(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize)
	:CParticle(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 40;
	m_vOffset = 0;
	m_BatchSize = 10;

	m_fZero = 30.f;

	m_fWidth = 100.f;
	m_fHeight = 1500.f;

	for (int i = 0; i < numParticle; ++i) {
		Add_Particle();
	}
}

CPart_Atk::~CPart_Atk(void) {
}

void CPart_Atk::Set_BoundingBox(BoundingBox _boundingBox) {
	m_BoundingBox = _boundingBox;
}

void CPart_Atk::Set_Origin(_vec3 _origin) {
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter) {
		Reset_Particle(&(*iter));
	}
}

void CPart_Atk::Reset_Particle(ATTRIBUTE* _attribute) {
	_attribute->bAlive = true;

	_attribute->vPosition = m_vOrigin;

	float ftempRand_r = sqrtf(-2.f*logf((float)(rand() + 1) / (RAND_MAX + 1)));
	float ftempRand_z = sqrtf(-2.f*logf((float)(rand() + 1) / (RAND_MAX + 1)));
	float ftempRand_t = 2.f*Pi*(float)rand() / RAND_MAX;

	_attribute->vVelocity.x = (ftempRand_r*cosf(ftempRand_t))*m_fWidth;
	_attribute->vVelocity.y = ((ftempRand_r*sinf(ftempRand_t))*m_fHeight+m_fSpeed);
	_attribute->vVelocity.z = (ftempRand_z*cosf(ftempRand_t))*m_fWidth;

	_attribute->tColor = D3DXCOLOR(255.f, 0.f, 0.f, 255.f);

	_attribute->fLifeTime = Engine::CTimerMgr::GetInstance()->Get_TimeDelta(L"Particle_Timer");
}

_int CPart_Atk::Update_Component(const _float & _fTimeDelta) {
	if (Is_Empty()) {
		return -1;
	}

	if (-1 == CParticle::Update_Component(_fTimeDelta)) {
		return -1;
	}

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end();) 
	{
		if (m_BoundingBox.isPointInside(iter->vPosition) == false)
		{
			//iter = m_arrParticle.erase(iter);
			Reset_Particle(&(*iter));
		}
		else 
		{
			iter->vPosition += iter->vVelocity*_fTimeDelta;
			iter->vVelocity.y -= GRAVITY;

			++iter;
		}
	}

	return 0;
}

CPart_Atk * CPart_Atk::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize) {
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CPart_Atk*	pInstance = new CPart_Atk(pGraphicDev, _vec3(0.f,0.f,0.f) ,&tempBoundingBox, numParticle,_fSize);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CPart_Atk::Clone(_vec3 _origin, BoundingBox _boundingBox) {
	CPart_Atk* pClonedParticle= new CPart_Atk(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CPart_Atk::Free(void) {
	CParticle::Free();
}
