#ifndef Texture_Square_h__
#define Texture_Square_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTexture_Square :public CVIBuffer {
private:
	explicit CTexture_Square(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture_Square(const CTexture_Square& rhs);
	virtual ~CTexture_Square(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	void Set_VertexColor(DWORD _dwColor);

private:
	LPDWORD m_pColorEntry;

public:
	static CTexture_Square* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
	virtual void Free(void) override;
};

END
#endif
