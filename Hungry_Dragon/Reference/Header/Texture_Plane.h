#ifndef Texture_Plane_h__
#define Texture_Plane_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTexture_Plane : public CVIBuffer
{
private:
	explicit CTexture_Plane(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture_Plane(const CTexture_Plane& rhs);
	virtual ~CTexture_Plane(void);

public:
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer(void) override;

	void Set_Height(void* _bitmap);

private:
	_ulong				m_dwCntZ;
	_ulong				m_dwCntX;

public:
	static CTexture_Plane*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
