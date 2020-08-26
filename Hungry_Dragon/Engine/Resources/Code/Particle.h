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
	virtual void	Add_Particle();
	float			Get_RandomFloat(float lowBound, float highBound);
	void			Get_RandomVector(_vec3* _out, _vec3* _min, _vec3* _max);

	void			Set_Texture(_tchar* texFileName);
	void			Set_Color(D3DXCOLOR _color);
	void			Set_Size(_float _fSize);
	void			Set_Empty();
	void			Set_LifeTime(bool _isLifeLimit, _float _lifeTime);
	void			Set_Origin(_vec3 _newOriginPos);

	void			Set_ZeroToOne(float _fZero, float _fOne) { m_fZero = _fZero; m_fOne = _fOne;	};

public:
	virtual HRESULT Ready_Buffer(void);
	virtual void	Render_Buffer(void);
	virtual void	Render_Begin(void);
	virtual _int	Update_Component(const _float& fTimeDelta);
	virtual void	Render_End(void);
	virtual void	Reset_Buffer(void);

public:
	virtual void	Reset_Particle(ATTRIBUTE* _attribute)PURE;
	void			Empty_Particle(void);
	bool			Is_Empty(void);
	bool			Is_Dead(void);
	DWORD			FloatToDword(float& f);


public:
	virtual CResources*	Clone(_vec3 _origin, BoundingBox _boundingBox)PURE;
	virtual void Free(void);

protected:
	virtual void Romove_DeadParticle(void);

protected:
	//����! ���� ��ǥ �ƴ�! �����Ǵ� �� ���� ������ǥ�� �־��� ��.
	_vec3					m_vOrigin;			//��ƼŬ�� ������ ��ġ
	BoundingBox				m_BoundingBox;		//��ƼŬ�� ��µ� ����

	float					m_fEmitRate;		//���� �ֱ�
	float					m_fSize;			//��ƼŬ ������
	float					m_fSpeed;			//��ƼŬ �̵� �ӵ�
	IDirect3DTexture9*		m_Tex=nullptr;
	IDirect3DVertexBuffer9*	m_Vb;
	list<ATTRIBUTE>			m_arrParticle;
	int						m_iMaxParticle;

	DWORD					m_VbSize;
	DWORD					m_vOffset;
	DWORD					m_BatchSize;

	bool					m_bIsLifeLimit=false;
	_float					m_fLifeTime;

	float m_fZero = 10.f;
	float m_fOne = 40.f;
};

END
#endif
