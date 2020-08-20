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
	if (GetAsyncKeyState('G') & 0x0001 && 0 < m_pPlayer->Get_Mana())
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_BREATHIDLE);
		return;
	}
	if(m_pPlayer->Get_Mana() < 300)
		m_pPlayer->Add_Mana(1);
	if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
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
		//�߽����
		if (abs(m_pPlayer->Get_Transform()->m_vAngle.x) < 0.05f)
			m_pPlayer->Get_Transform()->m_vAngle.x = 0.f;
		else if (m_pPlayer->Get_Transform()->m_vAngle.x > 0.f)
			m_pPlayer->Get_Transform()->m_vAngle.x -= 0.05f;
		else
			m_pPlayer->Get_Transform()->m_vAngle.x += 0.05f;
		m_pPlayer->Get_Transform()->m_vInCamPos.y += 0.1f*sinf(m_fAngle);
		m_fAngle += 0.1f;
	}
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