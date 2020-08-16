#ifndef CaveCamera_h__
#define CaveCamera_h__

#include "CameraMain.h"
BEGIN(Engine)

class CBaseLand;

class ENGINE_DLL CCaveCamera : public CCameraMain
{
	enum PHASE { PHASE_ZERO, PHASE_ONE, PHASE_TWO, PHASE_END };
private:
	explicit CCaveCamera(void);
	virtual ~CCaveCamera(void);

public:
	HRESULT			Ready_Camera(void);
	virtual _int	Update_Camera(const _float& _fTimeDelta, LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY, CBaseLand* _pTerrain);

private:
	void			Move_Camera(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);
	void			Move_Phase01(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);
	void			Move_Phase2(LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY);

public:
	void			Switch_Phase(int _iPhase);

private:
	PHASE			m_ePhase = PHASE_ZERO;

public:
	static CCaveCamera*		Create(void);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

};
END
#endif // CaveCamera_h__
