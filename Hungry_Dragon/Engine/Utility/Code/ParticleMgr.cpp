#include "ParticleMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Export_Function.h"
USING(Engine)

IMPLEMENT_SINGLETON(Engine::CParticleMgr)

Engine::CParticleMgr::CParticleMgr(void) 
{

}

Engine::CParticleMgr::~CParticleMgr(void)
{
	Free();
}

void CParticleMgr::Ready_ParticleMgr(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_pGraphicDev = _pGraphicDev;
	m_pParticleTrans = CTransform::Create();
}

void CParticleMgr::Particle_Update(const float & fTimeDelta)
{
	list<_vec3>::iterator iter_pos = m_arrTrans.begin();
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();)
	{
		int life = (*iter)->Update_Component(fTimeDelta);

		if (life == 0) {
			++iter;
			++iter_pos;
		}
		else {
			Safe_Release(*iter);
			iter = m_arrParticle.erase(iter);
			iter_pos = m_arrTrans.erase(iter_pos);
		}
	}
}

void CParticleMgr::Particle_LateUpdate(const float & fTimeDelta)
{
	int tempParticleListSize = (int)m_arrParticle.size();
}

void CParticleMgr::Particle_Render()
{

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0);
	list<_vec3>::iterator iter_pos = m_arrTrans.begin();
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end(); ++iter,++iter_pos)
	{
		
		m_pParticleTrans->Set_Trans(&(*iter_pos));
		m_pParticleTrans->Update_Component(0.1f);
		m_pParticleTrans->Set_Transform(m_pGraphicDev);
		(*iter)->Render_Buffer();
	}
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

CResources* CParticleMgr::Particle_Create(Engine::PARTICLEID _eID, const _vec3 _pos)
{
	if (m_arrParticle.size() > m_iParticleLimit)
	{
		Safe_Release(m_arrParticle.front());
		m_arrParticle.front() = nullptr;
		m_arrParticle.pop_front();
		m_arrTrans.pop_front();
	}

	Engine::_vec3 vOrigin = _pos;
	Engine::BoundingBox tempBoundingBox;

	switch (_eID)
	{
	case Engine::PART_ATK:
		
		tempBoundingBox.vMax = vOrigin + Engine::_vec3(250.f, 250.f, 250.f);
		tempBoundingBox.vMin = vOrigin + Engine::_vec3(-250.f, -25.f, -250.f);
		break;
	case Engine::PART_WIND:
		tempBoundingBox.vMax = vOrigin + Engine::_vec3(250.f, 250.f, 250.f);
		tempBoundingBox.vMin = vOrigin + Engine::_vec3(-250.f, -25.f, -250.f);
		break;
	case Engine::PART_FRAGILE:
		tempBoundingBox.vMax = vOrigin + Engine::_vec3(250.f, 250.f, 250.f);
		tempBoundingBox.vMin = vOrigin + Engine::_vec3(-250.f, -25.f, -250.f);
		break;
	case Engine::PART_LEAF:
		tempBoundingBox.vMax = vOrigin + Engine::_vec3(250.f, 25.f, 250.f);
		tempBoundingBox.vMin = vOrigin + Engine::_vec3(-250.f, -125.f, -250.f);
		break;
	case Engine::PART_BEAM:
		tempBoundingBox.vMax = vOrigin + Engine::_vec3(1000.f, 1000.f, 1000.f);
		tempBoundingBox.vMin = vOrigin + Engine::_vec3(-1000.f, -1000.f, -1000.f);
		break;
	case Engine::PART_END:
		break;
	}
	
	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, _eID, tempBoundingBox, vOrigin);
	


	m_arrParticle.emplace_back(tempParticle);
	m_arrTrans.emplace_back(_vec3(0.f, 0.f, 0.f));
	return tempParticle;
}

bool CParticleMgr::Set_ParticleTrans(CResources* _particle, _vec3 _pos)
{
	// 파티클 위치 정보 갱신하는곳 
	// 개적화되어있음 고쳐
	int index;
	list<CResources*>::iterator iter_part = m_arrParticle.begin();
	list<_vec3>::iterator iter_pos = m_arrTrans.begin();
	for (index = 0; index < (int)m_arrParticle.size(); ++index, ++iter_part,++iter_pos)
	{
		if (_particle == (*iter_part))
		{
			break;
		}
	}

	if (iter_part != m_arrParticle.end())
	{
		(*iter_pos) = _pos;
		return true;
	}

	return false;
}


void Engine::CParticleMgr::Free(void)
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();)
	{
		Engine::Safe_Release((*iter));
		iter = m_arrParticle.erase(iter);
	}
	Engine::Safe_Release(m_pParticleTrans);
	m_arrParticle.clear();
}
