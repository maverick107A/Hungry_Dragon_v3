#ifndef DragonJaw_h__
#define DragonJaw_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CDragonJaw : public CVIBuffer
{
private:
	explicit CDragonJaw(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonJaw(const CDragonJaw& rhs);
	virtual ~CDragonJaw(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	VTXCOL*		pVertex = nullptr;

public:
	static CDragonJaw*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // DragonJaw_h__