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

void CGameObject::Initialize_Object(void)
{
	for (int i = 0; i < ID_END; ++i)
	{
		for (map<const _tchar*, CComponent*>::iterator iter = m_mapComponent[i].begin();iter!=m_mapComponent[i].end();++iter)
		{
			iter->second->Initialize_Component();
		}
	}
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

void CGameObject::LateUpdate_Object(const _float & fTimeDelta) {
	for (auto& iter : m_mapComponent[ID_DYNAMIC]) {
		iter.second->LateUpdate_Component(fTimeDelta);
	}

	return;
}

void Engine::CGameObject::Render_Object(void)
{

}

void CGameObject::Set_PatternEnd(_bool _bPatternEnd)
{
	m_bPatternEnd = _bPatternEnd;
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

CTransform * CGameObject::Get_Transform()
{
	return m_pTransform;
}

void CGameObject::Set_Address(CLayer * _pLayer) {
	m_AddressTag.StateFlag &= (char)0;
	m_AddressTag.StateFlag |= (char)64;
	m_AddressTag.LayerAddress = _pLayer;
	m_AddressTag.ObjAddress = this;
	m_AddressTag.ComponentAddress = nullptr;
}

