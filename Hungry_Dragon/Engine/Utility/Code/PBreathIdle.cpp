#include "PBreathIdle.h"
#include "Transform.h"
#include "PlayerMain.h"

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
}

void CPBreathIdle::Update_State(const float& fTimeDelta)
{
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

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		float fDeltaAngleX = (m_pPlayer->Get_AngleX() - m_pPlayer->Get_Transform()->m_vAngle.x)*0.25f;
		float fDeltaAngleY = (m_pPlayer->Get_AngleY() - m_pPlayer->Get_Transform()->m_vAngle.y)*0.25f;

		m_pPlayer->Get_Transform()->m_vAngle.x += fDeltaAngleX;
		m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaAngleY;
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

	//if(abs(m_pPlayer->Get_Transform()->m_vAngle.x) < 0.05f)
	//	m_pPlayer->Get_Transform()->m_vAngle.x = 0.f;
	//else if (m_pPlayer->Get_Transform()->m_vAngle.x > 0.f)
	//	m_pPlayer->Get_Transform()->m_vAngle.x -= 0.05f;
	//else
	//	m_pPlayer->Get_Transform()->m_vAngle.x += 0.05f;
	//m_pPlayer->Get_Transform()->m_vInCamPos.y += 0.1f*sinf(m_fAngle);
	//m_fAngle += 0.1f;
}

void CPBreathIdle::Out_State()
{
	m_pPlayer->Set_Breath(false);
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