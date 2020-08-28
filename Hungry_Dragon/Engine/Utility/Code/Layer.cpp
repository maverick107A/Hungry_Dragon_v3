#include "Layer.h"
#include "ObjectPool.h"
#include "CollisionMgr.h"
#include "ParticleMgr.h"
#include "MonsterMain.h"

USING(Engine)

Engine::CLayer::CLayer(void)
{

}

Engine::CLayer::~CLayer(void)
{

}

HRESULT Engine::CLayer::Ready_Layer(void)
{
	return S_OK;
}

void CLayer::Initialize_Layer(void)
{
	for (map<const _tchar*, list<CGameObject*>>::iterator iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		for (list<CGameObject*>::iterator iter_Obj = iter->second.begin(); iter_Obj != iter->second.end(); ++iter_Obj)
		{
			(*iter_Obj)->Initialize_Object();
		}
	}
}

_int Engine::CLayer::Update_Layer(const _float& fTimeDelta)
{
	_int iEnd = 0;
	_int iBulletEnd = 0;
	_int iMonsterEnd = 0;


	for (auto& iter = m_mapObject.begin(); iter != m_mapObject.end();++iter)
	{

		for (auto& iter_obj = (*iter).second.begin(); iter_obj != (*iter).second.end();)
		{
			iEnd = (*iter_obj)->Update_Object(fTimeDelta);

			if (iEnd == MONSTER_DEAD)
			{			
				CObjectPool::GetInstance()->Add_Object_Pool(*iter_obj, OBJID::STAND_MONSTER);
				iter_obj = (*iter).second.erase(iter_obj);
			}
			else if (iEnd == CAVEHORIZONBAT_DEAD)
			{
				CObjectPool::GetInstance()->Add_Object_Pool(*iter_obj, OBJID::HORIZON_REDMONSTER);
				iter_obj = (*iter).second.erase(iter_obj);
			}
			else if (iEnd == BULLET_DEAD)
			{
				CObjectPool::GetInstance()->Add_Object_Pool(*iter_obj, OBJID::NORMAL_BULLET);
				iter_obj = (*iter).second.erase(iter_obj);
			}
			else if (iEnd == PLAYERBULLET_DEAD)
			{
				Safe_Release(*iter_obj);
				iter_obj = (*iter).second.erase(iter_obj);
			}
			else if (0 == iEnd)
			{
				++iter_obj;
			}
			else{
				//일단 지우는 걸로 하고 만약 해당하는 오브젝트 종류의 오브젝트풀이 만들어진다면
				//거기로 Add해줄 것
				Safe_Release(*iter_obj);
				iter_obj = (*iter).second.erase(iter_obj);

			}
		}

	}


	//for (auto& iter = m_listMonster.begin(); iter != m_listMonster.end();)
	//{
	//	if (m_listMonster.begin() == m_listMonster.end())
	//		return iEnd;

	//	iMonsterEnd = (*iter)->Update_Object(fTimeDelta);
	//	//(*iter)->Set_Player(m_vPlayerPos);

	//	if (MONSTER_DEAD == iMonsterEnd)
	//	{
	//		CObjectPool::GetInstance()->Add_Object_Pool(*iter, OBJID::STAND_MONSTER);
	//		iter = m_listMonster.erase(iter);
	//	}
	//	else
	//		++iter;

	//}


	//for (auto& iter = m_listBullet.begin(); iter != m_listBullet.end();)
	//{

	//	if (m_listBullet.begin() == m_listBullet.end())
	//		return iEnd;


	//	iBulletEnd = (*iter)->Update_Object(fTimeDelta);

	//	if (BULLET_DEAD == iBulletEnd)
	//	{
	//		CObjectPool::GetInstance()->Add_Object_Pool(*iter, OBJID::NORMAL_BULLET);
	//		iter =	m_listBullet.erase(iter);
	//	}
	//	else
	//		++iter;

	//}


	return iEnd;
}

