#ifndef Camera_h__
#define Camera_h__

#include "Component.h"

BEGIN(Engine)

class CForestLand;

class ENGINE_DLL CCamera : public CComponent
{
private:
	explicit CCamera(void);
	virtual ~CCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Component(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp, CForestLand* _pTerrain);

private:
	POINT			m_tCenter = {};
	float			m_fAngleY = 0.f;
	float			m_fAngleX = 0.f;
	float			m_fAngleZ = 0.f;
	float			m_fCameraDis = 10.f;
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
