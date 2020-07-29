#ifndef RoadSector_h__
#define RoadSector_h__

#include "BaseSector.h"

BEGIN(Engine)

class ENGINE_DLL CRoadSector : public CBaseSector
{
protected:
	explicit CRoadSector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRoadSector(const CRoadSector& rhs);
	virtual ~CRoadSector(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CRoadSector*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
