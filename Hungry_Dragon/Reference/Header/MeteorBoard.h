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

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CMeteorBoard*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
