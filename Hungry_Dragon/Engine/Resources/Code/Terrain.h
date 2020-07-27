#ifndef Terrain_h__
#define Terrain_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrain : public CVIBuffer
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CTerrain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	

public:
	const vector<int>& Get_TerrainHeight();

private:
	vector<int>			m_vecHeight;
	IDirect3DTexture9*	m_pTex;
	bool				m_bCheck = true;
};

END
#endif // Terrain_h__
