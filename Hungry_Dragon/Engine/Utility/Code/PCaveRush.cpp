#include "PCaveRush.h"
#include "Transform.h"
#include "CaveCamera.h"
#include "PlayerMain.h"
#include "Export_System.h"

USING(Engine)

Engine::CPCaveRush::CPCaveRush(void)
{
	
}

Engine::CPCaveRush::CPCaveRush(const CPCaveRush& rhs)
{

}

Engine::CPCaveRush::~CPCaveRush(void)
{

}

void CPCaveRush::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPCaveRush::Update_State(const float& fTimeDelta)
{
	switch (m_ePhase)
	{
	case Engine::CPCaveRush::PHASE_ZERO:
		Phase_0(fTimeDelta);
		break;
	case Engine::CPCaveRush::PHASE_ONE:
		Phase_1(fTimeDelta);
		break;
	case Engine::CPCaveRush::PHASE_TWO:
		Phase_0(fTimeDelta);
		break;
	}
}

void CPCaveRush::Out_State()
{
}

void CPCaveRush::Phase_0(const float & fTimeDelta)
{
	if (Engine::Get_DIKeyState(DIK_LSHIFT))
	{
		m_fAccle = 2.f*10.f;
	}
	else
		m_fAccle = 10.f;
	if (Engine::Get_DIKeyState(DIK_W))
	{
		m_fSpeed += m_fAccle*fTimeDelta;
	}
	else if (Engine::Get_DIKeyState(DIK_S))
	{
		m_fSpeed -= m_fAccle*fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_A))
	{
		m_fAngularSpeed += 10.f*fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_D))
	{
		m_fAngularSpeed -= 10.f*fTimeDelta;
	}

	m_fAngularSpeed *= 0.95f;
	m_fSpeed *= 0.7f;

	m_fAngle += m_fAngularSpeed*fTimeDelta;

	m_pPlayer->Get_Transform()->Add_Trans(&_vec3(0.f, 0.f, m_fSpeed));
	m_pPlayer->Get_Transform()->m_vInCamPos.x = 7 * cosf(m_fAngle + Pi*0.5f);
	m_pPlayer->Get_Transform()->m_vInCamPos.y = 7 * sinf(-m_fAngle - Pi*0.5f);
	m_pPlayer->Get_Transform()->m_vAngle.z = -m_fAngle;

	m_pPlayer->Get_Camera()->Set_AfterAngle(2, -m_fAngle);
}

void CPCaveRush::Phase_1(const float & fTimeDelta)
{
	if (Engine::Get_DIKeyState(DIK_LSHIFT))
	{
		m_fAccle = 2.f*10.f;
	}
	else
		m_fAccle = 10.f;
	if (Engine::Get_DIKeyState(DIK_W))
	{
		m_fUpSpeed += m_fAccle*fTimeDelta;
	}
	else if (Engine::Get_DIKeyState(DIK_S))
	{
		m_fUpSpeed -= m_fAccle*fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_A))
	{
		m_fSpeed -= m_fAccle*fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_D))
	{
		m_fSpeed += m_fAccle*fTimeDelta;
	}

	m_fSpeed *= 0.7f;
	m_fUpSpeed *= 0.7f;
	m_fPosZ += m_fSpeed;
	m_fPosY += m_fUpSpeed;

	if (m_fPosZ > 16.f)
		m_fPosZ = 16.f;
	if (m_fPosZ < -16.f)
		m_fPosZ = -16.f;
	if (m_fPosY > 9.f)
		m_fPosY = 9.f;
	if (m_fPosY < -9.f)
		m_fPosY = -9.f;

	m_pPlayer->Get_Transform()->m_vInCamPos.z = m_fPosZ;
	m_pPlayer->Get_Transform()->m_vInCamPos.y = m_fPosY;
	m_pPlayer->Get_Camera()->Set_AfterAngle(2, -m_fAngle);
	//m_pPlayer->Get_Transform()->Add_Trans(&_vec3(0.f, m_fUpSpeed, m_fSpeed));
}

void CPCaveRush::Switch_Phase(int _iPhase)
{
	m_ePhase = (PHASE)_iPhase;
	if (1 == _iPhase)
	{
		m_fAngle = 0.f;
		m_pPlayer->Get_Transform()->m_vAngle.z = -m_fAngle;
		m_fAngularSpeed = 0.f;
	}
	if (2 == _iPhase)
	{
		m_pPlayer->Get_Camera()->Set_AfterAngle(2, -m_fAngle);
	}
}

CPCaveRush* Engine::CPCaveRush::Create(void)
{
	return new CPCaveRush;
}

void Engine::CPCaveRush::Free(void)
{

}

CComponent* Engine::CPCaveRush::Clone(void)
{
	return new CPCaveRush(*this);
}