#ifndef Particle_h__
#define Particle_h__

#include "Resources.h"

BEGIN(Engine)
class ENGINE_DLL CParticle :public CResources {
protected:
	explicit CParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CParticle(const CParticle& rhs);
	virtual ~CParticle(void);

public:
	virtual HRESULT Ready_Buffer(void);
	virtual void	Render_Buffer(void);
	virtual void	Render_Begin(void);
	virtual void	Render_End(void);
	virtual void	Reset_Buffer(void);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute)PURE;
	virtual void	Add_Particle();
	bool			Is_Empty(void);
	bool			Is_Dead(void);
	void			Set_Texture(_tchar* texFileName);
	void			Set_Size(_float _fSize);
	DWORD			FloatToDword(float& f);
	float			Get_RandomFloat(float lowBound, float highBound);
	void			Get_RandomVector(_vec3* _out, _vec3* _min, _vec3* _max);

public:
	virtual CResources*	Clone(_vec3 _origin, BoundingBox _boundingBox)PURE;
	virtual void Free(void);

protected:
	virtual void Romove_DeadParticle(void);



protected:
	_vec3					m_vOrigin;
	BoundingBox				m_BoundingBox;

	float					m_fEmitRate;
	float					m_fSize;
	float					m_fSpeed;
	IDirect3DTexture9*		m_Tex=nullptr;
	IDirect3DVertexBuffer9*	m_Vb;
	list<ATTRIBUTE>			m_arrParticle;
	int						m_iMaxParticle;

	DWORD					m_VbSize;
	DWORD					m_vOffset;
	DWORD					m_BatchSize;
};

END
#endif
