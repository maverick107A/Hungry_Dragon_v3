#ifndef Boss_Flow_h__
#define Boss_Flow_h__

#include "Define.h"
#include "Engine_Define.h"
#include "GiantGolem.h"

USING(Engine)

class CBoss_Flow
{
	DECLARE_SINGLETON(CBoss_Flow)
public:
	enum EVENTID{EVENT_SCENECHANGE, EVENT_END};
	enum PHASEID { PHASE_1 , PHASE_2, PHASE_3, PHASE_4, PHASE_END };

private:
	explicit CBoss_Flow(void);
	virtual ~CBoss_Flow(void);
	

public:
	void Ready_Boss_Flow(LPDIRECT3DDEVICE9 pGraphicDev, CGiantGolem* _pBoss);
public:
	void Set_Phase(PHASEID _eID) { m_uPhaseNum = _eID; }
public:
	void	Update_BossFlow(float _fTimeDelta);
	void	Render_Sfx();

private:
	CGiantGolem*	m_pBoss = nullptr;
	CTransform*		m_pPlayerTransform = nullptr;
	_bool			m_bBossPause = false;
	PHASEID			m_uPhaseNum = PHASE_1;
	

private:
	// 출력할 글디바.
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	LPD3DXSPRITE					m_pSprite;

};


#endif // GameMgr_h__
