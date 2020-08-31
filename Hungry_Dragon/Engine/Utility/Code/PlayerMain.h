#ifndef PlayerMain_h__
#define PlayerMain_h__

#include "GameObject.h"
#include "Animation_Controller.h"

class CTerrain_Locater;

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTransform;
class CAnimationTransform;
class CCameraMain;
class CBaseLand;
class CPlayerState;
class CBreathBase;
class CMonsterMain;
class CAnimation_Controller;

class ENGINE_DLL CPlayerMain : public Engine::CGameObject
{
public:
	enum STATE { STATE_FLYIDLE, STATE_FLY, STATE_LANDIDLE, STATE_LANDRUSH, STATE_BREATHIDLE, STATE_BREATHFLY, STATE_HIT, STATE_END };
	enum PARTS { PART_FACE, PART_JAW, PART_BODY, PART_2BODY, PART_3BODY, PART_4BODY, PART_5BODY, PART_6BODY, PART_7BODY, PART_WING, PART_LWING, PARTS_END};

protected:
	explicit CPlayerMain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerMain(void);

public:
	virtual HRESULT Ready_Object(void) { return 0; }
	virtual void Initialize_Object(void) { return; }
	virtual int Update_Object(const float& fTimeDelta) { return 0; }
	virtual void LateUpdate_Object(const _float& fTimeDelta) {};
	virtual void Render_Object(void) {}

public:
	int						Get_Hp() { return m_iHp; }
	int						Get_MaxHp() { return m_iMaxHp; }
	int						Get_Stamina() { return m_iStamina; }
	int						Get_MaxStamina() { return m_iMaxStamina; }
	int						Get_Mana() { return m_iMana; }
	int						Get_MaxMana() { return m_iMaxMana; }
	int						Get_BreathRad() { return m_iBreathRad; }
	float					Get_ColSize() { return m_fColSize; }
	float					Get_Speed() { return m_fSpeed; }
	float					Get_Exhaust() { return m_fExhaust; }
	bool					Get_Breath() { return m_bBreath; }
	bool					Get_AccelCheck() { return m_bAccelCheck; }
	bool					Get_LockOn() { return m_bLock; }
	CTransform*				Get_Transform() { return m_pTransform; }
	CAnimationTransform*	Get_PartsTrans(int _i) { return m_pPartsTrans[_i]; }
	const D3DXVECTOR3&		Get_Look() { return m_vLook; }
	const D3DXVECTOR3&		Get_Up() { return m_vUp; }
	const D3DXVECTOR3&		Get_Right() { return m_vRight; }
	const float&			Get_AngleX() { return m_fAngleX; }
	const float&			Get_AngleY() { return m_fAngleY; }
	CBaseLand*				Get_Terrain() { return m_pTerrain; }
	CCameraMain*			Get_Camera() { return m_pCamera; }
	CMonsterMain*			Get_Boss() { return m_pBoss; }
	_vec3					Get_Lwing() { return m_vLWingPos; }
	_vec3					Get_RWing() { return m_vRWingPos; }
	_vec3					Get_HitDir() { return m_vHitDir; }
	STATE					Get_State() { return m_eState; }


	ANIMATION				m_eAnimation = ANI_IDLE;

public:
	void Set_Sate(STATE _eState) { m_eState = _eState; }
	void Set_Breath(bool _bCheck) { m_bBreath = _bCheck; }
	void Set_BreathRad(int _iRad) { m_iBreathRad = _iRad; }
	void Set_MouseTime(float _fTime) { m_fMouseTime = _fTime; }
	void Set_AccelCheck(bool _bCheck) { m_bAccelCheck = _bCheck; }
	void Set_Animation(ANIMATION _eAni) { m_eAnimation = _eAni; }
	void Set_Right(_vec3 _vRight) { m_vRight = _vRight; }
	void Set_HitDir(_vec3 _vDir) { m_vHitDir = _vDir; }
	void Set_FrameSpeed(float _fSpeed) { m_pAnimationController->Set_FrameSpeed(_fSpeed); }
	void Set_PlusSpeed(float _fSpeed);
	void Set_Exhaust(float _fTime) { m_fExhaust = _fTime; }

public:
	void Add_Hp(int _iHp) { m_iHp += _iHp; }
	void Add_Stamina(int _iStamina) { m_iStamina += _iStamina; if (m_iStamina > m_iMaxStamina-1)m_iStamina = m_iMaxMana-1; }
	void Add_Mana(int _iMana) { m_iMana += _iMana; }
	void Add_BreathRad(int _iRad) { m_iBreathRad += _iRad; }

protected:
	virtual void State_Change() {};
	virtual HRESULT	Add_Component(void) { return 0; }

protected:
	CVIBuffer*				m_pPartsBuffer[PARTS_END];
	CAnimationTransform*	m_pPartsTrans[PARTS_END];
	CCameraMain*			m_pCamera = nullptr;
	CTerrain_Locater*		m_pTerrrrrrrain = nullptr;
	CBaseLand*				m_pTerrain = nullptr;
	CPlayerState*			m_pState = nullptr;
	CBreathBase*			m_pBreath = nullptr;
	D3DXVECTOR3				m_vLook;
	D3DXVECTOR3				m_vUp;
	D3DXVECTOR3				m_vRight;
	float					m_fAngleX = 0.f;
	float					m_fAngleY = 0.f;
	float					m_vAngle = 0.f;
	float					m_fMSpeed = 0.1f;
	float					m_fBaseSpeed = 40.f;
	float					m_fPlusSpeed = 0.f;
	float					m_fSpeed = 0.f;
	float					m_fExhaust = 0.f;
	bool					m_bAccelCheck = false;
	bool					m_bLand = false;
	bool					m_bShift = false;
	bool					m_bBreath = false;
	bool					m_bLock = false;
	float					m_fMouseTime = 0.f;
	STATE					m_eState = STATE_END;

	int						m_iHp = 100;
	int						m_iMaxHp = 100;
	int						m_iStamina = 100;
	int						m_iMaxStamina = 100;
	int						m_iMana = 100;
	int						m_iMaxMana = 100;


	float					m_fColSize = 0.f;
	CMonsterMain*			m_pBoss = nullptr;

	D3DXMATRIX				m_matOld1;
	D3DXMATRIX				m_matOld2;
	D3DXMATRIX				m_matOld3;
	D3DXMATRIX				m_matOld4;
	D3DXMATRIX				m_matOld5;
	D3DXMATRIX				m_matOld6;
	D3DXMATRIX				m_matOld7;

	Engine::CAnimation_Controller* m_pAnimationController;

	_vec3					m_vRWingPos;
	_vec3					m_vRMWingPos;
	_vec3					m_vLWingPos;
	_vec3					m_vLMWingPos;
	_vec3					m_vHitDir;

	int						m_iBreathRad = 10;
public:
	D3DXVECTOR3				m_vNorm = { 0.f,1.f,0.f };

public:
	static CPlayerMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
protected:
	virtual void Free(void) override;


};

END
#endif // PlayerMain_h__
