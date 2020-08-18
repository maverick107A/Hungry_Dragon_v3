#ifndef HeightCol_h__
#define HeightCol_h__

#include "BaseLand.h"

BEGIN(Engine)

class ENGINE_DLL CHeightCol : public CBaseLand
{
private:
	explicit CHeightCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHeightCol(const CHeightCol& rhs);
	virtual ~CHeightCol(void);

public:
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer(void) override;

	void Set_Height(const _tchar* _pPath, _float _fHeight = 2560.f);
	void Set_HeightRedBase(const _tchar* _pPath, _float _fHeight = 2560.f);
	void Set_RandomHeight(_float _fMag, _uint uContrast);
	VTXCOL* Get_EntryVB();

private:
	_ulong				m_dwCntZ;
	_ulong				m_dwCntX;

public:
	static CHeightCol*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
