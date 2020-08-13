#ifndef CubeCol_h__
#define CubeCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeCol :public CVIBuffer {
private:
	explicit CCubeCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeCol(const CCubeCol& rhs);
	virtual ~CCubeCol(void);

public:
	virtual HRESULT Ready_Buffer(void)override;
	virtual void Render_Buffer(void)override;

public:
	static CCubeCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void)override;
	virtual void Free(void)override;

};

END
#endif
