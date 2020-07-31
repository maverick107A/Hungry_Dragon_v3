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
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer(void) override;

	void Set_Height(void* _bitmap);

private:
	_ulong				m_dwCntZ;
	_ulong				m_dwCntX;

public:
	static CLandTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
