#ifndef VICustom_h__
#define VICustom_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVICustom :public CVIBuffer
{
private:
	explicit CVICustom(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVICustom(const CVICustom& rhs);
	virtual ~CVICustom(void);

public:
	virtual HRESULT Ready_Buffer(void)override;
	HRESULT			Ready_Buffer(LPCTSTR _address);
	HRESULT			Ready_Buffer(list<VTXCOL> _listVertex, list<INDEX16> _listIndex);
	virtual void Render_Buffer(void)override;
	

public:
	//�ҷ��� .dat ���� �ּ� �ȳ־��ָ� �ƹ��͵� �ȳ���
	static CVICustom* Create(LPDIRECT3DDEVICE9 pGraphicDev);					//�̰Ÿ���
	static CVICustom* Create(LPDIRECT3DDEVICE9 pGraphicDev,list<VTXCOL> _listVertex,list<INDEX16> _listIndex);//MFC��
	static CVICustom* Create(LPDIRECT3DDEVICE9 pGraphicDev,LPCTSTR _address);	//�̰� �̿��� ��
	virtual CComponent* Clone(void)override;
	virtual void Free(void)override;

private:
	void Load_VI(LPCTSTR _address);

private:
	list<Engine::VTXCOL>	m_listVertex;
	list<Engine::INDEX16>	m_listIndex;
};
END
#endif
