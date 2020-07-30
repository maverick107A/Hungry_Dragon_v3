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
	//땅이동
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
		_vec3 vNorm;
		Land_Check(&fHeight, &vNorm);
		m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y = fHeight;

		//지형탈때 X각 구하기
		//X각도
		fDis = sqrtf(vNorm.x*vNorm.x + vNorm.y*vNorm.y + vNorm.z*vNorm.z);
		fPlaneDis = sqrtf(vNorm.x*vNorm.x + vNorm.z*vNorm.z);
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
		m_pPlayer->Get_Transform()->m_vAngle.x = -(Pi*0.5f - fAngleX)*cosf(m_pPlayer->Get_Transform()->m_vAngle.y - fAngleY);


	}
	else
	{
		m_pPlayer->Set_Sate(CPlayerMain::STATE_LANDIDLE);
	}
	//이륙
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