#ifndef Ingame_Info_h__
#define Ingame_Info_h__

#include "Define.h"
#include "Engine_Define.h"
#include "Transform.h"

class CIngame_Info
{
	DECLARE_SINGLETON(CIngame_Info)
public:
	enum STAGEID { STAGE_FOREST , STAGE_CAVE_ONE, STAGE_CAVE_TWO, STAGE_CAVE_FINAL, STAGE_SKY , STAGE_LAVA , STAGE_END };

private:
	explicit CIngame_Info(void);
	explicit CIngame_Info(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIngame_Info(void);

public:			
	void Init_Info(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	Engine::STATUS * Get_PlayerInfo() { return &m_pPlayerStatus; }
	Engine::GOODS * Get_PlayerGoods() { return &m_pPlayerGoods; }

private:
	// ����� �۵��.
	LPDIRECT3DDEVICE9						m_pGraphicDev;
private:
	Engine::STATUS 						m_pPlayerStatus;
	Engine::GOODS 							m_pPlayerGoods;
};


#endif // GameMgr_h__
