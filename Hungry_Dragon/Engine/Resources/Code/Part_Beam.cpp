#include "Part_Beam.h"

#include "Export_Function.h"
USING(Engine)

CPart_Beam::CPart_Beam(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CParticle(pGraphicDev)
{
}

CPart_Beam::CPart_Beam(const CPart_Beam & rhs)
	:CParticle(rhs)
{
	m_arrParticle = rhs.m_arrParticle;

	m_fDepth = rhs.m_fDepth;
	m_iRadius = rhs.m_iRadius;
}

CPart_Beam::CPart_Beam(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox * boundingBox, int numParticle, float _fSize)
	:CPart_Beam(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 40;
	m_vOffset = 0;
	m_BatchSize = 10;

	m_fDepth = 100.f;
	m_fRadius = 5.f;
	m_iRadius=14;

	for (int i = 0; i < numParticle; ++i) {
		Add_Particle();
	}
}

CPart_Beam::~CPart_Beam(void) {
}

_int CPart_Beam::Get_Radius()
{
	return m_iRadius;
}

void CPart_Beam::Set_BoundingBox(BoundingBox _boundingBox) {
	m_BoundingBox = _boundingBox;
}

void CPart_Beam::Set_Origin(_vec3 _origin) {
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter) {
		Reset_Particle(&(*iter));
	}
}

void CPart_Beam::Set_Player(CPlayerMain * _pPlayer) {
	m_pPlayer = _pPlayer;
}

void CPart_Beam::Set_Radius(_int _radius)
{
	if (_radius < 14)
	{
		m_iRadius = 14;
		return;
	}

	m_iRadius = _radius;
}

void CPart_Beam::Reset_Particle(ATTRIBUTE * _attribute) {
	_attribute->bAlive = true;

	if (m_pPlayer) {
		_vec3 BeamPos;
		memcpy(&BeamPos, &m_pPlayer->Get_Transform()->m_matWorld._31, sizeof(_vec3));

		_attribute->vPosition = BeamPos*2.f;
	}
	else {
		_attribute->vPosition = m_vOrigin;
	}
	float tempRadX;
	float tempRadY;
	//float tempZ;

	float tempRotX=1.f;
	float tempRotY=1.f;
	float tempRotZ=1.f;


	if (m_pPlayer) {
		_matrix matPlayer= m_pPlayer->Get_Transform()->Get_World();
		_attribute->vVelocity.x = matPlayer._31;
		_attribute->vVelocity.y = matPlayer._32;
		_attribute->vVelocity.z = matPlayer._33;

		float randSpeed= rand()*0.0000305185f * 2;
		_attribute->vVelocity *= randSpeed;


		float randShad = rand() % 101 * 0.01f;
		float randAlpha = rand() % 101 * 0.01f;
		_attribute->tColor = D3DXCOLOR(1.f, randShad, 0.f, randAlpha);
		// X컬러는 0.f ~ 1.f 사이 값임 DWORD가 아님
		/*if (rand() % 2 == 0)
			_attribute->tColor = D3DXCOLOR(255.f, 255.f, 0.f, 255.f);
		else
			_attribute->tColor = D3DXCOLOR(255.f, 0.f, 0.f, 255.f);*/
		tempRotZ = matPlayer._33;
		tempRotX = matPlayer._31;
		tempRotY = matPlayer._32;
		
	}
	else {
		_attribute->vVelocity = _vec3(0.f, 0.f, 1.f);
	}

	float tempInnerRadius=(m_iRadius*0.5f-2)*(m_iRadius*0.5f-2);
	float tempOuterRadius=m_iRadius*m_iRadius*0.25f;
	do {
		tempRadX = rand()*0.0000305185f * m_iRadius - m_iRadius*0.5f;
		tempRadY = rand()*0.0000305185f * m_iRadius - m_iRadius*0.5f;
		//tempZ = rand()*0.0000305185f * 3;
	} while (tempRadX*tempRadX + tempRadY*tempRadY <= tempInnerRadius || tempRadX*tempRadX + tempRadY*tempRadY > tempOuterRadius);

	_vec3 vOutput;
	if (m_pPlayer)
	{
		vOutput = m_pPlayer->Get_Up()*tempRadX + m_pPlayer->Get_Right()*tempRadY;
	}


	_attribute->vPosition.x += vOutput.x;
	_attribute->vPosition.y += vOutput.y;
	_attribute->vPosition.z += vOutput.z;

	

	_attribute->vAccel = _vec3(1.5f,1.5f,1.5f);
}

_int CPart_Beam::Update_Component(const _float & fTimeDelta) {
	if (Is_Empty()) {
		return -1;
	}

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end();) {
		if (m_BoundingBox.isPointInside(iter->vPosition) == false) {
  			Reset_Particle(&(*iter));
			++iter;
		}
		else {
			iter->vPosition += iter->vVelocity*fTimeDelta*50;
			iter->vVelocity.x *= iter->vAccel.x;
			iter->vVelocity.y *= iter->vAccel.y;
			iter->vVelocity.z *=iter->vAccel.z;
			++iter;
		}
	}

	return 0;
}

void CPart_Beam::Manual_Reset_Particle() {
	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end(); ++iter) {
		Reset_Particle(&(*iter));
	}
}

CPart_Beam * CPart_Beam::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize) {
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CPart_Beam*	pInstance = new CPart_Beam(pGraphicDev, _vec3(0.f, 0.f, 0.f), &tempBoundingBox, numParticle, _fSize);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CPart_Beam::Clone(_vec3 _origin, BoundingBox _boundingBox) {
	CPart_Beam* pClonedParticle = new CPart_Beam(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CPart_Beam::Free(void) {
	CParticle::Free();
}
