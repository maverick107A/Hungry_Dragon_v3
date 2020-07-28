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

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CBoardSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
