#include "Part_Wind.h"
#include "PlayerMain.h"

USING(Engine)

CPart_Wind::CPart_Wind(LPDIRECT3DDEVICE9 pGraphicDev)
	:CParticle(pGraphicDev)
{
}

CPart_Wind::CPart_Wind(const CPart_Wind & rhs)
	:CParticle(rhs)
{
}

CPart_Wind::CPart_Wind(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox * boundingBox, int numParticle, float _fSize)
	:CParticle(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 500;
	m_vOffset = 0;
	m_BatchSize = 100;
	m_fSpeed = 30.f;
	m_fOne = 150.f;
	m_fZero = 10.f;

	for (int i = 0; i < numParticle; ++i)
	{
		Add_Particle();
	}
}

CPart_Wind::~CPart_Wind(void)
{
}

void CPart_Wind::Set_BoundingBox(BoundingBox _boundingBox)
{
	m_BoundingBox = _boundingBox;
}

void CPart_Wind::Set_Origin(_vec3 _origin)
{
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter)
	{
		Reset_Particle(&(*iter));
	}
}

void CPart_Wind::Set_Player(CPlayerMain * _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPart_Wind::Reset_Particle(ATTRIBUTE * _attribute)
{
	_attribute->bAlive = true;

	_attribute->vPosition = m_vOrigin;
	if (m_pPlayer)
	{
		_attribute->vPosition += m_pPlayer->Get_Up()*(WINCY*0.5f - rand()*(WINCY) / RAND_MAX);
		_attribute->vPosition += m_pPlayer->Get_Right()*(WINCX*0.5f - rand()*(WINCX) / RAND_MAX);
		//_attribute->vPosition.x += WINCX*0.5f - rand()*(WINCX) / RAND_MAX;
		//_attribute->vPosition.y += WINCY*0.5f - rand()*(WINCY) / RAND_MAX;
		_attribute->vVelocity = (_attribute->vPosition - m_vOrigin)*m_fSpeed;

		_attribute->tColor = D3DXCOLOR(255.f, 255.f, 255.f, 255.f);
	}

}

_int CPart_Wind::Update_Component(const _float & _fTimeDelta)
{
	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end();++iter)
	{
		if (m_BoundingBox.isPointInside(iter->vPosition) == false)
		{
			Reset_Particle(&(*iter));
		}
		else
		{
			iter->vPosition += iter->vVelocity*_fTimeDelta;
		}
	}

	return 0;
}

CPart_Wind* CPart_Wind::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize)
{
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CPart_Wind*	pInstance = new CPart_Wind(pGraphicDev, _vec3(0.f, 0.f, 0.f), &tempBoundingBox, numParticle, _fSize);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CPart_Wind::Clone(_vec3 _origin, BoundingBox _boundingBox)
{
	CPart_Wind* pClonedParticle = new CPart_Wind(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CPart_Wind::Free(void)
{
	CParticle::Free();
}
