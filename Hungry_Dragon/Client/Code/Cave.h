#ifndef Cave_h__
#define Cave_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CCaveCylinder;
class CTransform;

END

USING(Engine)

class CCave : public Engine::CGameObject
{
private:
	explicit CCave(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCave(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual Engine::_int Update_Object(const Engine::_float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
public:
	void Set_Loop(bool _bLoop) { m_bLoop = _bLoop; }		// 루프끝내기
	void Set_Active(bool _bActive) { m_bActive = _bActive; }		// 업뎃
	void Set_Trans(_vec3& _vPos);
	float Get_EndPoint();

private:
	HRESULT		Add_Component(void);

private:
	Engine::CCaveCylinder*	m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTransform*		m_pTransformBeyond = nullptr;
	float					m_fForwardSpeed = 1.f;
	float					m_fUpdateTick = 0.f;
	bool					m_bLoop = true;
	bool					m_bActive = true;
	float					m_fCaveLength = 0.f;

public:
	static CCave*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // SkyBox_h__
