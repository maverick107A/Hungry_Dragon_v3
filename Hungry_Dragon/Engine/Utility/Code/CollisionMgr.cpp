#include "CollisionMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonsterMain.h"
#include "PlayerMain.h"

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

void CCollisionMgr::Player_Monster(list<CGameObject*> * _pPlayer, list<CGameObject*> * _pMonster, const float& fTimeDelta)
{
	for (auto& pPlayer : *_pPlayer)
	{
		for (auto& pMonster : *_pMonster)
		{
			_vec3 vPlayerPos, vMonsterPos, vDis;
			pPlayer->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);
			pMonster->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
			vDis = vPlayerPos - vMonsterPos;
			if (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < 4)
			{
				static_cast<CMonsterMain*>(pMonster)->Kill_Monster(fTimeDelta);
			}
		}
	}
}

bool CCollisionMgr::Player_MonsterCol(CGameObject * _caller, CGameObject * _callee)
{
	_vec3 vPlayerPos, vMonsterPos, vDis;
	_caller->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);
	_callee->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
	vDis = vPlayerPos - vMonsterPos;

	return ((powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2)) < 50);
}


void Engine::CCollisionMgr::Free(void)
{
}
