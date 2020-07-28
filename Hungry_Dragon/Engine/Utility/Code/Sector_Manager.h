#ifndef Sector_Manager_h__
#define Sector_Manager_h__

#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CSector_Manager : public CComponent
{
	DECLARE_SINGLETON(CSector_Manager)

private:
	explicit CSector_Manager(void);
	virtual ~CSector_Manager(void);

public:
	

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;	// 필요한가?

private:
	virtual CComponent*	Clone(void) { return nullptr; }
	virtual void Free(void);

};

END
#endif // Renderer_h__
