#include "Layer.h"
#include "ObjectPool.h"
#include "CollisionMgr.h"

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
			else if (iEnd == BULLET_DEAD)
			{
				CObjectPool::GetInstance()->Add_Object_Pool(*iter_obj, OBJID::NORMAL_BULLET);
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

	//충돌처리
	//list<CGameObject*>	listMonster = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"Monster"))->second;
	//list<CGameObject*>	listPlayer = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(L"TestPlayer"))->second;
	//for (auto& pPlayer : listPlayer)
	//{
	//	for (auto& pMonster : listMonster)
	//	{
	//		if(CCollisionMgr::Player_Monster(pPlayer, pMonster))
	//		{
	//		}
	//	}
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

CComponent* Engine::CLayer::Get_Component(CGameObject* _findObj,const _tchar* pComponentTag, COMPONENTID eID)
{
	return _findObj->Get_Component(pComponentTag, eID);
}