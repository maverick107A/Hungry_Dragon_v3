#ifndef Meteor_Circular_h__
#define Meteor_Circular_h__

#include "Define.h"
#include "Meteor_Object.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END

USING(Engine)

class CMeteor_Circular : public CMeteor_Object {
private:
	explicit CMeteor_Circular(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor_Circular(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void		Set_Radius(_vec3 _vRadius) { m_vRadius = _vRadius; }
	void		Set_Axis(_vec3 _vAxis) { m_vAxis = _vAxis; }
	void		Set_Center(_vec3 _vCenter) { m_vCenter = _vCenter; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_RotateSpeed(float _fRotateSpeed) { m_fRotateSpeed = _fRotateSpeed; }

private:
	HRESULT		Add_Component(void);

private:
	_vec3		m_vRadius = { 8000.f, 0.f, 0.f };
	_vec3		m_vAxis = { 0.f, 1.f, 0.f };
	_vec3		m_vCenter = { 19200.f, 5000.f, 19200.f };
	float		m_fAngle = 0.f;
	float		m_fRotateSpeed = 1.f;

public:
	static CMeteor_Circular*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
