#include "Particle.h"

USING(Engine)

CParticle::CParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CResources(pGraphicDev)
{
	m_Vb = 0;
	m_Tex = 0;
	m_fSpeed = 17.f;
}

CParticle::CParticle(const CParticle & rhs)
	:CResources(rhs)
	,m_vOrigin(rhs.m_vOrigin)
	,m_fEmitRate(rhs.m_fEmitRate)
	,m_fSize(rhs.m_fSize)
	,m_arrParticle(rhs.m_arrParticle)
	,m_iMaxParticle(rhs.m_iMaxParticle)
	,m_VbSize(rhs.m_VbSize)
	,m_vOffset(rhs.m_vOffset)
	,m_BatchSize(rhs.m_BatchSize)
	,m_fSpeed(rhs.m_fSpeed)
{
	m_BoundingBox = rhs.m_BoundingBox;

	m_Tex = rhs.m_Tex;
	if(m_Tex!=nullptr)
		m_Tex->AddRef();

	m_Vb = rhs.m_Vb;
	if(m_Vb!=nullptr)
		m_Vb->AddRef();
}

CParticle::~CParticle(void) {
}

HRESULT CParticle::Ready_Buffer(void) {
	m_pGraphicDev->CreateVertexBuffer(m_VbSize * sizeof(PARTICLE), D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, FVF_PART, D3DPOOL_DEFAULT, &m_Vb, 0);

	return S_OK;
}

void CParticle::Render_Buffer(void) {
	Render_Begin();
	m_pGraphicDev->SetTexture(0, m_Tex);
	m_pGraphicDev->SetFVF(FVF_PART);
	m_pGraphicDev->SetStreamSource(0, m_Vb, 0, sizeof(PARTICLE));

	if (m_vOffset >= m_VbSize) {
		m_vOffset = 0;
	}

	PARTICLE* pParticle=0;
	m_Vb->Lock(m_vOffset * sizeof(PARTICLE), m_BatchSize * sizeof(PARTICLE), (void**)&pParticle, m_vOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD particleInBatchNum = 0;

	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();;
	for (; iter != m_arrParticle.end();++iter) {
		if (iter->bAlive) {
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

void CParticle::Render_Begin(void) {
	float fZero = 0.f;
	float fOne = 1.f;

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, FloatToDword(m_fSize));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDword(fZero));

	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, FloatToDword(fZero));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, FloatToDword(fZero));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, FloatToDword(fOne));

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CParticle::Render_End(void) {
	m_pGraphicDev->SetTexture(0, 0);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
}

//파티클을 재활용하기 위해 개개의 파티클이 가진 속성을 원래대로 리셋해주는 함수
void CParticle::Reset_Buffer(void) {
	for (auto& iter : m_arrParticle) {
		Reset_Particle(&(iter));
	}
}

void CParticle::Add_Particle() {
	ATTRIBUTE attribute;
	Reset_Particle(&attribute);
	m_arrParticle.emplace_back(attribute);
}

bool CParticle::Is_Empty(void) {
	return m_arrParticle.empty();
}

bool CParticle::Is_Dead(void) {
	for (auto iter : m_arrParticle) {
		if (iter.bAlive) {
			return false;
		}
	}

	return true;
}

void CParticle::Set_Texture(_tchar * texFileName) {
	IDirect3DTexture9*		temp_Tex;
	if (S_OK == D3DXCreateTextureFromFile(m_pGraphicDev, texFileName, &temp_Tex)) {
		Safe_Release(m_Tex);
		m_Tex=temp_Tex;
	}
		
}

void CParticle::Set_Size(_float _fSize) {
	if (_fSize>0) {
		m_fSize = _fSize;
	}
}

void CParticle::Free(void) {
	Safe_Release(m_Tex);
	Safe_Release(m_Vb);
	CResources::Free();
}

void CParticle::Romove_DeadParticle(void) 
{
	list<ATTRIBUTE>::iterator iter = m_arrParticle.begin();

	for (; iter != m_arrParticle.end();) 
	{
		if ((*iter).bAlive) 
		{
			++iter;
		}
		else 
		{
			iter = m_arrParticle.erase(iter);
		}
	}
}

DWORD CParticle::FloatToDword(float& f) {
	return *((DWORD*)&f);
}

float CParticle::Get_RandomFloat(float lowBound, float highBound) {
	if (lowBound >= highBound) // bad input
		return lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;

	// return float in [lowBound, highBound] interval. 
	return (f * (highBound - lowBound)) + lowBound;
}

void CParticle::Get_RandomVector(_vec3* _out, _vec3* _min, _vec3* _max) {
	_out->x = Get_RandomFloat(_min->x, _max->x);
	_out->y = Get_RandomFloat(_min->y, _max->y);
	_out->z = Get_RandomFloat(_min->z, _max->z);
}