#ifndef Meteor_Spawner_h__
#define Meteor_Spawner_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CBaseLand;

END

class CMeteor_Object;
class CMeteor_Circular;
class CMeteor_Linear;

USING(Engine)

class CMeteor_Spawner : public Engine::CGameObject
{
private:
	explicit CMeteor_Spawner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor_Spawner(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void Spawn_Meteor();
	void Fire_Meteor();

public:
	void Instantiate_Meteor(_vec3& vPos);
	void Instantiate_CircularMeteor(_vec3 _vRadius, _vec3 _vCenter, _vec3 _vAxis, float _fSpeed, float _fAngle);	// 수선의발(반지름), 중심, 축, 회전속도, 생성 위치 
	void Instantiate_LinearMeteor(_vec3 _vRadius, _vec3 _vSrc, _vec3 _vDest, float _fLimit, float _fAngle);	// 공격 크기(충돌포함), 생성 위치, 목표 위치, 지속시간, 회전각


private:
	HRESULT		Add_Component(void);
	

private:
	Engine::CTransform*		m_pTransform;
	Engine::CTransform*		m_pPlayerTrans = nullptr;
	vector<CMeteor_Object*>	m_vecObjectPool;
	vector<CMeteor_Object*>::iterator	m_iterFinder;		// 순회자
	CMeteor_Object*			m_pMeteor;
	_bool					m_bActive = true;
	_float					m_fSummonTick = 0.f;
	_float					m_fSummonTime = 0.25f;

	_float					m_fFireTick = 0.f;
	_float					m_fFireTime = 1.f;


	vector<CMeteor_Circular*>	m_vecCircularPool;
	vector<CMeteor_Circular*>::iterator	m_iterCircular;		// 순회자
	CMeteor_Circular*		m_pCircular;

	list<CMeteor_Linear*>	m_listLinearPool;
	CMeteor_Linear*			m_pLinear;


public:
	static CMeteor_Spawner*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
