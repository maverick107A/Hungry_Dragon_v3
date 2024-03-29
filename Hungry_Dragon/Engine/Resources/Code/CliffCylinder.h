#ifndef CliffCylinder_h__
#define CliffCylinder_h__

#include "VIBuffer.h"
#include "SkyCube.h"

BEGIN(Engine)

class ENGINE_DLL CCliffCylinder : public CVIBuffer
{
private:
	explicit CCliffCylinder(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCliffCylinder(const CCliffCylinder& rhs);
	virtual ~CCliffCylinder(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	float Get_Height() { return m_fHeight; }
	float Get_Radius() { return m_fRadius; }

private:
	float m_fHeight = 0.f;
	UINT m_uStackCount = 0;
	float m_fStackHeight = 0.f;
	float m_fRadius = 0.f;
	UINT m_uRingCount = 0;
	UINT m_uSliceCount = 0;
	UINT m_uVtxNum = 0;


public:
	static CCliffCylinder*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
