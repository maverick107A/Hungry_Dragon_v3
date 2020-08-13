#ifndef CubeDra_h__
#define CubeDra_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeDra : public CVIBuffer
{
private:
	explicit CCubeDra(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeDra(const CCubeDra& rhs);
	virtual ~CCubeDra(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CCubeDra*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // CubeDra_h__
