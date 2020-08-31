#ifndef Vent_h__
#define Vent_h__

#include "Define.h"
#include "GameObject.h"
#include "Obstacle.h"

BEGIN(Engine)

class CVentCube;
class CTransform;
class CTexture;
class CPlayerMain;

END

USING(Engine)

class CVent : public Engine::CGameObject
{
private:
	explicit CVent(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CVent(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object(void);
	virtual Engine::_int Update_Object(const Engine::_float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
public:
	void Set_ObsLoop(bool _bLoop) { m_bLoop = _bLoop; }
	void Set_Loop(bool _bLoop) { m_bVentLoop = _bLoop; }
	void Set_Active(bool _bActive) { m_bActive = _bActive; }		// 업뎃
	void Set_Trans(_vec3& _vPos);
	void Set_Speed(float _fSpeed) { m_fForwardSpeed = _fSpeed; }
	float Get_EndPoint();

public:
	void Ready_Obstacles();
	void Release_Obstacles();

	void Instantiate_Obstacle(_vec3& vPos, _float fRotX, _float fRotY);
	void Deactivate_Obstacle();


private:
	HRESULT		Add_Component(void);

private:
	Engine::CVentCube*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTransform*		m_pTransformBeyond = nullptr;
	Engine::CTransform*		m_pPlayerTrans = nullptr;
	Engine::CTexture*		m_pTex = nullptr;
	Engine::CTexture*		m_pObsTex = nullptr;
	Engine::CPlayerMain*	m_pPlayer = nullptr;
	float					m_fForwardSpeed = 1.f;
	float					m_fUpdateTick = 0.f;
	bool					m_bLoop = true;
	bool					m_bVentLoop = true;
	bool					m_bActive = true;
	float					m_fCaveLength = 0.f;

	// 간단한 오브젝트 풀링
	vector<CObstacle*>				m_vecObs;
	vector<CObstacle*>::iterator	m_iterHead;		// 맨 앞 활성자
	vector<CObstacle*>::iterator	m_iterTail;		// 맨 앞 비활성자
	list<CObstacle*>				m_listActiveObs;
	CObstacle*						m_pObs;
	_bool							m_bFull = false;
	_float							m_fSummonTick = 0.f;
	_float							m_fSummonTime = 1.f;
	_uint							m_uDelayDeactNum = 0;
public:
	static CVent*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // SkyBox_h__
