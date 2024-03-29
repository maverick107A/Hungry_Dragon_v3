#ifndef Torus_h__
#define Torus_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTorus :public CResources {
protected:
	explicit CTorus(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTorus(const CTorus& rhs);
	virtual ~CTorus(void);

public:
	void Get_Radius(_float* _fInnerRadius, _float* _fOuterRadius);

public:
	virtual HRESULT Ready_Buffer(void);
	virtual void	Render_Buffer(void);

public:
	static CTorus* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void);
	virtual void		Free(void);

protected:
	ID3DXMesh*		m_pTorus;
	_float			m_fInnerRadius=5.f;
	_float			m_fOuterRadius=60.f;
};

END

#endif // !Torus_h__
