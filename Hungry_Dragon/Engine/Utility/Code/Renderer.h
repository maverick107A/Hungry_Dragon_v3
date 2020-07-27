#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer : public CComponent
{
	DECLARE_SINGLETON(CRenderer)

private:
	explicit CRenderer(void);
	virtual ~CRenderer(void);

public:
	void	Add_RenderGroup(RENDERID eType, CGameObject* pGameObject);
	void	Render_GameObject(void);
	void	Clear_RenderGroup(void);

private:
	list<CGameObject*>			m_RenderGroup[RENDER_END];
	LPDIRECT3DDEVICE9			m_pGraphicDev;

private:
	virtual CComponent*	Clone(void) { return nullptr; }
	virtual void Free(void);

};

END
#endif // Renderer_h__
