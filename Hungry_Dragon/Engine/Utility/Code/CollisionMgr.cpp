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

bool CCollisionMgr::PBullet_Monster(CGameObject * _pPBullet, CGameObject * _pMonster)
{
	_pPBullet->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC);
	_pMonster->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC);
	return false;
}


void Engine::CCollisionMgr::Free(void)
{
}
