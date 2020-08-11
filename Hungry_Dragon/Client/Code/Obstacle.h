#ifndef Obstacle_h__
#define Obstacle_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CObstacleCube;
class CTransform;
class CTexture;

END

USING(Engine)

class CObstacle : public Engine::CGameObject
{
private:
	explicit CObstacle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CObstacle(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual Engine::_int Update_Object(const Engine::_float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
public:
	void Set_Active(bool _bActive) { m_bActive = _bActive; }		// ¾÷µ«
	void Set_Trans(_vec3& _vPos);
	void Set_RotationX(float _fAngleX);
	void Set_RotationY(float _fAngleY);
	void Set_Speed(float _fSpeed) { m_fForwardSpeed = _fSpeed; }

private:
	HRESULT		Add_Component(void);

private:
	Engine::CObstacleCube*		m_pBufferCom = nullptr;
	//Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTexture*		m_pTex = nullptr;
	float					m_fForwardSpeed = 1.f;
	float					m_fUpdateTick = 0.f;
	bool					m_bActive = true;


public:
	static CObstacle*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // SkyBox_h__
