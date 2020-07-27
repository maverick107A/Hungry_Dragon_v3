#include "Renderer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

Engine::CRenderer::CRenderer(void)
{

}

Engine::CRenderer::~CRenderer(void)
{
	Free();
}

void Engine::CRenderer::Add_RenderGroup(RENDERID eType, CGameObject* pGameObject)
{
	if (RENDER_END <= eType)
		return;

	m_RenderGroup[eType].push_back(pGameObject);
	pGameObject->AddRef();
}

void Engine::CRenderer::Render_GameObject(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& iter : m_RenderGroup[i])
		{
			iter->Render_Object();
			Safe_Release(iter);			// 레퍼런스 카운트 감소
		}
		m_RenderGroup[i].clear();
	}
}

void Engine::CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}

}

void Engine::CRenderer::Free(void)
{
	Clear_RenderGroup();
}

