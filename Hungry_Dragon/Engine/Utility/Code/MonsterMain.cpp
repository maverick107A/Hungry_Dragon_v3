#include "MonsterMain.h"
#include "Export_Function.h"
#include "Particle.h"

Engine::CMonsterMain::CMonsterMain(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{
}

Engine::CMonsterMain::~CMonsterMain(void)
{
}

HRESULT Engine::CMonsterMain::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	switch (rand() % 4)
	{
	case 0:
		m_eType = BUFF_SPEED;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fFirstFrame = 0.f;
		m_tFrame.fMaxFrame = 14.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 1:
		m_eType = BUFF_HP;
		m_tFrame.fStartFrame = 16.f;
		m_tFrame.fFirstFrame = 16.f;
		m_tFrame.fMaxFrame = 29.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 2:
		m_eType = BUFF_EXP;
		m_tFrame.fStartFrame = 31.f;
		m_tFrame.fFirstFrame = 31.f;
		m_tFrame.fMaxFrame = 44.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	case 3:
		m_eType = BUFF_SP;
		m_tFrame.fStartFrame = 46.f;
		m_tFrame.fFirstFrame = 46.f;
		m_tFrame.fMaxFrame = 59.f;
		m_tFrame.fFrameSpeed = 1.0f;
		break;
	}




	return S_OK;
}

int Engine::CMonsterMain::Update_Object(const float & fTimeDelta)
{

	m_vPlayerPos = ((Engine::CLayer*)(this->Get_Parent()))->Get_PlayerPos();

	Engine::CGameObject::Update_Object(fTimeDelta);

	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	D3DXVECTOR3 Dir = vMonsterPos - m_vPlayerPos;
	m_fPlayerDistance = D3DXVec3Length(&Dir);
	Dir.y = 0;
	m_fDistance = D3DXVec3Length(&Dir);

	if (m_eState != MONSTER_DYING &&  m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_SUICIDE && m_eState != MONSTER_LAYDEAD)
	{
		if (m_fDistance < 400 && m_eState != MONSTER_DYING)
		{
			m_eState = MONSTER_ACTIVATE;

		}
		else if (m_eState != MONSTER_DYING)
		{
			m_eState = MONSTER_IDLE;
		}
	}
	if (m_fDistance > 7000)
	{
		m_eState = MONSTER_REBORN;
		m_iEvent = MONSTER_DEAD;
	}

	if (m_eState == MONSTER_SUICIDE)
	{
		m_fMonster_HP -= m_fDamaged;
		Dead_Monster();
	}

	if (m_eState == MONSTER_LAYDEAD)
	{
		m_fMonster_HP -= (m_fMonster_MaxHP * 0.2f);
		Dead_Monster();
	}
	
	
	State_Change();
	return m_iEvent;
}

void Engine::CMonsterMain::Render_Object(void)
{

}

void Engine::CMonsterMain::LateUpdate_Object(const float & fTimeDelta)
{
	m_vPlayerPos = ((Engine::CLayer*)(this->Get_Parent()))->Get_PlayerPos();
	if (m_eState == MONSTER_DEACTIVATE)
	{
		m_pTransform->Set_Trans(&m_vPlayerPos);
		m_pTransform->Update_Component(fTimeDelta);
	}

	D3DXVECTOR3	vParticlePos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vParticlePos);
	if (m_pParticle != nullptr)
	{
		if (false == Engine::Set_ParticleTrans(m_pParticle, vParticlePos))
		{
			m_pParticle = nullptr;
		}
	}
}

