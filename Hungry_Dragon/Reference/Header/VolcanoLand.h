#ifndef VolcanoLand_h__
#define VolcanoLand_h__

#include "BaseLand.h"
#include "Texture.h"

BEGIN(Engine)

class ENGINE_DLL CVolcanoLand : public CBaseLand
{
protected:
	explicit CVolcanoLand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVolcanoLand(const CVolcanoLand& rhs);
	virtual ~CVolcanoLand(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

private:
	CTexture* m_pTerrainTex;


public:
	static CVolcanoLand*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
