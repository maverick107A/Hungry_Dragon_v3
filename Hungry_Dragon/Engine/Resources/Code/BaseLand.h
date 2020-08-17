#ifndef BaseLand_h__
#define BaseLand_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CBaseLand : public CVIBuffer
{
protected:
	explicit CBaseLand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBaseLand(const CBaseLand& rhs);
	virtual ~CBaseLand(void);

public:
	virtual HRESULT		Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void		Render_Buffer(void);

public:
	vector<int>& Get_TerrainHeight();
	vector<float>& Get_AdvanceHeight();

protected:
	vector<int>			m_vecHeight;
	vector<float>		m_vecAdvanceHeight;
	bool				m_bCheck = true;

protected:
	HANDLE				m_hFile;	// ≥Ù¿Ã∏  ¡§∫∏
	BITMAPFILEHEADER	m_fh;
	BITMAPINFOHEADER	m_ih;

public:
	static CBaseLand*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
