#include "Management.h"
#include "Export_Utility.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

Engine::CManagement::CManagement(void)
{

}

Engine::CManagement::~CManagement(void)
{
	Free();
}

HRESULT Engine::CManagement::Set_Scene(CScene* pScene)
{
	Safe_Release(m_pScene);

	Engine::Clear_RenderGroup();

	m_pScene = pScene;
	m_pFormerScene = m_pScene;
	m_pScene->Initialize_Scene();

	return S_OK;
}

_int Engine::CManagement::Update_Scene(const _float& fTimeDelta)
{
	if (nullptr == m_pScene)
		return -1;

	m_pScene->Update_Scene(fTimeDelta);

	if (m_pScene != m_pFormerScene) {
		m_pFormerScene = m_pScene;
	}

	return 0;
}

void CManagement::LateUpdate_Scene(const _float & fTimeDelta) {
	m_pScene->LateUpdate_Scene(fTimeDelta);
}

void Engine::CManagement::Render_Scene(void)
{
	if (nullptr == m_pScene)
		return;

	m_pScene->Render_Scene();
}

void Engine::CManagement::Free(void)
{
	Safe_Release(m_pScene);
}

CComponent* Engine::CManagement::Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, CGameObject* _pObj ,const _tchar* pComponentTag, COMPONENTID eID)
{
	if (nullptr == m_pScene)
		return nullptr;

	return m_pScene->Get_Component(pLayerTag, pObjTag, _pObj ,pComponentTag, eID);
}

