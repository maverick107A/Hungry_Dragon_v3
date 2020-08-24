#include "EngineEventMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonsterMain.h"
#include "PlayerMain.h"

USING(Engine)

IMPLEMENT_SINGLETON(CEngineEventMgr)

Engine::CEngineEventMgr::CEngineEventMgr(void) 
{

}

Engine::CEngineEventMgr::~CEngineEventMgr(void)
{
	Free();
}

void Engine::CEngineEventMgr::Free(void)
{
	m_listEvents.clear();
}
