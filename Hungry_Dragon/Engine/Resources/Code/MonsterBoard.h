#ifndef MonsterBoard_h__
#define MonsterBoard_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CMonsterBoard : public CVIBuffer
{
protected:
	explicit CMonsterBoard(LPDIRECT3DDEVICE9 pGraphicDev , _float _iAnimUCnt , _float _iAnimVCnt);
	explicit CMonsterBoard(const CMonsterBoard& rhs);
	virtual ~CMonsterBoard(void);

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

	// ����ƽ�� ��� ���� ī�޶� �ٶ󺼰Ű� ī�޶� ������ ���� ž�� + ���ͺ���� ����


public:
	static CMonsterBoard*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _float _fU, _float _fV);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
	
private:
	_float		m_fTexU;
	_float		m_fTexV;

	_int		m_iAnimUCnt;
	_int		m_iAnimVCnt;

	_float		m_fFrameUCnt = 1;
	_float		m_fFrameVCnt = 1;


};

END
#endif // RcTex_h__
