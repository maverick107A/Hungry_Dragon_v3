#ifndef PlayerMain_h__
#define PlayerMain_h__

#include "GameObject.h"

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTransform;
class CCamera;
class CForestLand;
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
	virtual int Update_Object(const float& fTimeDelta) { return 0; }
	virtual void Render_Object(void) {}

public:
	void Set_Sate(STATE _eState) { m_eState = _eState; }

public:
	CTransform* Get_Transform() { return m_pTransform; }
	const D3DXVECTOR3&			Get_Look() { return m_vLook; }
	CForestLand*	Get_Terrain() { return m_pTerrain; }

protected:
	virtual void State_Change() {};
	virtual HRESULT	Add_Component(void) { return 0; }

protected:
	CVIBuffer*				m_pBufferCom = nullptr;
	CTransform*				m_pTransform = nullptr;
	CCamera*				m_pCamera = nullptr;
	CForestLand*				m_pTerrain = nullptr;
	CPlayerState*			m_pState = nullptr;
	D3DXVECTOR3				m_vLook;
	D3DXVECTOR3				m_vUp;
	bool					m_bLand = false;
	bool					m_bShift = false;
	float					m_fSpeed = 10.f;
	STATE					m_eState = STATE_END;

public:
	static CPlayerMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
protected:
	virtual void Free(void) override;


};

END
#endif // PlayerMain_h__
