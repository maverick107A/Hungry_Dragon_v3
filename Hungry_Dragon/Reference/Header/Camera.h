#ifndef Camera_h__
#define Camera_h__

#include "Component.h"

BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CCamera : public CComponent
{
private:
	explicit CCamera(void);
	virtual ~CCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Component(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp, CBaseLand* _pTerrain);

public:
	_vec3			Get_Pos() { return m_vPos; }

public:
	void			Set_AngleZPlus(float _fAngle) { m_fAngleZ += _fAngle; }

private:
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up);
	void			Move_Camera_InMFC(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up);
	void			Ride_Terrain(CBaseLand* _pTerrain);

private:
	POINT			m_tCenter = {};
	float			m_fAngleY = 0.f;
	float			m_fAngleX = 0.f;
	float			m_fAngleZ = 0.f;
	float			m_fCameraDis = 15.f;
	float			m_fCameraDisSpeed = 0.5f;
	_vec3			m_vDir = {};
	_vec3			m_vDir1 = {};
	_vec3			m_vUpOrigin = { 0.f, 1.f, 0.f };
	_vec3			m_vUp = { 0.f, 1.f, 0.f };
	_vec3			m_vUp1 = { 0.f, 1.f, 0.f };
	_vec3			m_vLook = { 0.f,0.f,1.f };
	_vec3			m_vPos = { 0.f,50.f,0.f };
	bool			m_bTCol = false;

public:
	static CCamera*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // Camera_h__
