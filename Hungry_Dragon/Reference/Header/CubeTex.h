#ifndef CubeTex_h__
#define CubeTex_h__

#include "VIBuffer.h"


BEGIN(Engine)


class ENGINE_DLL CTexture_Cube : public CVIBuffer
{

private:
	explicit CTexture_Cube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture_Cube(const CTexture_Cube& rhs);
	virtual ~CTexture_Cube(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CTexture_Cube*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;



};



END



#endif // CubeTex_h__
