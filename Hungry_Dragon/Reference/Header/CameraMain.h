#ifndef CameraMain_h__
#define CameraMain_h__

#include "Component.h"

BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CCameraMain : public CComponent
{
protected:
	explicit CCameraMain(void);
	virtual ~CCameraMain(void);

public:
	HRESULT			Ready_Camera(void) { return 0; }
	virtual _int	Update_Camera(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY, CBaseLand* _pTerrain) { return 0; }

public:
	_vec3			Get_Pos() { return m_vPos; }

public:
	void			Set_AngleZPlus(float _fAngle) { m_vAngle.z += _fAngle; }
	void			Set_Angle(int _iIndex, float _fAngle) { m_vAngle[_iIndex] = _fAngle; }
	void			Set_AfterAngle(int _iIndex, float _fAngle) { m_vAfterAngle[_iIndex] = _fAngle; }
	void			Set_Shock() { m_bShock = true; m_fShockAngle = 5.f; }

protected:
	virtual void	Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY) {}
	void			Ride_Terrain(CBaseLand* _pTerrain);
	void			Shock_Cam();
	
protected:
	POINT			m_tCenter = {};
	//float			m_fAngleY = 0.f;
	//float			m_fAngleX = 0.f;
	//float			m_fAngleZ = 0.f;
	//float			m_fAngleXReal = 0.f;
	//float			m_fAngleYReal = 0.f;
	//float			m_fAngleZReal = 0.f;
	float			m_fCameraDis = 25.f;
	float			m_fCameraDisSpeed = 0.5f;
	_vec3			m_vAngle = {0.f,0.f,0.f};
	_vec3			m_vAfterAngle = {0.f,0.f,0.f};
	_vec3			m_vDir = {0.f,0.f,0.f};
	_vec3			m_vUpOrigin = { 0.f, 1.f, 0.f };
	_vec3			m_vUp = { 0.f, 1.f, 0.f };
	_vec3			m_vLook = { 0.f,0.f,1.f };
	_vec3			m_vPos = { 0.f,50.f,0.f };
	bool			m_bTCol = false;
	bool			m_bLock = false;


	bool			m_bShock = false;
	bool			m_bCheck = false;
	int				m_iTime = 0;
	float			m_fShockAngle = 0.f;

public:
	static CCameraMain*		Create(void) { return nullptr; }
	virtual CComponent*		Clone(void) { return nullptr; }

protected:
	virtual void Free(void) {}

};
END
#endif // CameraMain_h__
