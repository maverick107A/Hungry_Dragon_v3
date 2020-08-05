#include "Scene.h"

USING(Engine)

Engine::CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

Engine::CScene::~CScene(void)
{

}

HRESULT Engine::CScene::Ready_Scene(void)
{
	return S_OK;
}

_int Engine::CScene::Update_Scene(const _float& fTimeDelta)
{
	_int iEnd = 0;

	for (auto& iter : m_mapLayer)
	{
		iter.second->Set_Player(m_vPlayerPos);
		iEnd = iter.second->Update_Layer(fTimeDelta);

		if (iEnd & 0x80000000)
			return iEnd;
	}

	return iEnd;
}

void CScene::LateUpdate_Scene(const _float & fTimeDelta) {
	for (auto& iter : m_mapLayer) {
		iter.second->LateUpdate_Layer(fTimeDelta);
	}
}

void Engine::CScene::Render_Scene(void)
{
	for (auto& iter : m_mapLayer)
		iter.second->Render_Layer();
}

void Engine::CScene::Free(void)
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();

	Safe_Release(m_pGraphicDev);
}

CComponent* Engine::CScene::Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, Engine::CGameObject* _pObj, const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second->Get_Component(_pObj, pComponentTag, eID);
}

