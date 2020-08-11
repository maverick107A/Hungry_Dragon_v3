#ifndef CaveCamera_h__
#define CaveCamera_h__

#include "Component.h"

BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CCaveCamera : public CComponent
{
private:
	explicit CCaveCamera(void);
	virtual ~CCaveCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Camera(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY, CBaseLand* _pTerrain);
	virtual _int	Update_CameraMFC(LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp);
public:
	_vec3			Get_Pos() { return m_vPos; }

public:
	void			Set_AngleZPlus(float _fAngle) { m_fAngleZ += _fAngle; }

private:
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);
	void			Move_Camera_InMFC(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up);
	void			Ride_Terrain(CBaseLand* _pTerrain);
	
private:
	POINT			m_tCenter = {};
	float			m_fAngleY = 0.f;
	float			m_fAngleX = 0.f;
	float			m_fAngleZ = 0.f;
	float			m_fAngleXReal = 0.f;
	float			m_fAngleYReal = 0.f;
	float			m_fAngleZReal = 0.f;
	float			m_fCameraDis = 100.f;
	float			m_fCameraDisSpeed = 0.5f;
	_vec3			m_vDir = {};
	_vec3			m_vUpOrigin = { 0.f, 1.f, 0.f };
	_vec3			m_vUp = { 0.f, 1.f, 0.f };
	_vec3			m_vLook = { 0.f,0.f,1.f };
	_vec3			m_vPos = { 0.f,50.f,0.f };
	bool			m_bTCol = false;

public:
	static CCaveCamera*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // CaveCamera_h__
