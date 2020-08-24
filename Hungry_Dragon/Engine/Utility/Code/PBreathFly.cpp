#include "PBreathFly.h"
#include "Transform.h"
#include "PlayerMain.h"
#include "Camera.h"
#include "Export_System.h"

USING(Engine)

Engine::CPBreathFly::CPBreathFly(void)
{

}

Engine::CPBreathFly::CPBreathFly(const CPBreathFly& rhs)
{

}

Engine::CPBreathFly::~CPBreathFly(void)
{

}

void CPBreathFly::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_pPlayer->Set_Breath(true);
	m_pPlayer->Set_Animation(ANI_BREATHFLY);
}

void CPBreathFly::Update_State(const float& fTimeDelta)
{
	if(GetAsyncKeyState('G') & 0x0001)
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
		return;
	}
	if (0 >= m_pPlayer->Get_Mana())
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
		return;
	}
	m_pPlayer->Add_Mana(-1);

	D3DXVECTOR3 vDir = { 0.f,0.f,0.f };
	D3DXVECTOR3 vLook = { 0.f,0.f,0.f };
	D3DXVECTOR3 vRight = { 0.f,0.f,0.f };

	//float fCos = cosf(m_pPlayer->Get_AngleX());

	//vLook.y = -sinf(m_pPlayer->Get_AngleX());
	//vLook.x = sinf(m_pPlayer->Get_AngleY())*fCos;
	//vLook.z = cosf(m_pPlayer->Get_AngleY())*fCos;


	//D3DXVec3Cross(&vRight, &_vec3(0.f,1.f,0.f), &vLook);
	//D3DXVec3Normalize(&vRight, &vRight);
	//D3DXVec3Normalize(&vLook, &vLook);

	D3DXMATRIX vRotZ;

	D3DXMATRIX vRotX, vRotY, vRotTotal;
	D3DXMatrixRotationX(&vRotX, m_pPlayer->Get_AngleX());
	D3DXMatrixRotationY(&vRotY, m_pPlayer->Get_AngleY());

	vRotTotal = vRotX*vRotY;
	D3DXVec3TransformNormal(&vLook, &_vec3(0.f, 0.f, 1.f), &vRotTotal);

	D3DXVec3Cross(&vRight, &m_pPlayer->Get_Up(), &vLook);

	bool bCheck = false;
	bool bShift = false;
	if (Engine::Get_DIKeyState(DIK_W))
	{
		vDir += vLook;
		bCheck = true;
	}
	else if (Engine::Get_DIKeyState(DIK_S))
	{
		vDir -= vLook;
		bCheck = true;
	}
	if (GetAsyncKeyState('A'))
	{
		vDir -= vRight;
		bCheck = true;
	}
	else if (GetAsyncKeyState('D'))
	{
		vDir += vRight;
		bCheck = true;
	}
	if (Engine::Get_DIKeyState(DIK_SPACE))
	{
		vDir += D3DXVECTOR3(0.f, 1.f, 0.f);
		bCheck = true;
	}
	if (GetAsyncKeyState(VK_SHIFT))
	{
		bShift = true;
	}
	//if (GetAsyncKeyState('Q'))
	//{
	//	m_pPlayer->Get_Camera()->Set_AngleZPlus(m_fAngleSpeed*0.4f);
	//	m_pPlayer->Get_Transform()->m_vAngle.z += m_fAngleSpeed*0.4f;
	//}
	//if (GetAsyncKeyState('E'))
	//{
	//	m_pPlayer->Get_Camera()->Set_AngleZPlus(-m_fAngleSpeed*0.4f);
	//	m_pPlayer->Get_Transform()->m_vAngle.z -= m_fAngleSpeed*0.4f;
	// 
	if (GetAsyncKeyState('E'))
	{
		m_pPlayer->Get_Transform()->m_vInCamPos = vDir*100.f;
	}
	if (bCheck)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		if (bShift)
		{
			vDir *= m_fBoostMulti;
			m_pPlayer->Set_Animation(ANI_FASTBREATH);
		}
		else
			m_pPlayer->Set_Animation(ANI_BREATHFLY);
		//속도적용
		vDir *= fTimeDelta*m_fSpeed;
		//가속
		m_vSpeed += vDir;
		//감쇠
		m_vSpeed *= m_fDamping;
		//실제 적용
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += m_vSpeed;
		//여기까지 가속시스템

		//float fAngleX = m_pPlayer->Get_AngleX();
		//if (abs(m_pPlayer->Get_Transform()->m_vAngle.x - fAngleX) < m_fAngleSpeed)
		//	m_pPlayer->Get_Transform()->m_vAngle.x = fAngleX;
		//else if (m_pPlayer->Get_Transform()->m_vAngle.x < fAngleX)
		//	m_pPlayer->Get_Transform()->m_vAngle.x += m_fAngleSpeed;
		//else
		//	m_pPlayer->Get_Transform()->m_vAngle.x -= m_fAngleSpeed;

		//float fAngleY = m_pPlayer->Get_AngleY();
		//if (abs(m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) < m_fAngleSpeed)
		//	m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
		//else if (m_pPlayer->Get_Transform()->m_vAngle.y < fAngleY)
		//	m_pPlayer->Get_Transform()->m_vAngle.y += m_fAngleSpeed;
		//else
		//	m_pPlayer->Get_Transform()->m_vAngle.y -= m_fAngleSpeed;

		//구버전
		float fDis = sqrtf(m_vSpeed.x*m_vSpeed.x + m_vSpeed.y*m_vSpeed.y + m_vSpeed.z*m_vSpeed.z);
		float fPlaneDis = sqrtf(m_vSpeed.x*m_vSpeed.x + m_vSpeed.z*m_vSpeed.z);
		float fAngleX = acosf(fPlaneDis / fDis);
		if (0 < m_vSpeed.y)
			fAngleX *= -1;
		//부드러운 이동 시작
		float fDeltaX = (fAngleX - m_pPlayer->Get_Transform()->m_vAngle.x)*0.1f;
		m_pPlayer->Get_Transform()->m_vAngle.x += fDeltaX;
		//if (abs(m_pPlayer->Get_Transform()->m_vAngle.x - fAngleX) < m_fAngleSpeed)
		//	m_pPlayer->Get_Transform()->m_vAngle.x = fAngleX;
		//else
		//{
		//	if ((m_pPlayer->Get_Transform()->m_vAngle.x - fAngleX) > 0)
		//		m_pPlayer->Get_Transform()->m_vAngle.x -= m_fAngleSpeed;
		//	else
		//		m_pPlayer->Get_Transform()->m_vAngle.x += m_fAngleSpeed;
		//}
		//끝

		//구버전
		if (0.f != fPlaneDis)
		{
			float fAngleY = acosf(m_vSpeed.z / fPlaneDis);
			if (0 > m_vSpeed.x)
			{
				fAngleY *= -1;
				fAngleY += D3DX_PI * 2;
			}
			//부드러운이동 시작
			float fDeltaY = (fAngleY - m_pPlayer->Get_Transform()->m_vAngle.y);

			//if (abs(fDeltaY) < m_fAngleSpeed)
			//	m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
			//else if (abs(fDeltaY) > (D3DX_PI*2- m_fAngleSpeed))
			//	m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;

			if (fDeltaY > 0.f)
			{
				if (fDeltaY < D3DX_PI)
					m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaY*m_fAngleDamping;
				else
					m_pPlayer->Get_Transform()->m_vAngle.y += (fDeltaY - D3DX_PI * 2)*m_fAngleDamping;
			}
			else
			{
				if (fDeltaY > -D3DX_PI)
					m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaY*m_fAngleDamping;
				else
					m_pPlayer->Get_Transform()->m_vAngle.y += (D3DX_PI * 2 + fDeltaY)*m_fAngleDamping;
			}
			if (m_pPlayer->Get_Transform()->m_vAngle.y < 0)
				m_pPlayer->Get_Transform()->m_vAngle.y += D3DX_PI * 2;
			if (m_pPlayer->Get_Transform()->m_vAngle.y > D3DX_PI * 2)
				m_pPlayer->Get_Transform()->m_vAngle.y -= D3DX_PI * 2;

			//if (abs(m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) < m_fAngleSpeed)
			//	m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
			//else if (abs(m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) > (D3DX_PI*2- m_fAngleSpeed))
			//	m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
			//else
			//{
			//	if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) > D3DX_PI)
			//		m_pPlayer->Get_Transform()->m_vAngle.y += m_fAngleSpeed;
			//	else if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) < -D3DX_PI)
			//		m_pPlayer->Get_Transform()->m_vAngle.y -= m_fAngleSpeed;
			//	else if ((m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY) > 0)
			//		m_pPlayer->Get_Transform()->m_vAngle.y -= m_fAngleSpeed;
			//	else
			//		m_pPlayer->Get_Transform()->m_vAngle.y += m_fAngleSpeed;
			//	if (m_pPlayer->Get_Transform()->m_vAngle.y < 0)
			//		m_pPlayer->Get_Transform()->m_vAngle.y += D3DX_PI *2;
			//	if (m_pPlayer->Get_Transform()->m_vAngle.y > D3DX_PI *2)
			//		m_pPlayer->Get_Transform()->m_vAngle.y -= D3DX_PI *2;
			//}
			//끝
		}
	}
	else
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_BREATHIDLE);
	}
	if (Land_Check())
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDRUSH);
}

void CPBreathFly::Out_State()
{
	m_pPlayer->Set_Breath(false);
}

CPBreathFly* Engine::CPBreathFly::Create(void)
{
	return new CPBreathFly;
}

void Engine::CPBreathFly::Free(void)
{
}

CComponent* Engine::CPBreathFly::Clone(void)
{
	return new CPBreathFly(*this);
}