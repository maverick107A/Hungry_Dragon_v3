#ifndef BaseSector_h__
#define BaseSector_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CBaseSector : public CResources
{
protected:
	explicit CBaseSector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBaseSector(const CBaseSector& rhs);
	virtual ~CBaseSector(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// 스태틱의 경우 거의 카메라만 바라볼거고 카메라 각도에 따라 탑뷰 + 쿼터뷰블렌딩 적용


public:
	static CBaseSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
