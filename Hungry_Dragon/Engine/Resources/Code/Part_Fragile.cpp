#include "Part_Fragile.h"

USING(Engine)

CPart_Fragile::CPart_Fragile(LPDIRECT3DDEVICE9 pGraphicDev)
	:CParticle(pGraphicDev)
{
	for (int i = 0; i < 10; ++i) {
		m_arrTex[i] = nullptr;
	}
}

CPart_Fragile::CPart_Fragile(const CPart_Fragile & rhs)
	:CParticle(rhs)
{
	m_iTexIndex = 0;
	m_bTexRight = true;
	for (int i = 0; i < 10; ++i) {
		m_arrTex[i] = rhs.m_arrTex[i];
		m_arrTex[i]->AddRef();
	}
}

CPart_Fragile::CPart_Fragile(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vOrigin, BoundingBox * boundingBox, int numParticle, float _fSize)
	:CParticle(pGraphicDev)
{
	m_BoundingBox = *boundingBox;
	m_fSize = _fSize;
	m_VbSize = 40;
	m_vOffset = 0;
	m_BatchSize = 10;

	for (int i = 0; i < numParticle; ++i)
	{
		Add_Particle();
	}
}

CPart_Fragile::~CPart_Fragile(void)
{
}

void CPart_Fragile::Set_BoundingBox(BoundingBox _boundingBox)
{
	m_BoundingBox = _boundingBox;
}

void CPart_Fragile::Set_Origin(_vec3 _origin)
{
	m_vOrigin = _origin;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end(); ++iter)
	{
		Reset_Particle(&(*iter));
	}
}

void CPart_Fragile::Set_TexArray() {
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture0.dds", &m_arrTex[0]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture1.dds", &m_arrTex[1]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture2.dds", &m_arrTex[2]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture3.dds", &m_arrTex[3]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture4.dds", &m_arrTex[4]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture5.dds", &m_arrTex[5]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture6.dds", &m_arrTex[6]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture7.dds", &m_arrTex[7]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture8.dds", &m_arrTex[8]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Texture9.dds", &m_arrTex[9]);
}

void CPart_Fragile::Set_TexArrayMFC() {
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture0.dds", &m_arrTex[0]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture1.dds", &m_arrTex[1]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture2.dds", &m_arrTex[2]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture3.dds", &m_arrTex[3]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture4.dds", &m_arrTex[4]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture5.dds", &m_arrTex[5]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture6.dds", &m_arrTex[6]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture7.dds", &m_arrTex[7]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture8.dds", &m_arrTex[8]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture9.dds", &m_arrTex[9]);
}

void CPart_Fragile::Reset_Particle(ATTRIBUTE * _attribute)
{
	_attribute->bAlive = true;
	_attribute->vPosition = m_vOrigin;

	_vec3 randPos = _vec3(rand()%10-5,rand()%10-5,rand()%10-5);
	_attribute->vPosition += randPos;
	D3DXVec3Normalize(&_attribute->vVelocity, &(_attribute->vPosition-m_vOrigin));

	//삼각형 파티클 색깔 바꿔주는 부분 여기서 안함.
}

_int CPart_Fragile::Update_Component(const _float & _fTimeDelta)
{
	if (Is_Empty())
	{
		return -1;
	}

	if(m_bTexRight)
		m_Tex=m_arrTex[m_iTexIndex++];
	else
		m_Tex = m_arrTex[m_iTexIndex--];

	if (m_iTexIndex == 10) {
		m_iTexIndex = 8;
		m_bTexRight = false;
	}
	else if(m_iTexIndex==-1){
		m_iTexIndex = 1;
		m_bTexRight = true;
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
			iter->vPosition += iter->vVelocity*_fTimeDelta*100.f;
			++iter;
		}
	}
	return 0;
}

CPart_Fragile * CPart_Fragile::Create(LPDIRECT3DDEVICE9 pGraphicDev, int numParticle, float _fSize)
{
	BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = { 0.f,0.f,0.f };
	tempBoundingBox.vMin = { 0.f,0.f,0.f };
	CPart_Fragile*	pInstance = new CPart_Fragile(pGraphicDev, _vec3(0.f, 0.f, 0.f), &tempBoundingBox, numParticle, _fSize);
	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);
	return pInstance;
}

CResources * CPart_Fragile::Clone(_vec3 _origin, BoundingBox _boundingBox)
{
	CPart_Fragile* pClonedParticle = new CPart_Fragile(*this);
	pClonedParticle->Set_BoundingBox(_boundingBox);
	pClonedParticle->Set_Origin(_origin);
	return pClonedParticle;
}

void CPart_Fragile::Free(void)
{
	for(int i=0;i<10;++i)
		Safe_Release(m_arrTex[i]);
	Safe_Release(m_Vb);
	CResources::Free();
}
