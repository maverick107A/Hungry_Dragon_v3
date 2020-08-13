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
	const vector<float>& Get_TerrainHeight();
	const _vec3*		Get_VtxPos(void) const { return m_pPos; }
private:
	vector<float>		m_vecHeight;
	IDirect3DTexture9*	m_pTex;
	_vec3*				m_pPos;
	bool				m_bCheck = true;
	_bool				m_bClone;
public:
	static CTerrain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;
};

END
#endif // Terrain_h__
