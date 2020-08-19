#ifndef DragonBody_h__
#define DragonBody_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CDragonBody : public CVIBuffer
{
private:
	explicit CDragonBody(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonBody(const CDragonBody& rhs);
	virtual ~CDragonBody(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	VTXCOL*		pVertex = nullptr;

public:
	static CDragonBody*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // DragonBody_h__
