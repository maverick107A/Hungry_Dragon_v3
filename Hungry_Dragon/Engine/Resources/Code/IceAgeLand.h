#ifndef IceAgeLand_h__
#define IceAgeLand_h__

#include "BaseLand.h"
#include "Texture.h"

BEGIN(Engine)

class ENGINE_DLL CIceAgeLand : public CBaseLand
{
protected:
	explicit CIceAgeLand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIceAgeLand(const CIceAgeLand& rhs);
	virtual ~CIceAgeLand(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

private:
	CTexture* m_pTerrainTex;


public:
	static CIceAgeLand*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
