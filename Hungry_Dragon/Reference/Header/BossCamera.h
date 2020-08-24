#ifndef BossCamera_h__
#define BossCamera_h__

#include "CameraMain.h"
BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CBossCamera : public CCameraMain
{
	enum PHASE { PHASE_ZERO, PHASE_ONE, PHASE_END };
private:
	explicit CBossCamera(void);
	virtual ~CBossCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Camera(const _float& _fTimeDelta, float* _fAngleX, float* _fAngleY, _vec3* _vLook, _vec3* _vUp, CPlayerMain* _pPlayer);

private:
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);
	void			Move_Phase01(float* _fAngleX, float* _fAngleY, _vec3 * _vLook, _vec3 * _vUp);
	void			Move_Phase2(float* _fAngleX, float* _fAngleY, _vec3 * _vLook, _vec3 * _vUp, CPlayerMain* _pPlayer);

public:
	void			Switch_Phase(int _iPhase);

private:
	PHASE			m_ePhase = PHASE_ZERO;

public:
	static CBossCamera*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // BossCamera_h__
