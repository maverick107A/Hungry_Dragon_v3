#include "Layer.h"
#include "ObjectPool.h"
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

_int Engine::CLayer::Update_Layer(const _float& fTimeDelta)
{
	_int iEnd = 0;
	_int iBulletEnd = 0;

	for (auto& iter = m_mapObject.begin(); iter != m_mapObject.end();)
	{
		iEnd = iter->second->Update_Object(fTimeDelta);
		iter->second->Set_Player(m_vPlayerPos);

		if (MONSTER_DEAD == iEnd)
		{
			// 비활성리스트에 넣어주기 iter;
			CObjectPool::GetInstance()->Add_Object_Pool(iter->second, OBJID::STAND_MONSTER);
			iter = m_mapObject.erase(iter);
		}
		else
			++iter;
	}


	for (auto& iter = m_listBullet.begin(); iter != m_listBullet.end();)
	{
		if (m_listBullet.begin() == m_listBullet.end())
			return iEnd;


		iBulletEnd = (*iter)->Update_Object(fTimeDelta);
		(*iter)->Set_Player(m_vPlayerPos);

		if (BULLET_DEAD == iBulletEnd)
		{
			CObjectPool::GetInstance()->Add_Object_Pool(*iter, OBJID::NORMAL_BULLET);
			iter =	m_listBullet.erase(iter);
		}
		else
			++iter;

	}


	return iEnd;
}

void Engine::CLayer::Render_Layer(void)
{
	for (auto& iter : m_mapObject)
		iter.second->Render_Object();

	for (auto& iter : m_listBullet)
		iter->Render_Object();
	
}

CLayer* Engine::CLayer::Create(void)
{
	CLayer*	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CLayer::Free(void)
{
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();


	 for (auto& iter : m_listBullet)
	 {
		 Safe_Release(iter);
	 }
	 m_listBullet.clear();

}

HRESULT Engine::CLayer::Add_Object(const _tchar* pObjTag, CGameObject* pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_mapObject.emplace(pObjTag, pGameObject);

	return S_OK;
}

HRESULT Engine::CLayer::Add_Bullet_Object(CGameObject * pGameObject , _vec3 _pos)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	pGameObject->Set_Pos(_pos);
	m_listBullet.push_back(pGameObject);

	return S_OK;
}

CComponent* Engine::CLayer::Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second->Get_Component(pComponentTag, eID);
}