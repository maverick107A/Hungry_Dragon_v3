#ifndef Camera_h__
#define Camera_h__

#include "CameraMain.h"

BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CCamera : public CCameraMain
{
private:
	explicit CCamera(void);
	virtual ~CCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Camera(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY, CBaseLand* _pTerrain);
	virtual _int	Update_Camera(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp, CBaseLand* _pTerrain);
	virtual _int	Update_CameraMFC(LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp);

private:
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _vUp);
	void			Move_Camera_InMFC(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up);

public:
	static CCamera*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // Camera_h__
