#include "PLandIdle.h"
#include "Transform.h"
#include "PlayerMain.h"

USING(Engine)

Engine::CPLandIdle::CPLandIdle(void)
{
	
}

Engine::CPLandIdle::CPLandIdle(const CPLandIdle& rhs)
{

}

Engine::CPLandIdle::~CPLandIdle(void)
{

}

void CPLandIdle::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPLandIdle::Update_State(const float& fTimeDelta)
{
	if (GetAsyncKeyState('W') || GetAsyncKeyState('S'))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDRUSH);
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
	}
}

void CPLandIdle::Out_State()
{
}

CPLandIdle* Engine::CPLandIdle::Create(void)
{
	return new CPLandIdle;
}

void Engine::CPLandIdle::Free(void)
{

}

CComponent* Engine::CPLandIdle::Clone(void)
{
	return new CPLandIdle(*this);
}