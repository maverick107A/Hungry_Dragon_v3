#ifndef Meteor_Linear_h__
#define Meteor_Linear_h__

#include "Define.h"
#include "Meteor_Object.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END

USING(Engine)

class CMeteor_Linear : public CMeteor_Object {
private:
	explicit CMeteor_Linear(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor_Linear(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void		Set_Radius(_vec3 _vRadius) { m_vRadius = _vRadius; }
	void		Set_Dest(_vec3 _vDest) { m_vDest = _vDest; }
	void		Set_Center(_vec3 _vCenter) { m_vCenter = _vCenter; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Limit(float _fLimit) { m_fLimit = _fLimit; }
	void		Set_Delta(_vec3 _vDelta) { m_vDelta = _vDelta; }

private:
	HRESULT		Add_Component(void);

private:
	_vec3		m_vRadius = { 500.f, 0.f, 0.f };
	_vec3		m_vDest = { 0.f, 0.f, 0.f };
	_vec3		m_vCenter = { 19200.f, 5000.f, 19200.f };
	_vec3		m_vDelta = { 0.f,0.f,0.f };
	float		m_fAngle = 0.f;
	float		m_fLimit = 10.f;

public:
	static CMeteor_Linear*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
