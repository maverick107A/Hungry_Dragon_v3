#include "CollisionMgr.h"
#include "GameObject.h"
#include "Transform.h"

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

bool CCollisionMgr::Player_Monster(CGameObject * _pPlayer, CGameObject * _pMonster)
{
	_vec3 vPlayerPos, vMonsterPos, vDis;
	_pPlayer->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);
	_pMonster->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
	vDis = vPlayerPos - vMonsterPos;
	//if(powf(vDis.x,2)+ powf(vDis.y, 2)+ powf(vDis.z, 2) < 4 )

	return (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < 4);
}


void Engine::CCollisionMgr::Free(void)
{
}
