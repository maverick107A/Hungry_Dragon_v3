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
		vDir *= fTimeDelta*m_fSpeed;;
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += vDir;
		float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
		float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
		float fAngleX = acosf(fPlaneDis / fDis);
		if (0 < vDir.y)
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
			float fAngleY = acosf(vDir.z / fPlaneDis);
			if (0 > vDir.x) // 각도의 범위는 -Pi to Pi
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