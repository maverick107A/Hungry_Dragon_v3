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
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();)
	{
		int life = (*iter)->Update_Component(fTimeDelta);

		if (life == 0) {
			++iter;
		}
		else {
			Safe_Release(*iter);
			iter = m_arrParticle.erase(iter);
		}
	}

	m_vecTrans.clear();
}

void CParticleMgr::Particle_LateUpdate(const float & fTimeDelta)
{
	int tempParticleListSize = (int)m_arrParticle.size();
	m_vecTrans.clear();
	m_vecTrans.reserve(tempParticleListSize);

	for (int i = 0; i < tempParticleListSize; ++i)
	{
		m_vecTrans.emplace_back(Engine::_vec3(0.f,0.f,0.f));
	}
}

void CParticleMgr::Particle_Render()
{
	/*int index = 0;
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end(); ++iter,++index)
	{
		m_pParticleTrans->Set_Trans(&m_vecTrans[index]);
		m_pParticleTrans->Update_Component(0.1f);
		m_pParticleTrans->Set_Transform(m_pGraphicDev);
		(*iter)->Render_Buffer();
	}*/
}

CResources* CParticleMgr::Particle_Create(const _vec3 _pos)
{
	//Engine::Particle_Render();


	Engine::_vec3 vOrigin = _pos;
	Engine::BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = vOrigin+ Engine::_vec3(500.f, 500.f, 500.f);
	tempBoundingBox.vMin = vOrigin+Engine::_vec3(-500.f, -5.f, -500.f);
	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_ATK, tempBoundingBox, vOrigin);

	static_cast<Engine::CPart_Atk*>(tempParticle)->Set_Texture(L"../../Asset/snowflake.dds");

	m_arrParticle.emplace_back(tempParticle);
	return tempParticle;
}

bool CParticleMgr::Set_ParticleTrans(CResources* _particle, _vec3 _pos)
{

	int index;
	list<CResources*>::iterator iter_part = m_arrParticle.begin();
	for (index = 0; index < (int)m_arrParticle.size(); ++index, ++iter_part)
	{
		if (_particle == (*iter_part))
		{
			break;
		}
	}

	if (iter_part != m_arrParticle.end())
	{
		m_vecTrans[index] = _pos;
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
