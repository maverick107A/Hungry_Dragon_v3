#ifndef GlacierTex_h__
#define GlacierTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CGlacierTex : public CVIBuffer
{
private:
	explicit CGlacierTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGlacierTex(const CGlacierTex& rhs);
	virtual ~CGlacierTex(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	// �ɰ��ų� ��ƼŬ�� ó���ϴ� �� ���� ������Ʈ�� ���� ����

public:
	static CGlacierTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	
};

END
#endif // RcTex_h__
