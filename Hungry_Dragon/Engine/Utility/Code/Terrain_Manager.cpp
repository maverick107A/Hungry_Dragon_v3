#include "Terrain_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTerrain_Manager)

Engine::CTerrain_Manager::CTerrain_Manager(void)
{

}

Engine::CTerrain_Manager::~CTerrain_Manager(void)
{
	Free();
}


void Engine::CTerrain_Manager::Free(void)
{
	
}

