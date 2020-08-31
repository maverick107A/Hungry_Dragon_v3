#include "PLandRush.h"
#include "Transform.h"
#include "PlayerMain.h"

USING(Engine)

Engine::CPLandRush::CPLandRush(void)
{
	
}

Engine::CPLandRush::CPLandRush(const CPLandRush& rhs)
{

}

Engine::CPLandRush::~CPLandRush(void)
{

}

void CPLandRush::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_pPlayer->Set_Animation(ANI_FLY);
}

void CPLandRush::Update_State(const float& fTimeDelta)
{
	if (m_pPlayer->Get_Mana() < m_pPlayer->Get_MaxMana())
		m_pPlayer->Add_Mana(1);
	//땅이동
	D3DXVECTOR3 vDir = { 0.f,0.f,0.f };
	D3DXVECTOR3 vLook = { 0.f,0.f,0.f };
	D3DXVECTOR3 vRight = { 0.f,0.f,0.f };

	vLook.y = -sinf(m_pPlayer->Get_AngleX());
	vLook.x = sinf(m_pPlayer->Get_AngleY());
	vLook.z = cosf(m_pPlayer->Get_AngleY());

	vLook.y = 0.f;
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Cross(&vRight, &_vec3(0.f, 1.f, 0.f),&vLook);

	bool bCheck = false;
	bool bShift = false;
	if (GetAsyncKeyState('W'))
	{
		vDir += vLook;
		bCheck = true;
	}
	else if (GetAsyncKeyState('S'))
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
	if (GetAsyncKeyState(VK_SHIFT))
	{
		if (0 < m_pPlayer->Get_Stamina())
			bShift = true;
		else
			m_pPlayer->Set_Exhaust(1.5f);
	}
	if (bCheck)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		if (bShift)
		{
			vDir *= m_fBoostMulti;
			m_pPlayer->Add_Stamina(-1);
			m_pPlayer->Set_AccelCheck(true);
			m_pPlayer->Set_Animation(ANI_FASTFLY);
		}
		else
		{
			m_pPlayer->Set_Animation(ANI_FLY);
			if (m_pPlayer->Get_Stamina() < m_pPlayer->Get_MaxStamina() && m_pPlayer->Get_Exhaust() < 0.f)
				m_pPlayer->Add_Stamina(1);
		}
		vDir *= fTimeDelta*m_fSpeed;
		m_pPlayer->Get_Transform2()->m_vInfo[Engine::INFO_POS] += vDir;
		float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
		float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
		//m_pPlayer->Get_Transform2()->m_vAngle.x = 0.f;
		if (0.f != fPlaneDis)
		{
			float fAngleY = acosf(vDir.z / fPlaneDis);
			if (0 > vDir.x)
				fAngleY *= -1;
			m_pPlayer->Get_Transform2()->m_vAngle.y = fAngleY;
		}
	}
	else
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDIDLE);
	}
	//이륙
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Get_Transform2()->m_vInfo[Engine::INFO_POS] += _vec3(0.f, 1.f, 0.f);
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
	}
}

void CPLandRush::LateUpdate_State()
{
	float fHeight;
	_vec3 vNorm;
	Land_Check(&fHeight, &vNorm);

	m_pPlayer->m_vNorm += (vNorm - m_pPlayer->m_vNorm)*0.2f;

	vNorm = m_pPlayer->m_vNorm;

	m_pPlayer->Get_Transform2()->m_vInfo[Engine::INFO_POS].y = fHeight;

	//지형탈때 X각 구하기
	//X각도
	float fDis = sqrtf(vNorm.x*vNorm.x + vNorm.y*vNorm.y + vNorm.z*vNorm.z);
	float fPlaneDis = sqrtf(vNorm.x*vNorm.x + vNorm.z*vNorm.z);
	float fAngleX = acosf(fPlaneDis / fDis);
	//천장타기때 필요한 주석
	//if (0 < vNorm.y)
	//	fAngleX *= -1;
	//Y각도
	float fAngleY;
	if (0.f == fPlaneDis)
		fAngleY = 0.f;
	else
	{
		fAngleY = acosf(vNorm.z / fPlaneDis);
		if (0 > vNorm.x)
		{
			fAngleY *= -1;
			fAngleY += Pi * 2;
		}
	}
	m_pPlayer->Get_Transform2()->m_vAngle.x = -(Pi*0.5f - fAngleX)*cosf(m_pPlayer->Get_Transform2()->m_vAngle.y - fAngleY);
}

void CPLandRush::Out_State()
{
}

CPLandRush* Engine::CPLandRush::Create(void)
{
	return new CPLandRush;
}

void Engine::CPLandRush::Free(void)
{

}

CComponent* Engine::CPLandRush::Clone(void)
{
	return new CPLandRush(*this);
}