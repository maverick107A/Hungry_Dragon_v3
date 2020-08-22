#ifndef PlayerMain_h__
#define PlayerMain_h__

#include "GameObject.h"

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

class ENGINE_DLL CPlayerMain : public Engine::CGameObject
{
public:
	enum STATE { STATE_FLYIDLE, STATE_FLY, STATE_LANDIDLE, STATE_LANDRUSH, STATE_BREATHIDLE, STATE_BREATHFLY, STATE_END };
	enum PARTS { PART_FACE, PART_JAW, PART_BODY, PART_2BODY, PART_3BODY, PART_WING, PART_LWING, PARTS_END};

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
	int						Get_Stamina() { return m_iStamina; }
	int						Get_Mana() { return m_iMana; }
	float					Get_ColSize() { return m_fColSize; }
	bool					Get_Breath() { return m_bBreath; }
	bool					Get_AccelCheck() { return m_bAccelCheck; }
	CTransform*				Get_Transform() { return m_pTransform; }
	CAnimationTransform*	Get_PartsTrans(int _i) { return m_pPartsTrans[_i]; }
	const D3DXVECTOR3&		Get_Look() { return m_vLook; }
	const D3DXVECTOR3&		Get_Up() { return m_vUp; }
	const float&			Get_AngleX() { return m_fAngleX; }
	const float&			Get_AngleY() { return m_fAngleY; }
	CBaseLand*				Get_Terrain() { return m_pTerrain; }
	CCameraMain*			Get_Camera() { return m_pCamera; }

	ANIMATION				m_eAnimation = ANI_IDLE;

public:
	void Set_Sate(STATE _eState) { m_eState = _eState; }
	void Set_Breath(bool _bCheck) { m_bBreath = _bCheck; }
	void Set_MouseTime(float _fTime) { m_fMouseTime = _fTime; }
	void Set_AccelCheck(bool _bCheck) { m_bAccelCheck = _bCheck; }
	void Set_Animation(ANIMATION _eAni) { m_eAnimation = _eAni; }

public:
	void Add_Hp(int _iHp) { m_iHp += _iHp; }
	void Add_Stamina(int _iStamina) { m_iStamina += _iStamina; }
	void Add_Mana(int _iMana) { m_iMana += _iMana; }

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
	float					m_fAngleX = 0.f;
	float					m_fAngleY = 0.f;
	bool					m_bAccelCheck = false;
	bool					m_bLand = false;
	bool					m_bShift = false;
	bool					m_bBreath = false;
	float					m_fMouseTime = 0.f;
	float					m_fSpeed = 10.f;
	STATE					m_eState = STATE_END;

	int						m_iHp = 300;
	int						m_iStamina = 1000;
	int						m_iMana = 300;

	float					m_fColSize = 0.f;

public:
	D3DXVECTOR3				m_vNorm = { 0.f,1.f,0.f };

public:
	static CPlayerMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
protected:
	virtual void Free(void) override;


};

END
#endif // PlayerMain_h__
