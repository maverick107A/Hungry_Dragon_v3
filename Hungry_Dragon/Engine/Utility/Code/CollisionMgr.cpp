#include "CollisionMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonsterMain.h"
#include "PlayerMain.h"
#include "Export_Function.h"

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
		_vec3 vTemp;
		float fTemp;
		float ColSize = Player->Get_ColSize();
		float fSquareRad = powf(Player->Get_BreathRad(),2);
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
				vTemp = vMonsterPos - vPlayerPos;
				fTemp = D3DXVec3Dot(&vDir, &vTemp)/D3DXVec3Dot(&vDir, &vDir);
				vTemp = vPlayerPos + vDir*fTemp - vMonsterPos;

				_vec3 vMola = vPlayerPos + vDir*fTemp - vMonsterPos;

				if(D3DXVec3Dot(&vMola,&vMola) < fSquareRad)
					static_cast<CMonsterMain*>(pMonster)->Kill_Lay_Monster(fTimeDelta);

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
					Player->Set_MouseTime(1.f);
					
				}
			}
		}
	}
}

void CCollisionMgr::Player_Boss(list<CGameObject*>* _pPlayer, list<CGameObject*>* _pBoss, const float & fTimeDelta)
{
	for (auto& pPlayer : *_pPlayer)
	{
		//플레이어는 한명이니 한번만
		CPlayerMain* Player = static_cast<CPlayerMain*>(pPlayer);
		_vec3 vPlayerPos;
		_vec3 vTemp;
		float fTemp;
		float ColSize = Player->Get_ColSize();
		float fSquareRad = powf(Player->Get_BreathRad(), 2);
		pPlayer->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);
		if (Player->Get_Breath())
		{
			//브레스 방향 구하기
			_vec3 vDir;
			memcpy(&vDir, &pPlayer->Get_Transform()->Get_World().m[2][0], sizeof(_vec3));
			for (auto& pBoss : *_pBoss)
			{
				_vec3 vMonsterPos, vDis;
				pBoss->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
				vTemp = vMonsterPos - vPlayerPos;
				fTemp = D3DXVec3Dot(&vDir, &vTemp) / D3DXVec3Dot(&vDir, &vDir);
				vTemp = vPlayerPos + vDir*fTemp - vMonsterPos;

				_vec3 vMola = vPlayerPos + vDir*fTemp - vMonsterPos;

				if (D3DXVec3Dot(&vMola, &vMola) < fSquareRad)
					static_cast<CMonsterMain*>(pBoss)->Kill_Boss(fTimeDelta);
			}
		}
		else
		{
			for (auto& pBoss : *_pBoss)
			{
				_vec3 vMonsterPos, vDis;
				pBoss->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
				vDis = vPlayerPos - vMonsterPos;
				if (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < ColSize)
				{
					static_cast<CMonsterMain*>(pBoss)->Kill_Monster(fTimeDelta);
					Player->Set_MouseTime(1.f);

				}
				//부위 공격 위치랑 사이즈 바꿔야함
				if (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < ColSize)
				{
					if (Player->Get_State() != CPlayerMain::STATE::STATE_HIT)
					{
						vDis.y = 0.f;
						D3DXVec3Normalize(&vDis, &vDis);
						Player->Set_HitDir(vDis);
						Player->Set_Sate(CPlayerMain::STATE::STATE_HIT);
						Player->Add_Hp(-30);
					}
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
