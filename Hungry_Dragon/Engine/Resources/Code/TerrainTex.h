#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"
BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTex(const CTerrainTex& rhs);
	virtual ~CTerrainTex(void);

public:
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer(void) override;
public:
	_ulong Get_Height(const _float& _X, const _float& _Z);
	void Piking_Terrain(const _float  & _x, const _float & _z,  _float  & _Index_X,  _float   & _Index_Y, _int   & _TriPoint);



private:
	HANDLE				m_hFile;
	BITMAPFILEHEADER	m_fh;
	BITMAPINFOHEADER	m_ih;
	_float				m_Terrain_Interval;
	_ulong *			m_pHight;
	_ulong				m_dwCntZ;
	_ulong				m_dwCntX;
	
public:
	static CTerrainTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;
};

END
#endif // TerrainTex_h__