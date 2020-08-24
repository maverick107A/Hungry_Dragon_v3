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
	m_pPlayer->Set_Animation(ANI_IDLE);
	m_pPlayer->Set_FrameSpeed(1.f);
}

void CPLandIdle::Update_State(const float& fTimeDelta)
{
	if (m_pPlayer->Get_Stamina() < 300)
		m_pPlayer->Add_Stamina(2);
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
	m_pPlayer->Set_FrameSpeed(3.f);
}

void CPLandIdle::LateUpdate_State()
{
	float fHeight;
	_vec3 vNorm;

	Land_Check(&fHeight, &vNorm);

	m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y += (fHeight - m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y)*0.2f;
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