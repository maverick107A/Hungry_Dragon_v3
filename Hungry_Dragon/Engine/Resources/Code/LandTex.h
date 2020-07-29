#ifndef LandTex_h__
#define LandTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CLandTex : public CVIBuffer
{
private:
	explicit CLandTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLandTex(const CLandTex& rhs);
	virtual ~CLandTex(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	void Set_Height(void* _bitmap);

public:
	static CLandTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
