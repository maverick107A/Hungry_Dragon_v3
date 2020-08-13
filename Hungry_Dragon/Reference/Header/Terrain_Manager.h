#ifndef Terrain_Manager_h__
#define Terrain_Manager_h__

#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CTerrain_Manager : public CComponent
{
	DECLARE_SINGLETON(CTerrain_Manager)

private:
	explicit CTerrain_Manager(void);
	virtual ~CTerrain_Manager(void);

public:
	

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;	

private:
	virtual CComponent*	Clone(void) { return nullptr; }
	virtual void Free(void);

};

END
#endif // Renderer_h__
