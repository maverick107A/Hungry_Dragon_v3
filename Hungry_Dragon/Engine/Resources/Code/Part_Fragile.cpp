#include "Part_Fragile.h"

USING(Engine)

CPart_Fragile::CPart_Fragile(LPDIRECT3DDEVICE9 pGraphicDev)
	:CParticle(pGraphicDev)
{
	for (int i = 0; i < DIR_END; ++i) {
		for (int j = 0; j < 10; ++j) {
			m_arrTex[i][j] = nullptr;
		}
	}
}

CPart_Fragile::CPart_Fragile(const CPart_Fragile & rhs)
	:CParticle(rhs)
{
	for (int i = 0; i < DIR_END; ++i) {
		for (int j = 0; j < 10; ++j) {
			m_arrTex[i][j] = rhs.m_arrTex[i][j];
			m_arrTex[i][j]->AddRef();
		}
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
	for (int _eDir = 0; _eDir < DIR_END; ++_eDir) {
		switch (_eDir)
		{
		case Engine::DIR_N:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNS_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][i]);
			}
			break;
		case Engine::DIR_S:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNS_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][9 - i]);
			}
			break;
		case Engine::DIR_E:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleEW_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][i]);
			}
			break;
		case Engine::DIR_W:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleEW_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][9 - i]);
			}
			break;
		case Engine::DIR_NE:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNE_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][i]);
			}
			break;
		case Engine::DIR_SW:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNE_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][9 - i]);
			}
			break;
		case Engine::DIR_NW:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNW_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][i]);
			}
			break;
		case Engine::DIR_SE:
			for (int i = 0; i < 10; ++i)
			{
				TCHAR str[128] = L"";
				wsprintf(str, L"../../Asset/Particle/Tri/TriangleNW_%d.dds", i);
				D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_arrTex[_eDir][9 - i]);
			}
			break;
		}
	}
}

void CPart_Fragile::Set_TexArrayMFC() {
	/*D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture0.dds", &m_arrTex[0]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture1.dds", &m_arrTex[1]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture2.dds", &m_arrTex[2]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture3.dds", &m_arrTex[3]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture4.dds", &m_arrTex[4]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture5.dds", &m_arrTex[5]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture6.dds", &m_arrTex[6]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture7.dds", &m_arrTex[7]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture8.dds", &m_arrTex[8]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Asset/Texture9.dds", &m_arrTex[9]);*/
}

void CPart_Fragile::Reset_Particle(ATTRIBUTE * _attribute)
{
	_attribute->bAlive = true;
	_attribute->vPosition = m_vOrigin;
	_attribute->bFrameUp = true;
	_attribute->iShape = rand() % 8;
	_attribute->iFrameIndex = rand() % 10;
	_vec3 randPos = _vec3((_float)(rand()%10-5), (_float)(rand()%10-5), (_float)(rand()%10-5));
	_attribute->vPosition += randPos;
	_attribute->tColor=D3DXCOLOR((float)(rand()%255)/255.f, (float)(rand()%255) / 255.f, (float)(rand()%255) / 255.f, (float)(rand()%255) / 255.f);
	D3DXVec3Normalize(&_attribute->vVelocity, &(_attribute->vPosition-m_vOrigin));
}

_int CPart_Fragile::Update_Component(const _float & _fTimeDelta)
{
	if (Is_Empty())
	{
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
			iter = m_arrParticle.erase(iter);
			//Reset_Particle(&(*iter));
		}
		else
		{

			if(iter->bFrameUp)
				iter->iFrameIndex++;
			else
				iter->iFrameIndex--;

			if (iter->iFrameIndex >= 10) {
				iter->iFrameIndex = 8;
				iter->bFrameUp = false;
			}
			else if(iter->iFrameIndex <=-1){
				iter->iFrameIndex = 1;
				iter->bFrameUp = true;
			}

			iter->vPosition += iter->vVelocity*_fTimeDelta*100.f;
			++iter;
		}
	}
	return 0;
}

void CPart_Fragile::Render_Buffer(void)
{
	Render_Begin();

	m_pGraphicDev->SetFVF(FVF_PART);
	m_pGraphicDev->SetStreamSource(0, m_Vb, 0, sizeof(PARTICLE));

	if (m_vOffset >= m_VbSize) {
		m_vOffset = 0;
	}

	PARTICLE* pParticle = 0;
	m_Vb->Lock(m_vOffset * sizeof(PARTICLE), m_BatchSize * sizeof(PARTICLE), (void**)&pParticle, m_vOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD particleInBatchNum = 0;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();
	for (; iter != m_arrParticle.end(); ++iter) {
		if (iter->bAlive) {
			m_Tex = m_arrTex[iter->iShape][iter->iFrameIndex];		//파티클마다 다른 텍스처를 주기 위함.
			m_pGraphicDev->SetTexture(0, m_Tex);
			pParticle->vPosition = iter->vPosition;
			pParticle->tColor = (D3DCOLOR)iter->tColor;
			++pParticle;

			++particleInBatchNum;

			if (particleInBatchNum == m_BatchSize) {
				m_Vb->Unlock();

				m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, m_vOffset, m_BatchSize);

				m_vOffset += m_BatchSize;

				if (m_vOffset >= m_VbSize) {
					m_vOffset = 0;
				}

				m_Vb->Lock(m_vOffset * sizeof(PARTICLE), m_BatchSize * sizeof(PARTICLE), (void**)&pParticle, m_vOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				particleInBatchNum = 0;
			}


		}
	}

	m_Vb->Unlock();

	if (particleInBatchNum) {
		m_pGraphicDev->DrawPrimitive(
			D3DPT_POINTLIST,
			m_vOffset,
			particleInBatchNum);
	}

	m_vOffset += m_BatchSize;

	Render_End();
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
	for (int i = 0; i < DIR_END; ++i) {
		for (int j = 0; j < 10; ++j)
			Safe_Release(m_arrTex[i][j]);
	}

	Safe_Release(m_Vb);
	CResources::Free();
}
