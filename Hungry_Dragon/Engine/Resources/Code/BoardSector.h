#ifndef BoardSector_h__
#define BoardSector_h__

#include "BaseSector.h"

BEGIN(Engine)

class ENGINE_DLL CBoardSector : public CBaseSector
{
protected:
	explicit CBoardSector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBoardSector(const CBoardSector& rhs);
	virtual ~CBoardSector(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// 스태틱의 경우 거의 카메라만 바라볼거고 카메라 각도에 따라 탑뷰 + 쿼터뷰블렌딩 적용


public:
	static CBoardSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
