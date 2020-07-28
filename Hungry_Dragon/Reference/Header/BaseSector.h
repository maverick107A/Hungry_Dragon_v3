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

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CBaseSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
