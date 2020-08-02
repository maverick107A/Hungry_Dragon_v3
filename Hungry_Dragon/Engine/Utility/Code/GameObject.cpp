#include "GameObject.h"

USING(Engine)

Engine::CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

Engine::CGameObject::~CGameObject(void)
{

}

HRESULT Engine::CGameObject::Ready_Object(void)
{
	return S_OK;
}

_int Engine::CGameObject::Update_Object(const _float& fTimeDelta)
{
	_int iResult = 0;

	for (auto& iter : m_mapComponent[ID_DYNAMIC])
	{
	  iResult = iter.second->Update_Component(fTimeDelta);

	  if (iResult & 0x80000000)
		  return -1;
	}

	return iResult;
}

void Engine::CGameObject::Render_Object(void)
{

}

void Engine::CGameObject::Free(void)
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
		m_mapComponent[i].clear();
	}	

	Safe_Release(m_pGraphicDev);
}

CComponent* Engine::CGameObject::Find_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapComponent[eID].begin(), m_mapComponent[eID].end(), CTag_Finder(pComponentTag));

	if (iter == m_mapComponent[eID].end())
		return nullptr;

	return iter->second;
}

CComponent* Engine::CGameObject::Get_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = Find_Component(pComponentTag, eID);

	if (nullptr == pComponent)
		return nullptr;

	return pComponent;
}

void CGameObject::Set_Address(CLayer * _pLayer) {
	m_AddressTag.StateFlag &= (char)0;
	m_AddressTag.StateFlag &= (char)64;
	m_AddressTag.LayerAddress = _pLayer;
	m_AddressTag.ObjAddress = this;
	m_AddressTag.ComponentAddress = nullptr;
}

