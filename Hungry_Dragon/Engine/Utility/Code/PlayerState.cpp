#include "PlayerState.h"
#include "PlayerMain.h"
#include "Transform.h"
#include "Terrain.h"
#include "BaseLand.h"

USING(Engine)

Engine::CPlayerState::CPlayerState(void)
{
	
}

Engine::CPlayerState::CPlayerState(const CPlayerState& rhs)
{

}

Engine::CPlayerState::~CPlayerState(void)
{

}

bool CPlayerState::Land_Check(float* _fHeight, _vec3* _vNorm)
{
	//D3DXVECTOR3* vPos = &m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS];
	CBaseLand* pTerrain = m_pPlayer->Get_Terrain();
	
	if (pTerrain == nullptr)
	{
		if (_fHeight)
			*_fHeight = 0.f;
		if (_vNorm)
			*_vNorm = _vec3(0.f, 1.f, 0.f);
		return false;
	}

	float PosX = m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].x;
	float PosZ = m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].z;
	if (PosX > 0.f)
	{
		while (true)
		{
			if (PosX <= 12800.f)
				break;
			PosX -= 12800.f;
		}
	}
	else
	{
		while (true)
		{
			if (PosX > 0.f)
				break;
			PosX += 12800.f;
		}
	}

	if (PosZ > 0)
	{
		while (true)
		{
			if (PosZ <= 12800.f)
				break;
			PosZ -= 12800.f;
		}
	}
	else
	{
		while (true)
		{
			if (PosZ > 0.f)
				break;
			PosZ += 12800.f;
		}
	}


	//if (vPos->y > 13.f) 여기다 높이에 의한 컬링 만들어야함
	//	return;

	//m_uCurrSectorNum = ((int)fPlayerX + 25600) / 12800 + (9 - ((int)fPlayerZ + 51200) / 12800) * 5;
	//int Vernum = (int(vPos->x*INVERSETILESIZE) + VERTEXSIZE*int(vPos->z*INVERSETILESIZE));

	int Vernum = int(PosX*INVERSETILESIZE) + VERTEXSIZE*int(PosZ *INVERSETILESIZE);

	//if (0 > Vernum || VERTEXSIZE*(VERTEXSIZE-1)-1 < Vernum)
	//{
	//	if(_fHeight)
	//		*_fHeight = 0.f;
	//	return false;
	//}

	//if (_fHeight)
	//	*_fHeight = (float)pTerrain->Get_TerrainHeight()[Vernum]* 10.f;
	//if (_vNorm)
	//	*_vNorm = _vec3(0.f,1.f,0.f);
	//if (m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y <= (float)pTerrain->Get_TerrainHeight()[Vernum]* 10.f)
	//	return true;

	D3DXVECTOR3 Vertex1 = { float(int(PosX*INVERSETILESIZE)*TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(PosX*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(PosX*INVERSETILESIZE)*TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(PosX*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ + TILECZ) };

	_vec3 vPlayerPos = { PosX, 0.f, PosZ };

	D3DXVECTOR3 vTemp1 = vPlayerPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = pTerrain->Get_AdvanceHeight()[Vernum] + 40.f;
		Vertex2.y = pTerrain->Get_AdvanceHeight()[Vernum + 1] + 40.f;
		Vertex3.y = pTerrain->Get_AdvanceHeight()[Vernum + VERTEXSIZE] + 40.f;

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*PosX - vNorm.z*PosZ) / vNorm.y;

		if(_fHeight)
			*_fHeight = fTerrainHieght;
		if (_vNorm)
			*_vNorm = vNorm;


		if (GetAsyncKeyState(VK_LBUTTON))
		{
			TCHAR szBuff[256] = L"";
			wsprintf(szBuff, L"1 :%d, 2 :%d, 3 :%d", (int)Vertex1.y * 100, (int)Vertex2.y * 100, (int)Vertex3.y * 100);
			MessageBox(nullptr, szBuff, L"XY", 0);
		}

		if (m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght)
			return true;
	}
	else
	{
		Vertex2.y = pTerrain->Get_AdvanceHeight()[Vernum + 1] + 40.f;
		Vertex3.y = pTerrain->Get_AdvanceHeight()[Vernum + VERTEXSIZE] + 40.f;
		Vertex4.y = pTerrain->Get_AdvanceHeight()[Vernum + VERTEXSIZE + 1] + 40.f;

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex3);
		float fTerrainHieght = (fConst - vNorm.x*PosX - vNorm.z*PosZ) / vNorm.y;

		if (_fHeight)
			*_fHeight = fTerrainHieght;
		if (_vNorm)
			*_vNorm = vNorm;

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			TCHAR szBuff[256] = L"";
			wsprintf(szBuff, L"2 :%d, 3 :%d, 4 :%d", (int)(Vertex2.y * 100), (int)(Vertex3.y * 100), (int)(Vertex4.y * 100));
			MessageBox(nullptr, szBuff, L"XY", 0);
		}

		if (m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght)
			return true;
	}
	return false;
}

