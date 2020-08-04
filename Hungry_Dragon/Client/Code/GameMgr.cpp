#include "stdafx.h"
#include "GameMgr.h"
#include "Export_Utility.h"
#include "Transform.h"


USING(Engine)

IMPLEMENT_SINGLETON(CGameMgr)



CGameMgr::CGameMgr(void)
{
}


CGameMgr::~CGameMgr(void)
{
}

void CGameMgr::Game_Update(D3DXVECTOR3 _vPlayerPos)
{
	Engine::Set_Monster_LayerMap(OBJID::STAND_MONSTER, 9999 , _vPlayerPos);
}
