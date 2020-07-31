#include "ObjectPool.h"
#include "Export_Utility.h"
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
	if (0 == m_listObject[_Type].size())
	{
		return E_FAIL;
	}
	else if ((size_t)iCnt > m_listObject[_Type].size())
	{
		iCnt = m_listObject[_Type].size();
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

	if (0 == m_listObject[_Type].size())
	{
		return E_FAIL;
	}
	else if ((size_t)iCnt > m_listObject[_Type].size())
	{
		iCnt = m_listObject[_Type].size();
	}
	for (int i = 0; i < iCnt; ++i)
	{
		m_Layer->Add_Bullet_Object(m_listObject[_Type].front() , _Pos);
		m_listObject[_Type].pop_front();

	}

	return S_OK;
}

HRESULT CObjectPool::Set_Monster_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{


	if (0 == m_listObject[_Type].size())
	{
		return E_FAIL;
	}
	else if ((size_t)iCnt > m_listObject[_Type].size())
	{
		iCnt = m_listObject[_Type].size();
	}
	for (int i = 0; i < iCnt; ++i)
	{
		_Pos = { _Pos.x + (rand() % 2000) , 0 , _Pos.z +  (rand() % 2000) };
		m_Layer->Add_Monster_Object(m_listObject[_Type].front(), _Pos);
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
