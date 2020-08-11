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
}

void CParticleMgr::Particle_Render()
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end(); ++iter)
	{
		(*iter)->Render_Buffer();
	}
}

void CParticleMgr::Particle_Create()
{
	Engine::_vec3 vOrigin = Engine::_vec3(0.f, 0.f, 0.f);
	Engine::BoundingBox tempBoundingBox;
	tempBoundingBox.vMax = Engine::_vec3(100.f, 100.f, 100.f);
	tempBoundingBox.vMin = Engine::_vec3(-100.f, -100.f, -100.f);
	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_ATK, tempBoundingBox, vOrigin);

	static_cast<Engine::CPart_Atk*>(tempParticle)->Set_Texture(L"../../Asset/snowflake.dds");
	//_tempParticle->
	m_arrParticle.emplace_back(tempParticle);
}


void Engine::CParticleMgr::Free(void)
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();)
	{
		Engine::Safe_Release((*iter));
		iter = m_arrParticle.erase(iter);
	}
	m_arrParticle.clear();

	Safe_Release(m_pGraphicDev);
}
