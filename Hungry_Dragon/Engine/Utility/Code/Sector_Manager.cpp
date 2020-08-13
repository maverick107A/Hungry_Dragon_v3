#include "Sector_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSector_Manager)

Engine::CSector_Manager::CSector_Manager(void)
{

}

Engine::CSector_Manager::~CSector_Manager(void)
{
	Free();
}


void Engine::CSector_Manager::Free(void)
{
	
}

