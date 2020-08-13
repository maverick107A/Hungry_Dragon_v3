#include "ObjectPool.h"
#include "Layer.h"
#include <time.h>

USING(Engine)

IMPLEMENT_SINGLETON(CObjectPool)

CObjectPool::CObjectPool(void)
{
	srand(unsigned(time(NULL)));
}


CObjectPool::~CObjectPool(void)
{
	Free();
}

HRESULT CObjectPool::Add_Object_Pool(CGameObject * pGameObject, OBJID _Type)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_listObject[_Type].emplace_back(pGameObject);

	return S_OK;

}

HRESULT CObjectPool::Add_Object_Layer(OBJID _Type, _int iCnt)
{
	int iSize = m_listObject[_Type].size();

	if (0 == iSize)
	{
		return E_FAIL;
	}
	else if (iCnt > iSize)
	{
		iCnt = iSize;
	}

	for (int i = 0; i < iCnt; ++i)
	{
		m_Layer->Add_Object(L"TestPlayer", m_listObject[_Type].front());
		m_listObject[_Type].pop_front();

	}


	return S_OK;
}

HRESULT CObjectPool::Set_Bullet_LayerMap(OBJID _Type, _int iCnt , _vec3 _Pos)
{
	int iSize = m_listObject[_Type].size();
	if (0 == iSize)
	{
		return E_FAIL;
	}
	else if (iCnt > iSize)
	{
		iCnt = iSize;
	}
	for (int i = 0; i < iCnt; ++i)
	{
		CGameObject* insertBullet= m_listObject[_Type].front();
		insertBullet->Set_Pos(_Pos);
		m_Layer->Add_Object(L"Bullet", insertBullet);
		m_listObject[_Type].pop_front();

	}

	return S_OK;
}

HRESULT CObjectPool::Set_Monster_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	int iSize = m_listObject[_Type].size();

	if (0 == iSize)
	{
		return E_FAIL;
	}
	else if (iCnt > iSize)
	{
		iCnt = iSize;
	}
	for (int i = 0; i < iCnt; ++i)
	{
		_vec3 _pPos = { _Pos.x + (rand() % 3000) , 0 , _Pos.z +  (rand() % 3000) };
		CGameObject* insertedMonster = m_listObject[_Type].front();
		insertedMonster->Set_Pos(_pPos);
		m_Layer->Add_Object(L"Monster", insertedMonster);
		m_listObject[_Type].pop_front();
	}

	return S_OK;
}





void CObjectPool::Set_Object_LayerMap(CLayer * _Layer)
{
	m_Layer = _Layer;
}


void CObjectPool::Free(void)
{

	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		for (auto& iter : m_listObject[i])
			Safe_Release(iter);

		m_listObject[i].clear();
	}



}
