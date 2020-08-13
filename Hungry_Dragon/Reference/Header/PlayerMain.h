#ifndef PlayerMain_h__
#define PlayerMain_h__

#include "GameObject.h"

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTransform;
class CCameraMain;
class CBaseLand;
class CPlayerState;

class ENGINE_DLL CPlayerMain : public Engine::CGameObject
{
public:
	enum STATE { STATE_FLYIDLE, STATE_FLY, STATE_LANDIDLE, STATE_LANDRUSH, STATE_END };

protected:
	explicit CPlayerMain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerMain(void);

public:
	virtual HRESULT Ready_Object(void) { return 0; }
	virtual void Initialize_Object(void) { return; }
	virtual int Update_Object(const float& fTimeDelta) { return 0; }
	virtual void Render_Object(void) {}

public:
	int Get_Hp() { return m_iHp; }
	int	Get_Stamina() { return m_iStamina; }

public:
	void Set_Sate(STATE _eState) { m_eState = _eState; }

public:
	void Add_Hp(int _iHp) { m_iHp += _iHp; }

public:
	CTransform* Get_Transform() { return m_pTransform; }
	//const D3DXVECTOR3&			Get_Look() { return m_vLook; }
	//const D3DXVECTOR3&			Get_Up() { return m_vUp; }
	const float&			Get_AngleX() { return m_fAngleX; }
	const float&			Get_AngleY() { return m_fAngleY; }
	CBaseLand*	Get_Terrain() { return m_pTerrain; }
	CCameraMain*	Get_Camera() { return m_pCamera; }

protected:
	virtual void State_Change() {};
	virtual HRESULT	Add_Component(void) { return 0; }

protected:
	CVIBuffer*				m_pBufferCom = nullptr;
	CCameraMain*			m_pCamera = nullptr;
	CBaseLand*				m_pTerrain = nullptr;
	CPlayerState*			m_pState = nullptr;
	//D3DXVECTOR3				m_vLook;
	//D3DXVECTOR3				m_vUp;
	float					m_fAngleX = 0.f;
	float					m_fAngleY = 0.f;
	bool					m_bLand = false;
	bool					m_bShift = false;
	float					m_fSpeed = 10.f;
	STATE					m_eState = STATE_END;

	int						m_iHp = 100;
	int						m_iStamina = 100;

public:
	static CPlayerMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
protected:
	virtual void Free(void) override;


};

END
#endif // PlayerMain_h__
