#include "Part_Leaf.h"

USING(Engine)

CPart_Leaf::CPart_Leaf(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CParticle(pGraphicDev)
{
}

CPart_Leaf::CPart_Leaf(const CPart_Leaf & rhs)
	:CParticle(rhs)
{
	m_arrParticle = rhs.m_arrParticle;

	m_fWidth = 5.f;
	m_fHeight = 10.f;

	m_fZero = 80;
	m_fOne = 100;
	
}

CPart_Leaf
::CPart_Leaf(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vOrigin ,BoundingBox * boundingBox, int numParticle,float _fSize)
	:CParticle(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 40;
	m_vOffset = 0;
	m_BatchSize = 10;

	m_fWidth = 100.f;
	m_fHeight = 1500.f;

	for (int i = 0; i < numParticle; ++i) {
		Add_Particle();
	}
}

CPart_Leaf::~CPart_Leaf(void) {
}

void CPart_Leaf::Set_BoundingBox(BoundingBox _boundingBox) {
	m_BoundingBox = _boundingBox;
	
}

void CPart_Leaf::Set_Origin(_vec3 _origin) {
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter) {
		Reset_Particle(&(*iter));
	}
}

void CPart_Leaf::Reset_Particle(ATTRIBUTE* _attribute) {
	_attribute->bAlive = true;

	float _fRandY = (rand() % 100)*1.f;
	_attribute->vPosition = m_vOrigin + _vec3((rand() % 100 - 50)*0.5f *_fRandY*0.01f, -_fRandY, (rand() % 100 - 50)*0.5f * _fRandY*0.01f);

	_attribute->vVelocity.x = (rand()%100 - 50)*0.5f;
	_attribute->vVelocity.y = -0.1f;
	_attribute->vVelocity.z = (rand() % 100 - 50)*0.5f;

	float fRand = 0.8f - (rand() % 1)*0.05f;

	_attribute->tColor = D3DXCOLOR(0.f, fRand, 0.f, 1.f);

	_attribute->fLifeTime = Engine::CTimerMgr::GetInstance()->Get_TimeDelta(L"Particle_Timer");
}

_int CPart_Leaf::Update_Component(const _float & _fTimeDelta) {
	if (Is_Empty()) {
		return -1;
	}

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end();) 
	{
		if (m_BoundingBox.isPointInside(iter->vPosition) == false)
		{
			iter = m_arrParticle.erase(iter);
			//Reset_Particle(&(*iter));
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

CPart_Leaf * CPart_Leaf::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle,float _fSize) {
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CPart_Leaf*	pInstance = new CPart_Leaf(pGraphicDev, _vec3(0.f,0.f,0.f) ,&tempBoundingBox, numParticle,_fSize);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CPart_Leaf::Clone(_vec3 _origin, BoundingBox _boundingBox) {
	CPart_Leaf* pClonedParticle= new CPart_Leaf(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CPart_Leaf::Free(void) {
	CParticle::Free();
}
