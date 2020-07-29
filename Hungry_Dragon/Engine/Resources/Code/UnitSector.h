#ifndef UnitSector_h__
#define UnitSector_h__

#include "BaseSector.h"

BEGIN(Engine)

class ENGINE_DLL CUnitSector : public CBaseSector
{
protected:
	explicit CUnitSector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUnitSector(const CUnitSector& rhs);
	virtual ~CUnitSector(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CUnitSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
