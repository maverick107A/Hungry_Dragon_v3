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
			if (PosX < 12800.f)
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
			if (PosZ < 12800.f)
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


	D3DXVECTOR3 vTemp1 = m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = (float)pTerrain->Get_TerrainHeight()[Vernum] * 10.f+20.f;
		Vertex2.y = (float)pTerrain->Get_TerrainHeight()[Vernum + 1] * 10.f + 20.f;
		Vertex3.y = (float)pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] * 10.f + 20.f;

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

		if (m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght)
			return true;
	}
	else
	{
		Vertex2.y = (float)pTerrain->Get_TerrainHeight()[Vernum + 1]*10.f + 20.f;
		Vertex3.y = (float)pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] * 10.f + 20.f;
		Vertex4.y = (float)pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE + 1] * 10.f + 20.f;

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

		if (m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght)
			return true;
	}
	return false;
}

void Engine::CPlayerState::Free(void)
{

}