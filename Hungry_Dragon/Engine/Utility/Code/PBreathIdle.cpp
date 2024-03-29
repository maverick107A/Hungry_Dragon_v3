#include "PBreathIdle.h"
#include "Transform.h"
#include "PlayerMain.h"
#include "Export_Function.h"

USING(Engine)

Engine::CPBreathIdle::CPBreathIdle(void)
{
	
}

Engine::CPBreathIdle::CPBreathIdle(const CPBreathIdle& rhs)
{

}

Engine::CPBreathIdle::~CPBreathIdle(void)
{

}

void CPBreathIdle::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_pPlayer->Set_Breath(true);
	m_pPlayer->Set_Animation(ANI_BREATHIDLE);
	m_pPlayer->Set_FrameSpeed(1.f);
	Engine::Get_FMOD()->PlayLoop(L"long_breath");
}

void CPBreathIdle::Update_State(const float& fTimeDelta)
{
	if (m_pPlayer->Get_Stamina() < m_pPlayer->Get_MaxStamina() && m_pPlayer->Get_Exhaust() < 0.f)
		m_pPlayer->Add_Stamina(2);

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		Aim();
	}
	else
	{
		//�߽����
		if (abs(m_pPlayer->Get_Transform2()->m_vAngle.x) < 0.05f)
			m_pPlayer->Get_Transform2()->m_vAngle.x = 0.f;
		else if (m_pPlayer->Get_Transform2()->m_vAngle.x > 0.f)
			m_pPlayer->Get_Transform2()->m_vAngle.x -= 0.05f;
		else
			m_pPlayer->Get_Transform2()->m_vAngle.x += 0.05f;
		m_pPlayer->Get_Transform2()->m_vInCamPos.y += 0.1f*sinf(m_fAngle);
		m_fAngle += 0.1f;
	}

	if (GetAsyncKeyState('G') & 0x0001)
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLYIDLE);
		return;
	}
	if (0 >= m_pPlayer->Get_Mana())
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLYIDLE);
		return;
	}
	m_pPlayer->Add_Mana(-1);
	if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_BREATHFLY);
	}
	//if(abs(m_pPlayer->Get_Transform2()->m_vAngle.x) < 0.05f)
	//	m_pPlayer->Get_Transform2()->m_vAngle.x = 0.f;
	//else if (m_pPlayer->Get_Transform2()->m_vAngle.x > 0.f)
	//	m_pPlayer->Get_Transform2()->m_vAngle.x -= 0.05f;
	//else
	//	m_pPlayer->Get_Transform2()->m_vAngle.x += 0.05f;
	//m_pPlayer->Get_Transform2()->m_vInCamPos.y += 0.1f*sinf(m_fAngle);
	//m_fAngle += 0.1f;
}

void CPBreathIdle::Out_State()
{
	m_pPlayer->Set_Breath(false);
	m_pPlayer->Set_FrameSpeed(3.f);
	Engine::Get_FMOD()->StopLoop(L"long_breath");

}

CPBreathIdle* Engine::CPBreathIdle::Create(void)
{
	return new CPBreathIdle;
}

void Engine::CPBreathIdle::Free(void)
{

}

CComponent* Engine::CPBreathIdle::Clone(void)
{
	return new CPBreathIdle(*this);
}