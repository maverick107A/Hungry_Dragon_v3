#include "CameraMain.h"
#include "BaseLand.h"

USING(Engine)

Engine::CCameraMain::CCameraMain(void)
{
}

Engine::CCameraMain::~CCameraMain(void)
{

}

void CCameraMain::Ride_Terrain(CBaseLand* _pTerrain)
{
	int Vernum = (int(m_vPos.x*INVERSETILESIZE) + VERTEXSIZE*int(m_vPos.z*INVERSETILESIZE));

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
	}
}

void CCameraMain::Shock_Cam()
{
	if (m_bShock)
	{
		m_iTime += 1;


		if (m_bCheck)
			m_vShock.x = 0.5f;
		else
			m_vShock.x = -0.5f;
		m_bCheck = !m_bCheck;


		if (m_iTime > 5)
		{
			m_bShock = false;
			m_vShock.x = 0.f;
			m_iTime = 0;
		}
	}
}
