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
}

void CPLandRush::Update_State(const float& fTimeDelta)
{
	//¶¥ÀÌµ¿
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
	if (GetAsyncKeyState(VK_SHIFT))
	{
		bShift = true;
	}
	if (bCheck)
	{
		vDir.y = 0.f;
		D3DXVec3Normalize(&vDir, &vDir);
		if (bShift)
		{
			vDir *= 100.f;
		}
		vDir *= fTimeDelta*m_fSpeed;
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += vDir;
		float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
		float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
		m_pPlayer->Get_Transform()->m_vAngle.x = 0.f;
		if (0.f != fPlaneDis)
		{
			float fAngleY = acosf(vDir.z / fPlaneDis);
			if (0 > vDir.x)
				fAngleY *= -1;
			m_pPlayer->Get_Transform()->m_vAngle.y = fAngleY;
		}
		float fHeight;
		Land_Check(&fHeight);
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y = fHeight;
	}
	else
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDIDLE);
	}
	//ÀÌ·ú
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += _vec3(0.f, 1.f, 0.f);
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLY);
	}
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