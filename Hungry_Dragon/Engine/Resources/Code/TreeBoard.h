#ifndef TreeBoard_h__
#define TreeBoard_h__

#include "BaseBoard.h"

BEGIN(Engine)

class ENGINE_DLL CTreeBoard : public CBaseBoard
{
private:
	explicit CTreeBoard(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTreeBoard(const CTreeBoard& rhs);
	virtual ~CTreeBoard(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CTreeBoard*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
