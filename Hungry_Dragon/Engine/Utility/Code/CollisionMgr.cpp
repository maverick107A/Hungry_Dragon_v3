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
		//플레이어는 한명이니 한번만
		CPlayerMain* Player = static_cast<CPlayerMain*>(pPlayer);
		_vec3 vPlayerPos;
		float fTemp;
		float ColSize = Player->Get_ColSize();
		pPlayer->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);
		if (Player->Get_Breath())
		{
			//브레스 방향 구하기
			_vec3 vDir;
			memcpy(&vDir, &pPlayer->Get_Transform()->Get_World().m[2][0], sizeof(_vec3));
			for (auto& pMonster : *_pMonster)
			{
				_vec3 vMonsterPos, vDis;
				pMonster->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);

				_vec3 vTemp = vMonsterPos - vPlayerPos;

				fTemp = D3DXVec3Dot(&vDir, &vTemp)/D3DXVec3Dot(&vDir, &vDir);

				_vec3 vMola = vPlayerPos + vDir*fTemp - vMonsterPos;

				if(D3DXVec3Dot(&vMola,&vMola) < ColSize)
					static_cast<CMonsterMain*>(pMonster)->Kill_Monster(fTimeDelta);
			}
		}
		else
		{
			for (auto& pMonster : *_pMonster)
			{
				_vec3 vMonsterPos, vDis;
				pMonster->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
				vDis = vPlayerPos - vMonsterPos;
				if (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < ColSize)
				{
					static_cast<CMonsterMain*>(pMonster)->Kill_Monster(fTimeDelta);
				}
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

	return ((powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2)) < 400);
}


void Engine::CCollisionMgr::Free(void)
{
}
