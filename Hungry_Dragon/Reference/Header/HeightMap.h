#ifndef HeightMap_h__
#define HeightMap_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CHeightMap : public CVIBuffer {
private:
	explicit CHeightMap(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHeightMap(const CHeightMap& rhs);
	virtual ~CHeightMap(void);

public:
	const vector<_float> Get_Height() const {
		return m_vecHeight;
	}

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CHeightMap*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;

public:
	void Read_HeightMap(std::string _src);

private:
	IDirect3DTexture9* m_pTex=0;
	vector<_float>		m_vecHeight;
};


END
#endif // VIBuffer_h__
