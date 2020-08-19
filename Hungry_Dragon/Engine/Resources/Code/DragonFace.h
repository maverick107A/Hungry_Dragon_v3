#ifndef DragonFace_h__
#define DragonFace_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CDragonFace : public CVIBuffer
{
private:
	explicit CDragonFace(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonFace(const CDragonFace& rhs);
	virtual ~CDragonFace(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	VTXCOL*		pVertex = nullptr;
	float		m_fAngle = 0.f;
	float		m_fAngleSpeed = 0.1f;
	bool		m_bReverse = false;

	float		m_fMouse_Length = 1.f;
	float		m_fMouse_Height = 0.35f;
	float		m_fMouse_Width = 0.5f;

public:
	static CDragonFace*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void)override;
	virtual void Free(void) override;	

public:
	list<INDEX16> indexList;
	list<VTXCOL>  vertexList;
};

END
#endif // DragonFace_h__
