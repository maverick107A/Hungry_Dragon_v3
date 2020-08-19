#ifndef DragonWing_h__
#define DragonWing_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CDragonWing : public CVIBuffer
{
private:
	explicit CDragonWing(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonWing(const CDragonWing& rhs);
	virtual ~CDragonWing(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	VTXCOL*		pVertex = nullptr;

public:
	static CDragonWing*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // DragonWing_h__
