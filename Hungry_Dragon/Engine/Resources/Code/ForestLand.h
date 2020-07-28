#ifndef ForestLand_h__
#define ForestLand_h__

#include "BaseLand.h"
#include "Texture.h"

BEGIN(Engine)

class ENGINE_DLL CForestLand : public CBaseLand
{
protected:
	explicit CForestLand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CForestLand(const CForestLand& rhs);
	virtual ~CForestLand(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

private:
	CTexture* m_pTerrainTex;

public:
	static CForestLand*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
