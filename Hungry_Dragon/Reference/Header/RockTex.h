#ifndef RockTex_h__
#define RockTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRockTex : public CVIBuffer
{
private:
	explicit CRockTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRockTex(const CRockTex& rhs);
	virtual ~CRockTex(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	void Set_Side(void* _bitmap);

public:
	static CRockTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
