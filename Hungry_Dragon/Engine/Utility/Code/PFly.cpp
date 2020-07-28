#include "PFly.h"
#include "Transform.h"
#include "PlayerMain.h"

USING(Engine)

Engine::CPFly::CPFly(void)
{
	
}

Engine::CPFly::CPFly(const CPFly& rhs)
{

}

Engine::CPFly::~CPFly(void)
{

}

void CPFly::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPFly::Update_State(const float& fTimeDelta)
{
	D3DXVECTOR3 vDir = { 0.f,0.f,0.f };
	D3DXVECTOR3 vRight = { 0.f,0.f,0.f };
	D3DXVec3Cross(&vRight, &m_pPlayer->Get_Up(), &m_pPlayer->Get_Look());
	bool bCheck = false;
	bool bShift = false;
	if (GetAsyncKeyState('W'))
	{
		vDir += m_pPlayer->Get_Look();
		bCheck = true;
	}
	else if (GetAsyncKeyState('S'))
	{
		vDir -= m_pPlayer->Get_Look();
		bCheck = true;
	}
	else if (GetAsyncKeyState('A'))
	{
		vDir -= vRight;
		bCheck = true;
	}
	else if (GetAsyncKeyState('D'))
	{
		vDir += vRight;
		bCheck = true;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		vDir += D3DXVECTOR3(0.f, 1.f, 0.f);
		bCheck = true;
	}
	if (GetAsyncKeyState(VK_SHIFT))
	{
		bShift = true;
	}
	if (bCheck)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		if (bShift)
		{
			vDir *= 100.f;
		}
		vDir *= fTimeDelta*0.3f;
		m_vSpeed += vDir;
		float fLength = D3DXVec3Length(&m_vSpeed);
		if (50.f < fLength)
			m_vSpeed *= 50.f/fLength;
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += m_vSpeed;
		//여기까지 가속시스템

		float fDis = sqrtf(m_vSpeed.x*m_vSpeed.x + m_vSpeed.y*m_vSpeed.y + m_vSpeed.z*m_vSpeed.z);
		float fPlaneDis = sqrtf(m_vSpeed.x*m_vSpeed.x + m_vSpeed.z*m_vSpeed.z);
		float fAngleX = acosf(fPlaneDis / fDis);
		if (0 < m_vSpeed.y)
			fAngleX *= -1;
		if (abs(m_pPlayer->Get_Transform()->m_vAngle.x - fAngleX) < m_fAngleSpeed)
			m_pPlayer->Get_Transform()->m_vAngle.x = fAngleX;
		else
		{
			if ((m_pPlayer->Get_Transform()->m_vAngle.x - fAngleX) > 0)
				m_pPlayer->Get_Transform()->m_vAngle.x -= m_fAngleSpeed;
			else
				m_pPlayer->Get_Transform()->m_vAngle.x += m_fAngleSpeed;
		}
		//m_pPlayer->Get_Transform()->m_vAngle.x = fAngleX;
		//m_pTransform->m_vAngle.x = m_pCamera->m_fAngleX;
		if (0.f != fPlaneDis)
		{
			float fAngleY = acosf(m_vSpeed.z / fPlaneDis);
			if (0 > m_vSpeed.x) // 각도의 범위는 -Pi to Pi
			{
				fAngleY *= -1;
				fAngleY += Pi*2;
			}
			if (abs(m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) < m_fAngleSpeed)
				m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
			else
			{
				//여기 하고있음
				if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) > Pi)
					m_pPlayer->Get_Transform()->m_vAngle.y += m_fAngleSpeed;
				else if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) < -Pi)
					m_pPlayer->Get_Transform()->m_vAngle.y -= m_fAngleSpeed;

				else if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) > 0)
					m_pPlayer->Get_Transform()->m_vAngle.y -= m_fAngleSpeed;
				else
					m_pPlayer->Get_Transform()->m_vAngle.y += m_fAngleSpeed;

				if (m_pPlayer->Get_Transform()->m_vAngle.y < 0)
					m_pPlayer->Get_Transform()->m_vAngle.y += Pi*2;
				if (m_pPlayer->Get_Transform()->m_vAngle.y > Pi*2)
					m_pPlayer->Get_Transform()->m_vAngle.y -= Pi*2;
			}
		}
		//D3DXVECTOR3 vMoveDir = { 0.f,0.f,1.f };
		//D3DXMATRIX MatRotX, MatRotY, MatTotal;
		//D3DXMatrixRotationX(&MatRotX, m_pPlayer->Get_Transform()->m_vAngle.x);
		//D3DXMatrixRotationY(&MatRotY, m_pPlayer->Get_Transform()->m_vAngle.y);
		//MatTotal = MatRotY*MatRotX;

		//D3DXVec3TransformNormal(&vMoveDir, &vMoveDir, &MatTotal);
		//m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += vMoveDir;

	}
	else
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLYIDLE);
	}
	//아무 쓸모없는 변수
	float fTemp;
	if (Land_Check(&fTemp))
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDRUSH);
}

void CPFly::Out_State()
{
	//m_pTransform->Add_Trans()
}

CPFly* Engine::CPFly::Create(void)
{
	return new CPFly;
}

void Engine::CPFly::Free(void)
{
}

CComponent* Engine::CPFly::Clone(void)
{
	return new CPFly(*this);
}