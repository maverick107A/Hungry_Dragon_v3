#ifndef ObstacleCube_h__
#define ObstacleCube_h__

#include "VIBuffer.h"
#include "SkyCube.h"

BEGIN(Engine)

class ENGINE_DLL CObstacleCube : public CVIBuffer
{
private:
	explicit CObstacleCube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CObstacleCube(const CObstacleCube& rhs);
	virtual ~CObstacleCube(void);

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
	static CObstacleCube*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
