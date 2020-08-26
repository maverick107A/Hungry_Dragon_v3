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
	m_pPlayer->Set_Animation(ANI_IDLE);
	m_pPlayer->Set_FrameSpeed(1.f);
}

void CPFlyIdle::Update_State(const float& fTimeDelta)
{
	if(m_pPlayer->Get_Mana() < m_pPlayer->Get_MaxMana())
		m_pPlayer->Add_Mana(1);
	if (m_pPlayer->Get_Stamina() < m_pPlayer->Get_MaxStamina())
		m_pPlayer->Add_Stamina(2);
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		Aim();
	}
	else
	{
		//중심잡기
		if (abs(m_pPlayer->Get_Transform()->m_vAngle.x) < 0.05f)
			m_pPlayer->Get_Transform()->m_vAngle.x = 0.f;
		else if (m_pPlayer->Get_Transform()->m_vAngle.x > 0.f)
			m_pPlayer->Get_Transform()->m_vAngle.x -= 0.05f;
		else
			m_pPlayer->Get_Transform()->m_vAngle.x += 0.05f;
		m_pPlayer->Get_Transform()->m_vInCamPos.y += 0.1f*sinf(m_fAngle);
		m_fAngle += 0.1f;
	}
	if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
	}
	if (GetAsyncKeyState('G') & 0x0001 && 0 < m_pPlayer->Get_Mana())
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_BREATHIDLE);
		return;
	}
}

void CPFlyIdle::Out_State()
{
	m_pPlayer->Set_FrameSpeed(3.f);
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