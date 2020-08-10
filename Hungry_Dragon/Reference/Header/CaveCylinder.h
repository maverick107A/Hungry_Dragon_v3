#ifndef CaveCylinder_h__
#define CaveCylinder_h__

#include "VIBuffer.h"
#include "SkyCube.h"

BEGIN(Engine)

class ENGINE_DLL CCaveCylinder : public CVIBuffer
{
private:
	explicit CCaveCylinder(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCaveCylinder(const CCaveCylinder& rhs);
	virtual ~CCaveCylinder(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

private:
	float m_fHeight = 0.f;
	UINT m_uStackCount = 0;
	float m_fStackHeight = 0.f;
	float m_fRadius = 0.f;
	UINT m_uRingCount = 0;
	UINT m_uSliceCount = 0;
	UINT m_uVtxNum = 0;


public:
	static CCaveCylinder*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
