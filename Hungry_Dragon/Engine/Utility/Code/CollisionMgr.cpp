#include "CollisionMgr.h"
#include "GameObject.h"

USING(Engine)

IMPLEMENT_SINGLETON(Engine::CCollisionMgr)

Engine::CCollisionMgr::CCollisionMgr(void) 
{

}

Engine::CCollisionMgr::~CCollisionMgr(void)
{
	Free();
}


bool Engine::CCollisionMgr::Find_First(CGameObject * _caller, CGameObject * _callee)
{
	return true;
}


void Engine::CCollisionMgr::Free(void)
{
}
