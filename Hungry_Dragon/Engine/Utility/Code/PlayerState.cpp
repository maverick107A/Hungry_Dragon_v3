#include "PlayerState.h"
#include "PlayerMain.h"
#include "Transform.h"
#include "Terrain.h"

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

bool CPlayerState::Land_Check(float* _fHeight)
{
	D3DXVECTOR3* vPos = &m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS];
	CTerrain*	 pTerrain = m_pPlayer->Get_Terrain();

	//if (vPos->y > 13.f) 여기다 높이에 의한 컬링 만들어야함
	//	return;

	int Vernum = (int(vPos->x*INVERSETILESIZE) + VERTEXSIZE*int(vPos->z*INVERSETILESIZE));

	if (0 > Vernum || VERTEXSIZE*VERTEXSIZE < Vernum)
	{
		*_fHeight = 0.f;
		return false;
	}

	D3DXVECTOR3 Vertex1 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };


	D3DXVECTOR3 vTemp1 = *vPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = pTerrain->Get_TerrainHeight()[Vernum];
		Vertex2.y = pTerrain->Get_TerrainHeight()[Vernum + 1];
		Vertex3.y = pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE];

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		*_fHeight = fTerrainHieght;

		if (vPos->y <= fTerrainHieght)
			return true;
	}
	else
	{
		Vertex2.y = pTerrain->Get_TerrainHeight()[Vernum + 1];
		Vertex3.y = pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE];
		Vertex4.y = pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE + 1];

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex3);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		*_fHeight = fTerrainHieght;

		if (vPos->y <= fTerrainHieght)
			return true;
	}
	return false;
}

void Engine::CPlayerState::Free(void)
{

}