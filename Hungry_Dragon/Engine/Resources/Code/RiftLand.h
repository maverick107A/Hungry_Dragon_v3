#ifndef RiftLand_h__
#define RiftLand_h__

#include "BaseLand.h"
#include "Texture.h"

BEGIN(Engine)

class ENGINE_DLL CRiftLand : public CBaseLand
{
protected:
	explicit CRiftLand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRiftLand(const CRiftLand& rhs);
	virtual ~CRiftLand(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

private:
	CTexture* m_pTerrainTex;

public:
	static CRiftLand*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
