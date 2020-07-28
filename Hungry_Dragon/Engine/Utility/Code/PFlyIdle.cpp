#include "PFlyIdle.h"
#include "Transform.h"
#include "PlayerMain.h"

USING(Engine)

Engine::CPFlyIdle::CPFlyIdle(void)
{
	
}

Engine::CPFlyIdle::CPFlyIdle(const CPFlyIdle& rhs)
{

}

Engine::CPFlyIdle::~CPFlyIdle(void)
{

}

void CPFlyIdle::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPFlyIdle::Update_State(const float& fTimeDelta)
{
	if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
	}
	m_pPlayer->Get_Transform()->m_vAngle.x = 0.f;
	m_pPlayer->Get_Transform()->Add_Trans(&_vec3(0.f, 0.1f*sinf(m_fAngle), 0.f));
	m_fAngle += 0.1f;
}

void CPFlyIdle::Out_State()
{
}

CPFlyIdle* Engine::CPFlyIdle::Create(void)
{
	return new CPFlyIdle;
}

void Engine::CPFlyIdle::Free(void)
{

}

CComponent* Engine::CPFlyIdle::Clone(void)
{
	return new CPFlyIdle(*this);
}