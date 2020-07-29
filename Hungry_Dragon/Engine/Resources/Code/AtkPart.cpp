#include "AtkPart.h"

USING(Engine)

CAtkPart::CAtkPart(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CParticle(pGraphicDev)
{
}

CAtkPart::CAtkPart(const CAtkPart & rhs)
	:CParticle(rhs)
{
	m_arrParticle = rhs.m_arrParticle;

	m_fWidth = 5.f;
	m_fHeight = 10.f;
	
}

CAtkPart::CAtkPart(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize)
	:CParticle(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 100;
	m_vOffset = 0;
	m_BatchSize = 25;

	m_fWidth = 5.f;
	m_fHeight = 10.f;

	for (int i = 0; i < numParticle; ++i) {
		Add_Particle();
	}
}

CAtkPart::~CAtkPart(void) {
}

void CAtkPart::Set_BoundingBox(BoundingBox _boundingBox) {
	m_BoundingBox = _boundingBox;
}

void CAtkPart::Set_Origin(_vec3 _origin) {
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter) {
		Reset_Particle(&(*iter));
	}
}

void CAtkPart::Reset_Particle(ATTRIBUTE* _attribute) {
	_attribute->bAlive = true;

	_attribute->vPosition = m_vOrigin;

	float ftempRand_r = sqrtf(-2.f*logf((float)(rand() + 1) / (RAND_MAX + 1)));
	float ftempRand_z = sqrtf(-2.f*logf((float)(rand() + 1) / (RAND_MAX + 1)));
	float ftempRand_t = 2.f*Pi*(float)rand() / RAND_MAX;

	_attribute->vVelocity.x = (ftempRand_r*cosf(ftempRand_t))*m_fWidth;
	_attribute->vVelocity.y = ((ftempRand_r*sinf(ftempRand_t))*m_fHeight-m_fSpeed);
	_attribute->vVelocity.z = (ftempRand_z*sinf(ftempRand_t))*m_fWidth;

	_attribute->tColor = D3DXCOLOR(255.f, 0.f, 0.f, 255.f-(rand()*50/RAND_MAX));

	_attribute->fLifeTime = Engine::CTimerMgr::GetInstance()->Get_TimeDelta(L"Particle_Timer");
}

_int CAtkPart::Update_Component(const _float & _fTimeDelta) {
	if (Is_Empty()) {
		return -1;
	}

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end();) {
		if (m_BoundingBox.isPointInside(iter->vPosition) == false/*||iter->vPosition.y>m_vOrigin.y*/) {
			//Reset_Particle(&(*iter));
			//(*iter).bAlive = false;
			iter = m_arrParticle.erase(iter);
		}
		else {
			iter->vPosition += iter->vVelocity*_fTimeDelta;
			iter->vVelocity.y -= GRAVITY;

			++iter;
		}
	}

	return 0;
}

CAtkPart * CAtkPart::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize) {
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CAtkPart*	pInstance = new CAtkPart(pGraphicDev, _vec3(0.f,0.f,0.f) ,&tempBoundingBox, numParticle,_fSize);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CAtkPart::Clone(_vec3 _origin, BoundingBox _boundingBox) {
	CAtkPart* pClonedParticle= new CAtkPart(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CAtkPart::Free(void) {
	CParticle::Free();
}
