#ifndef SkyCube_h__
#define SkyCube_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CSkyCube : public CVIBuffer
{
private:
	explicit CSkyCube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkyCube(const CSkyCube& rhs);
	virtual ~CSkyCube(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CSkyCube*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