void CLayer::LateUpdate_Layer(const _float & fTimeDelta) 
{
	for (auto& iter = m_mapObject.begin(); iter != m_mapObject.end();++iter) 
	{
		for (auto& iter_obj = iter->second.begin(); iter_obj != iter->second.end();++iter_obj)
		{
			(*iter_obj)->LateUpdate_Object(fTimeDelta);
		}
	}
	map<const _tchar*, list<CGameObject*>>::iterator mapPlayer = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"TestPlayer"));
	if (mapPlayer == m_mapObject.end())
		return;
	list<CGameObject*>	listPlayer = mapPlayer->second;

	//충돌처리
	map<const _tchar*, list<CGameObject*>>::iterator mapMonster = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"Monster"));
	if (mapMonster != m_mapObject.end())
	{
		list<CGameObject*>	listMonster = mapMonster->second;

		CCollisionMgr::Player_Monster(&listPlayer, &listMonster, fTimeDelta);
	}
	//보스
	map<const _tchar*, list<CGameObject*>>::iterator mapBoss = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"BossObject"));
	if (mapBoss != m_mapObject.end())
	{
		list<CGameObject*>	listBoss = mapBoss->second;

		CCollisionMgr::Player_Boss(&listPlayer, &listBoss, fTimeDelta);
	}

	//링충돌
	map<const _tchar*, list<CGameObject*>>::iterator mapAccelRing = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"Accel_Torus"));
	if (mapAccelRing != m_mapObject.end())
	{
		list<CGameObject*>* pListAccelRing = &(mapAccelRing->second);

		CCollisionMgr::Player_AccelRing(&listPlayer, pListAccelRing);
	}

	//몬스터 충돌


	//다른 버전

	//auto& iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"TestPlayer"));
	//if (iter != m_mapObject.end())
	//{
	//	CMonsterMain* pMonster = static_cast<CMonsterMain*>(Get_Object(L"Monster", CCollisionMgr::Player_MonsterCol, iter->second.front()));
	//
	//	if (pMonster)
	//		pMonster->Kill_Monster(fTimeDelta);
	//}
	


}

void Engine::CLayer::Render_Layer(void)
{
	

	for (auto& iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		for (auto& iter_obj = iter->second.begin(); iter_obj != iter->second.end(); ++iter_obj)
		{
			(*iter_obj)->Render_Object();
		}
	}	
}

CLayer* Engine::CLayer::Create(void)
{
	CLayer*	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
		Safe_Release(pInstance);

	pInstance->Set_Address();
	return pInstance;
}

void Engine::CLayer::Free(void)
{
	for (auto& iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		for_each(iter->second.begin(), iter->second.end(), CDeleteObj());
		iter->second.clear();
	}

	//for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
}

void CLayer::Delete_Object(const _tchar * _pObjTag)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(_pObjTag));

	for (auto& listiter = iter->second.begin(); listiter != iter->second.end(); ++listiter)
	{
		if(*listiter != nullptr)
		Safe_Release(*listiter);	
	}

	iter->second.clear();
}

HRESULT Engine::CLayer::Add_Object(const _tchar* pObjTag, CGameObject* pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
	{
		m_mapObject.emplace(pObjTag, list<CGameObject*>());

		auto iter_find = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));
		iter_find->second.emplace_back(pGameObject);
	}
	else
	{
		iter->second.emplace_back(pGameObject);
	}

	return S_OK;
}

//HRESULT Engine::CLayer::Add_Bullet_Object(CGameObject * pGameObject , _vec3 _pos)
//{
//	if (nullptr == pGameObject)
//		return E_FAIL;
//
//	pGameObject->Set_Pos(_pos);
//	m_listBullet.push_back(pGameObject);
//
//	return S_OK;
//}
//
//HRESULT Engine::CLayer::Add_Monster_Object(CGameObject * pGameObject, _vec3 _pos)
//{
//	if (nullptr == pGameObject)
//		return E_FAIL;
//	pGameObject->Set_Pos(_pos);
//	//pGameObject->Reborn_Monster();
//	m_listMonster.push_back(pGameObject);
//
//	return S_OK;
//}

void CLayer::Set_Address(void) {
	m_AddressTag.StateFlag &= (char)0;
	m_AddressTag.StateFlag |= (char)128;
	m_AddressTag.LayerAddress = this;
	m_AddressTag.ObjAddress = nullptr;
	m_AddressTag.ComponentAddress = nullptr;
}

CGameObject * CLayer::Get_Object(const _tchar * _pObjTag, bool(*_functionPointer)(CGameObject *_caller, CGameObject *_callee), CGameObject * _callerObj)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(_pObjTag));

	if (iter == m_mapObject.end())
	{
		return nullptr;
	}

	for (list<CGameObject*>::iterator iter_obj = iter->second.begin(); iter_obj != iter->second.end(); ++iter_obj)
	{
		if (_functionPointer(_callerObj, (*iter_obj)))
		{
			return (*iter_obj);
		}
	}

	return nullptr;
}

CGameObject * CLayer::Get_Object(const _tchar * _pObjTag)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(_pObjTag));

	if (iter == m_mapObject.end())
	{
		return nullptr;
	}

	return iter->second.front();
}

CComponent* Engine::CLayer::Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return (iter->second).front()->Get_Component(pComponentTag, eID);
}