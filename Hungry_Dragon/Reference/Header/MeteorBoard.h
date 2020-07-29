#ifndef MeteorBoard_h__
#define MeteorBoard_h__

#include "BaseBoard.h"

BEGIN(Engine)

class ENGINE_DLL CMeteorBoard : public CBaseBoard
{
private:
	explicit CMeteorBoard(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMeteorBoard(const CMeteorBoard& rhs);
	virtual ~CMeteorBoard(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// 스태틱의 경우 거의 카메라만 바라볼거고 카메라 각도에 따라 탑뷰 + 쿼터뷰블렌딩 적용


public:
	static CMeteorBoard*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