void CPlayerState::Aim()
{
	//float fAngleY = m_pPlayer->Get_AngleY();

	//if (fAngleY > D3DX_PI*2.f)
	//{
	//	while (true)
	//	{
	//		fAngleY -= D3DX_PI*2.f;
	//		if (fAngleY < D3DX_PI*2.f)
	//			break;
	//	}
	//}
	//else if (fAngleY < 0.f)
	//{
	//	while (true)
	//	{
	//		fAngleY += D3DX_PI*2.f;
	//		if (fAngleY > 0.f)
	//			break;
	//	}
	//}

	//float fDeltaAngleX = (m_pPlayer->Get_AngleX() - m_pPlayer->Get_Transform()->m_vAngle.x)*0.25f;
	//float fDeltaAngleY = (fAngleY - m_pPlayer->Get_Transform()->m_vAngle.y)*0.25f;



	//m_pPlayer->Get_Transform()->m_vAngle.x += fDeltaAngleX;
	//m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaAngleY;

	D3DXVECTOR3 vLook = { 0.f,0.f,0.f };

	D3DXMATRIX vRotX, vRotY, vRotTotal;
	D3DXMatrixRotationX(&vRotX, m_pPlayer->Get_AngleX());
	D3DXMatrixRotationY(&vRotY, m_pPlayer->Get_AngleY());

	vRotTotal = vRotX*vRotY;
	D3DXVec3TransformNormal(&vLook, &_vec3(0.f, 0.f, 1.f), &vRotTotal);

	float fDis = sqrtf(vLook.x*vLook.x + vLook.y*vLook.y + vLook.z*vLook.z);
	float fPlaneDis = sqrtf(vLook.x*vLook.x + vLook.z*vLook.z);
	float fAngleX = acosf(fPlaneDis / fDis);
	if (0 < vLook.y)
		fAngleX *= -1;
	//부드러운 이동 시작
	float fDeltaX = (fAngleX - m_pPlayer->Get_Transform()->m_vAngle.x)*0.1f;
	m_pPlayer->Get_Transform()->m_vAngle.x += fDeltaX;

	if (0.f != fPlaneDis)
	{
		float fAngleY = acosf(vLook.z / fPlaneDis);
		if (0 > vLook.x)
		{
			fAngleY *= -1;
			fAngleY += D3DX_PI * 2;
		}
		//부드러운이동 시작
		float fDeltaY = (fAngleY - m_pPlayer->Get_Transform()->m_vAngle.y);

		if (fDeltaY > 0.f)
		{
			if (fDeltaY < D3DX_PI)
				m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaY*0.9f;
			else
				m_pPlayer->Get_Transform()->m_vAngle.y += (fDeltaY - D3DX_PI * 2)*0.9f;
		}
		else
		{
			if (fDeltaY > -D3DX_PI)
				m_pPlayer->Get_Transform()->m_vAngle.y += fDeltaY*0.9f;
			else
				m_pPlayer->Get_Transform()->m_vAngle.y += (D3DX_PI * 2 + fDeltaY)*0.9f;
		}
		if (m_pPlayer->Get_Transform()->m_vAngle.y < 0)
			m_pPlayer->Get_Transform()->m_vAngle.y += D3DX_PI * 2;
		if (m_pPlayer->Get_Transform()->m_vAngle.y > D3DX_PI * 2)
			m_pPlayer->Get_Transform()->m_vAngle.y -= D3DX_PI * 2;
	}
}

void Engine::CPlayerState::Free(void)
{

}