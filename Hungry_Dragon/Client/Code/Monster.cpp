#include "stdafx.h"

#include "Monster.h"

#include "Export_Function.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

CMonster::~CMonster(void)
{
}

HRESULT CMonster::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

int CMonster::Update_Object(const float & fTimeDelta)
{
	m_vPlayerPos=((Engine::CLayer*)(this->Get_Parent()))->Get_PlayerPos();

	Engine::CGameObject::Update_Object(fTimeDelta);

	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	D3DXVECTOR3 Dir = vMonsterPos - m_vPlayerPos;
	m_fPlayerDistance = D3DXVec3Length(&Dir);
	Dir.y = 0;
	m_fDistance = D3DXVec3Length(&Dir);
	if (m_fDistance < 200)
	{
		m_bActivate = true;
	}
	else
		m_bActivate = false;


	if (m_fDistance > 7000)
	{
		m_bFirst = true;
		m_iEvent = MONSTER_DEAD;
	}


	return m_iEvent;
}

void CMonster::Render_Object(void)
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end(); ++iter)
	{
		(*iter)->Render_Buffer();
	}
}

void CMonster::LateUpdate_Object(const float & fTimeDelta)
{


}

void CMonster::Dead_Monster(const float & fTimeDelta)
{
	m_pTransform->Set_Minus_Scale(0.01f);
	
		Engine::_vec3 vOrigin = Engine::_vec3(0.f, 0.f, 0.f);
		Engine::BoundingBox tempBoundingBox;
		tempBoundingBox.vMax = Engine::_vec3(100.f, 100.f, 100.f);
		tempBoundingBox.vMin = Engine::_vec3(-100.f, -100.f, -100.f);
		Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_ATK, tempBoundingBox, vOrigin);

		//나중엔 미리 올려 놓는 식으로 구현하자
		static_cast<Engine::CAtk_Part*>(tempParticle)->Set_Texture(L"../../Asset/snowflake.dds");
		m_arrParticle.emplace_back(tempParticle);
	

	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();) {
		int life = (*iter)->Update_Component(fTimeDelta);

		if (life == 0) {
			++iter;
		}
		else {
			Safe_Release(*iter);
			iter = m_arrParticle.erase(iter);
		}

	}

	if (m_pTransform->m_vScale.x < 0 || m_pTransform->m_vScale.y < 0 || m_pTransform->m_vScale.z < 0)
	{
		m_bFirst = true;
 		m_iEvent = MONSTER_DEAD;
	}



}

float CMonster::Ride_Terrain()
{
	m_pTerrain = static_cast<Engine::CBaseLand*>
		(Engine::Get_Component(L"GameLogic",
			L"BackGround",
			L"Com_Buffer",
			Engine::ID_STATIC));

	if (m_pTerrain == nullptr)
		return 0;

	D3DXVECTOR3* vPos = &m_pTransform->m_vInfo[Engine::INFO_POS];


	int Vernum = (int(vPos->x*INVERSETILESIZE) + VERTEXSIZE*int(vPos->z*INVERSETILESIZE));

	if (Vernum < 0)
		Vernum = 0;

	if (Vernum > 16384)
		Vernum = 16384;

	D3DXVECTOR3 Vertex1 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };


	D3DXVECTOR3 vTemp1 = *vPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum] + 1;
		Vertex2.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum + 1] + 1;
		Vertex3.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] + 1;

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		return ((fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y) + 1;

	
	}
	else
	{
		Vertex2.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum + 1] + 1;
		Vertex3.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] + 1;
		Vertex4.y = (float)m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE + 1] + 1;

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex3);
		return ((fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y) + 1;
	}
}

HRESULT CMonster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Cube*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_BoxHead"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	//m_pBufferCom

	return S_OK;
}

void CMonster::Key_Input(const float & fTimeDelta)
{

}

CMonster * CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster*		pInstance = new CMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CMonster::Free(void)
{

	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();) {
		Engine::Safe_Release((*iter));
		iter = m_arrParticle.erase(iter);

	}
	m_arrParticle.clear();


	Engine::CGameObject::Free();
}