void Engine::CMonsterMain::State_Change()
{
		
	if (m_preState != m_eState)
	{
		
		if (m_eState == MONSTER_DEACTIVATE)
		{
			//m_pParticle = Engine::Particle_Create(Engine::PART_ATK, _vec3(0.f, 0.f, 0.f));
			m_pParticle = Engine::Particle_Create(Engine::PART_FRAGILE,_vec3(0.f, 0.f, 0.f));
			static_cast<CParticle*>(m_pParticle)->Set_LifeTime(true, 1.f);
			//Engine::Set_ParticleColor(static_cast<CParticle*>(m_pParticle), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
			switch (rand() % 4)
			{
			case 0:
				Get_FMOD()->PlayEffect(L"Fragile0");
				break;
			case 1:
				Get_FMOD()->PlayEffect(L"Fragile1");
				break;
			case 2:
				Get_FMOD()->PlayEffect(L"Fragile2");
				break;
			case 3:
				Get_FMOD()->PlayEffect(L"Fragile3");
				break;
			}
		}
		if (m_eState == MONSTER_SUICIDE || m_eState == MONSTER_LAYDEAD)
		{
			m_pParticle = Engine::Particle_Create(Engine::PART_FRAGILE, _vec3(0.f, 0.f, 0.f));
			static_cast<CParticle*>(m_pParticle)->Set_LifeTime(true, 1.f);
		}				
		if (m_eState == MONSTER_DYING)
		{
			m_pParticle = nullptr;
			
		}

		m_preState = m_eState;
	
	
	}
}

void Engine::CMonsterMain::Dead_Monster()
{
	m_pTransform->Set_Scale(m_fScale);

	if (m_fMonster_HP < 0)
	{
		m_iEvent = MONSTER_DEAD;
		m_eState = MONSTER_DYING;
	}

}

float Engine::CMonsterMain::Ride_Terrain()
{

	float PosX = m_pTransform->m_vInfo[Engine::INFO_POS].x;
	float PosZ = m_pTransform->m_vInfo[Engine::INFO_POS].z;


	_uint uSectorNum = ((int)PosX + 25600) / 12800 + (9 - ((int)PosZ + 51200) / 12800) * 5;
	CBaseLand* pTerrain = nullptr;
	if (50 > uSectorNum)
	{
		pTerrain = Get_Terrain(uSectorNum);
	}

	if (pTerrain == nullptr)
	{
		if (m_fHeight)
			m_fHeight = 0.f;

		return false;
	}


	if (PosX > 0)
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

	int Vernum = int(PosX*INVERSETILESIZE) + VERTEXSIZE*int(PosZ *INVERSETILESIZE);



	D3DXVECTOR3 Vertex1 = { float(int(PosX*INVERSETILESIZE)*TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(PosX*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(PosX*INVERSETILESIZE)*TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(PosX*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(PosZ*INVERSETILESIZE)*TILECZ + TILECZ) };


	D3DXVECTOR3 vTemp1 = m_pTransform->m_vInfo[Engine::INFO_POS] - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = (float)pTerrain->Get_TerrainHeight()[Vernum] * 10.f + 20.f;
		Vertex2.y = (float)pTerrain->Get_TerrainHeight()[Vernum + 1] * 10.f + 20.f;
		Vertex3.y = (float)pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] * 10.f + 20.f;

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*PosX - vNorm.z*PosZ) / vNorm.y;

		return fTerrainHieght;
	
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

		return fTerrainHieght;

	}
	return false;
}

void Engine::CMonsterMain::Kill_Monster(const float& fTimeDelta)
{
	m_eState = MONSTER_DEACTIVATE;
	m_fMonster_HP -= m_fDamaged;
	m_fScale = m_fMonster_HP / m_fMonster_MaxHP;
	m_fScale = m_fMaxScale * m_fScale;
	Dead_Monster();
}

void Engine::CMonsterMain::Kill_Lay_Monster(const float & fTimeDelta)
{
	m_eState = MONSTER_LAYDEAD;
}

CBaseLand * CMonsterMain::Get_Terrain(_uint _uNum)
{
	return m_pTerrain[_uNum];
}

HRESULT Engine::CMonsterMain::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);



	return S_OK;
}

void Engine::CMonsterMain::Key_Input(const float & fTimeDelta)
{

}

Engine::CMonsterMain * Engine::CMonsterMain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterMain*		pInstance = new CMonsterMain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CMonsterMain::Free(void)
{
	Engine::CGameObject::Free();
}
