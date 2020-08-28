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
		float fSquareRad = powf(float(Player->Get_BreathRad()),2);
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
		float fSquareRad = powf(float(Player->Get_BreathRad()), 2);
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
				CMonsterMain* Boss = static_cast<CMonsterMain*>(pBoss);
				_vec3 vMonsterPos, vDis;
				pBoss->Get_Transform()->Get_Info(Engine::INFO_POS, &vMonsterPos);
				vDis = vPlayerPos - vMonsterPos;
				if (powf(vDis.x, 2) + powf(vDis.y, 2) + powf(vDis.z, 2) < ColSize)
				{
					Boss->Kill_Monster(fTimeDelta);
					Player->Set_MouseTime(1.f);

				}
				//부위 공격 위치랑 사이즈 바꿔야함
				_vec3 vLhandPos, vRhandPos, vLDis, vRDis;
				_matrix matLeft, matRight;
				float BossSize, HandSize;
				matLeft = Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_LEFTHAND)->m_matWorld*Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_LEFTARM)->Get_WorldWithoutScale()*Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_BODY)->Get_WorldWithoutScale()*Boss->Get_Transform()->m_matWorld;
				matLeft = Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_RIGHTHAND)->m_matWorld*Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_RIGHTARM)->Get_WorldWithoutScale()*Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_BODY)->Get_WorldWithoutScale()*Boss->Get_Transform()->m_matWorld;

				memcpy(&vLhandPos, &matLeft._41, sizeof(_vec3));
				memcpy(&vRhandPos, &matRight._41, sizeof(_vec3));
				HandSize = Boss->Get_Parts_Transform(CMonsterMain::BOSSPARTS::PART_LEFTHAND)->m_vScale.x;
				BossSize = Boss->Get_Transform()->m_vScale.x;
				vLDis = vPlayerPos - vLhandPos;
				vRDis = vPlayerPos - vRhandPos;
				if (D3DXVec3Dot(&vLDis,&vLDis) < BossSize*BossSize*HandSize*HandSize*9)
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
				if (D3DXVec3Dot(&vRDis, &vRDis) < BossSize*BossSize*HandSize*HandSize*9)
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

void CCollisionMgr::Player_AccelRing(list<CGameObject*>* _pPlayer, list<CGameObject*>* _pAccelIing)
{
	CPlayerMain* pPlayer = static_cast<CPlayerMain*>(_pPlayer->front());
	_vec3 vPlayerPos;
	pPlayer->Get_Transform()->Get_Info(Engine::INFO_POS, &vPlayerPos);

	list<CGameObject*>::iterator iter_Ring = _pAccelIing->begin();
	int iA = 10;
	for (; iter_Ring != _pAccelIing->end(); ++iter_Ring)
	{
		_vec3 vRingPos;
			
		CTransform* tempTrans = (*iter_Ring)->Get_Transform();
		tempTrans->Get_Info(Engine::INFO_POS, &vRingPos);
		
		_vec3 vDis = vRingPos - vPlayerPos;
		D3DXVec3Dot(&vDis, &vDis);
		if (D3DXVec3Dot(&vDis, &vDis) < 55.f*55.f)
		{
			pPlayer->Set_PlusSpeed(120.f);
		}
	}

}


void Engine::CCollisionMgr::Free(void)
{
}
