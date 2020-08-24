#include "CameraMain.h"
#include "BaseLand.h"

USING(Engine)

Engine::CCameraMain::CCameraMain(void)
{
}

Engine::CCameraMain::~CCameraMain(void)
{

}

void CCameraMain::Camera_Set(LPDIRECT3DDEVICE9& _pGraphicDev, _vec3 _vPos, CBaseLand* _pTerrain)
{
	_vec3 vDeltaPos = _vPos - m_vDir*m_fCameraDis - m_vPos;
	m_vPos += vDeltaPos*0.2f;
	Ride_Terrain(_pTerrain);
	//정확한 방향 설정
	m_vDir = _vPos - m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &_vPos, &m_vUp);
	_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

}

void CCameraMain::Ride_Terrain(CBaseLand* _pTerrain)
{
	CBaseLand* pTerrain = _pTerrain;
	if (nullptr == pTerrain)
		return;

	float PosX = m_vPos.x;
	float PosZ = m_vPos.z;
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

	int Vernum = int(PosX*INVERSETILESIZE) + VERTEXSIZE*int(PosZ *INVERSETILESIZE);

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

		if (m_vPos.y < fTerrainHieght)
		{
			m_fCameraDis = 0.1f;
			//if (m_fCameraDis < 0.f)
			//	m_fCameraDis = 0.f;
		}
		else if (m_fCameraDis < 150.f)
			m_fCameraDis += m_fCameraDisSpeed;
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

		if (m_vPos.y < fTerrainHieght)
		{
			m_fCameraDis = 0.1f;
			//if (m_fCameraDis < 0.f)
			//	m_fCameraDis = 0.f;
		}
		else if (m_fCameraDis < 150.f)
			m_fCameraDis += m_fCameraDisSpeed;
	}


	/*int Vernum = (int(m_vPos.x*INVERSETILESIZE) + VERTEXSIZE*int(m_vPos.z*INVERSETILESIZE));

	if (0 > Vernum || VERTEXSIZE*(VERTEXSIZE - 1) - 1 < Vernum)
	{
	}
	else
	{
		D3DXVECTOR3 Vertex1 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
		D3DXVECTOR3 Vertex2 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
		D3DXVECTOR3 Vertex3 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };
		D3DXVECTOR3 Vertex4 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };


		D3DXVECTOR3 vTemp1 = m_vPos - Vertex3;
		D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
		if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
		{
			Vertex1.y = _pTerrain->Get_TerrainHeight()[Vernum] + 1.f;
			Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1] + 1.f;
			Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129] + 1.f;

			vTemp1 = Vertex2 - Vertex1;
			vTemp2 = Vertex3 - Vertex1;
			D3DXVECTOR3 vNorm = {};
			D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

			float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
			float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

			if (m_vPos.y < fTerrainHieght)
			{
				m_fCameraDis = 0.f;
				if (m_fCameraDis < 0.f)
					m_fCameraDis = 0.f;
			}
			else if (m_fCameraDis < 100.f)
				m_fCameraDis += m_fCameraDisSpeed;
		}
		else
		{
			Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1] + 1.f;
			Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129] + 1.f;
			Vertex4.y = _pTerrain->Get_TerrainHeight()[Vernum + 130] + 1.f;

			vTemp1 = Vertex3 - Vertex4;
			vTemp2 = Vertex2 - Vertex4;
			D3DXVECTOR3 vNorm = {};
			D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

			float fConst = D3DXVec3Dot(&vNorm, &Vertex2);
			float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

			if (m_vPos.y < fTerrainHieght)
			{
				m_fCameraDis = 0.f;
				if (m_fCameraDis < 0.f)
					m_fCameraDis = 0.f;
			}
			else if (m_fCameraDis < 100.f)
				m_fCameraDis += m_fCameraDisSpeed;
		}
	}*/
}

void CCameraMain::Shock_Cam()
{
	if (m_bShock)
	{
		m_iTime += 1;

		m_fShockAngle *= -0.9f;

		if (m_iTime > 10)
		{
			m_bShock = false;
			m_fShockAngle = 0.f;
			m_iTime = 0;
		}
	}
}
