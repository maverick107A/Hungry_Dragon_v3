#ifndef VentCube_h__
#define VentCube_h__

#include "VIBuffer.h"
#include "SkyCube.h"

BEGIN(Engine)

class ENGINE_DLL CVentCube : public CVIBuffer
{
private:
	explicit CVentCube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVentCube(const CVentCube& rhs);
	virtual ~CVentCube(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	float Get_Height() { return m_fHeight; }
	float Get_Radius() { return m_fRadius; }


private:
	float m_fHeight = 0.f;
	float m_fRadius = 0.f;


public:
	static CVentCube*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
