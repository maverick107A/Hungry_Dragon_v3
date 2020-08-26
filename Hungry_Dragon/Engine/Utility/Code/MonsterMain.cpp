#include "MonsterMain.h"
#include "Export_Function.h"

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
	m_fDetect_Range = 400.f;
	m_fDead_Range = 7000.f;
	m_tDeadColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	return S_OK;
}

void CMonsterMain::Initialize_Object(void)
{
}

int Engine::CMonsterMain::Update_Object(const float & fTimeDelta)
{

	if (m_bFirst)
	{
		m_pPlayerTransformCom = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));
		m_bFirst = false; 
	}

	 m_pPlayerTransformCom->Get_Info(Engine::INFO_POS ,&m_vPlayerPos);


	Engine::CGameObject::Update_Object(fTimeDelta);

	D3DXVECTOR3	vMonsterPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vMonsterPos);

	D3DXVECTOR3 Dir = vMonsterPos - m_vPlayerPos;
	m_fPlayerDistance = D3DXVec3Length(&Dir);
	Dir.y = 0;
	m_fDistance = D3DXVec3Length(&Dir);

	if (m_eState != MONSTER_DYING &&  m_eState != MONSTER_DEACTIVATE && m_eState != MONSTER_SUICIDE && m_eState != MONSTER_LAYDEAD && m_eState != MONSTER_DIG)
	{
		if (m_fDistance < m_fDetect_Range && m_eState != MONSTER_DYING)
		{
			m_eState = MONSTER_ACTIVATE;

		}
		else if (m_eState != MONSTER_DYING)
		{
			m_eState = MONSTER_IDLE;
		}
	}
	if (m_fDistance > m_fDead_Range)
	{
		m_eState = MONSTER_REBORN;
		m_iEvent = MONSTER_DEAD;
	}

	if (m_eState == MONSTER_SUICIDE)
	{
		m_fMonster_HP -= m_fDamaged;
		Dead_Monster();
	}

	if (m_eState == MONSTER_DIG)
	{
		m_fMonster_HP -= m_fDamaged;
		m_pTransform->m_vInfo[Engine::INFO_POS].y -= m_fSpeed;
		if (m_fMonster_HP < 0)
		{
				m_eState = MONSTER_REBORN;
		m_iEvent = MONSTER_DEAD;
		}
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

	if (m_eState == MONSTER_DEACTIVATE)
	{
		m_vPlayerPos = ((Engine::CLayer*)(this->Get_Parent()))->Get_PlayerPos() + (m_pPlayerTransformCom->m_vInfo[Engine::INFO_LOOK] * 1.2f);
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
			if (m_eVariation != MONSTER_HORIZONBAT && m_eVariation != MONSTER_BAT)
			{
				m_pParticle = Engine::Particle_Create(Engine::PART_ATK, _vec3(0.f, 0.f, 0.f));
				//m_pParticle = Engine::Particle_Create(Engine::PART_FRAGILE,_vec3(0.f, 0.f, 0.f));
				static_cast<Engine::CParticle*>(m_pParticle)->Set_LifeTime(true, m_fParticleLifeTime);
				Engine::Set_ParticleColor(static_cast<CParticle*>(m_pParticle), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
			}
	
		}
		if (m_eState == MONSTER_SUICIDE || m_eState == MONSTER_LAYDEAD)
		{
			//Engine::CResources*			m_pParticle = nullptr;
			m_pParticle = Engine::Particle_Create(Engine::PART_FRAGILE, _vec3(0.f, 0.f, 0.f));
			static_cast<Engine::CParticle*>(m_pParticle)->Set_LifeTime(true, m_fParticleLifeTime);
			Engine::Set_ParticleColor(static_cast<CParticle*>(m_pParticle), m_tDeadColor);
		}				
		if (m_eState == MONSTER_DYING)
		{
			m_pParticle = nullptr;

			if(m_eVariation != MONSTER_HORIZONBAT && m_eVariation != MONSTER_BAT)
			{
				CParticle*  tempParticle=static_cast<CParticle*>(Engine::Particle_Create(Engine::PART_FRAGILE, _vec3(0.f, 0.f, 0.f)));
				tempParticle->Set_LifeTime(true, m_fParticleLifeTime);
				Engine::Set_ParticleColor(static_cast<CParticle*>(tempParticle), m_tDeadColor);
				D3DXVECTOR3	vParticlePos;
				m_pTransform->Get_Info(Engine::INFO_POS, &vParticlePos);
				Engine::Set_ParticleTrans(tempParticle, vParticlePos);
			}
			// 여기서 스텟 넘겨주시면 됩니다.
			switch (m_eType)
			{
			case Engine::CMonsterMain::BUFF_HP:
				Get_EventMgr()->Set_Event(0, 10+(rand()%50), m_eVariation);
				break;
			case Engine::CMonsterMain::BUFF_MP:
				Get_EventMgr()->Set_Event(1, 10 + (rand() % 50), m_eVariation);

				break;
			case Engine::CMonsterMain::BUFF_SP:
				Get_EventMgr()->Set_Event(2, 10 + (rand() % 50), m_eVariation);

				break;
			case Engine::CMonsterMain::BUFF_EXP:
				Get_EventMgr()->Set_Event(3, 10 + (rand() % 50), m_eVariation);

				break;
			case Engine::CMonsterMain::BUFF_NONE:
				Get_EventMgr()->Set_Event(4, 30 + (rand() % 200), m_eVariation);
				break;
			case Engine::CMonsterMain::BUFF_END:
				break;
			default:
				break;
			}
		}

		if (m_eState == MONSTER_DIG)
		{
			//m_pParticle = Engine::Particle_Create(Engine::PART_STONE, _vec3(0.f, 0.f, 0.f));
			//static_cast<Engine::CParticle*>(m_pParticle)->Set_LifeTime(true, m_fParticleLifeTime);
			//Engine::Set_ParticleColor(static_cast<CParticle*>(m_pParticle), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
			m_pParticle = Engine::Particle_Create(Engine::PART_ATK, _vec3(0.f, 0.f, 0.f));
			static_cast<Engine::CParticle*>(m_pParticle)->Set_LifeTime(true, m_fParticleLifeTime);
			Engine::Set_ParticleColor(static_cast<CParticle*>(m_pParticle), D3DXCOLOR(0.8f, 0.78f, 0.13f, 1.f));
		}

		m_preState = m_eState;
	
	
	}
}

void Engine::CMonsterMain::Dead_Monster()
{
	m_pTransform->Set_Scale(m_fScale);

	if (m_fMonster_HP <= 0)
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

	if (m_fScale <= 0)
	{
		m_fScale = 0;
	}

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
