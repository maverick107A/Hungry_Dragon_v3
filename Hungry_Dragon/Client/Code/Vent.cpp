#include "stdafx.h"
#include "Vent.h"
#include "PlayerMain.h"

#include "Export_Function.h"

USING(Engine)

CVent::CVent(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CVent::~CVent(void)
{

}

HRESULT CVent::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fCaveLength = m_pBufferCom->Get_Height();
	m_pTransform->Set_Trans(&_vec3(0.f,0.f, m_fCaveLength*0.5f));
	m_pTransformBeyond->Set_Trans(&_vec3(0.f, 0.f, m_fCaveLength*1.5f));
	m_fForwardSpeed = 400.f;
	m_fSummonTime = 1.f;
	m_fSummonTick = 0.f;
	Ready_Obstacles();

	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	return S_OK;
}

void CVent::Initialize_Object(void)
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform",Engine::ID_DYNAMIC));
	m_pPlayer = static_cast<Engine::CPlayerMain*>(Engine::Get_Object(L"GameLogic", L"TestPlayer"));
}

_int CVent::Update_Object(const _float& fTimeDelta)
{
	if (!m_bActive)
	{
		return 0;
	}

	m_pTransform->Add_Trans(&_vec3(0.f, 0.f, -m_fForwardSpeed*fTimeDelta));
	m_pTransformBeyond->Add_Trans(&_vec3(0.f, 0.f, -m_fForwardSpeed*fTimeDelta));

	if (m_bLoop)
	{
		if (-m_fCaveLength*0.5f >= m_pTransform->Get_World()._43)
		{
			m_pTransform->Add_Trans(&_vec3(0.f, 0.f, m_fCaveLength*2.f));

		}
		if (-m_fCaveLength*0.5f >= m_pTransformBeyond->Get_World()._43)
		{
			m_pTransformBeyond->Add_Trans(&_vec3(0.f, 0.f, m_fCaveLength*2.f));

		}
	}

	for (auto& pObs : m_listActiveObs)
	{
		pObs->Update_Object(fTimeDelta);
		if (pObs->Get_Transform()->Get_World()._43 < -10.f)
		{
			++m_uDelayDeactNum;
			//충돌처리
			int i = 0;
			if (pObs->Get_Transform()->m_vInfo[Engine::INFO_POS].x == 10.f)
				i = 0;
			else if (pObs->Get_Transform()->m_vInfo[Engine::INFO_POS].x == -10.f)
				i = 1;
			else if (pObs->Get_Transform()->m_vInfo[Engine::INFO_POS].y == 10.f)
				i = 2;
			else if (pObs->Get_Transform()->m_vInfo[Engine::INFO_POS].y == -10.f)
				i = 3;
			else
				i = 4;
			switch(i)
			{
			case 0:
				if (m_pPlayerTrans->m_vInCamPos.x > 3.5)
					m_pPlayer->Get_Camera()->Set_Shock();
				break;
			case 1:
				if (m_pPlayerTrans->m_vInCamPos.x < -3.5)
					m_pPlayer->Get_Camera()->Set_Shock();
				break;
			case 2:
				if (m_pPlayerTrans->m_vInCamPos.y > 3.5)
					m_pPlayer->Get_Camera()->Set_Shock();
				break;
			case 3:
				if (m_pPlayerTrans->m_vInCamPos.y < -3.5)
					m_pPlayer->Get_Camera()->Set_Shock();
				break;
			case 4:
				if (pObs->Get_Transform()->m_vAngle.x)
				{
					if (abs(m_pPlayerTrans->m_vInCamPos.x) < 3.5)
						m_pPlayer->Get_Camera()->Set_Shock();
				}
				else
				{
					if (abs(m_pPlayerTrans->m_vInCamPos.y) < 3.5)
						m_pPlayer->Get_Camera()->Set_Shock();
				}
				break;
			}
		}
	}
	for (_uint i = 0; i < m_uDelayDeactNum; ++i)
	{
		Deactivate_Obstacle();
	}
	m_uDelayDeactNum = 0;


	m_fSummonTick += fTimeDelta;
	if (m_fSummonTick >= m_fSummonTime)
	{
		int iRand = rand() % 20;
		switch (iRand)
		{
			// 1개짜리
		case 0:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 1:
			Instantiate_Obstacle(_vec3(10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 2:
			Instantiate_Obstacle(_vec3(-10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 3:
			Instantiate_Obstacle(_vec3(0.f, 10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;
		case 4:
			Instantiate_Obstacle(_vec3(0.f, -10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;
		case 5:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;
		case 6:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			Instantiate_Obstacle(_vec3(10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 7:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			Instantiate_Obstacle(_vec3(-10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 8:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), 0.f, D3DX_PI*0.5f);
			Instantiate_Obstacle(_vec3(0.f, 10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;
		case 9:
			Instantiate_Obstacle(_vec3(0.f, 0.f, 1000.f), 0.f, D3DX_PI*0.5f);
			Instantiate_Obstacle(_vec3(0.f, -10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;

		case 10:
			Instantiate_Obstacle(_vec3(-10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			Instantiate_Obstacle(_vec3(10.f, 0.f, 1000.f), D3DX_PI*0.5f, 0.f);
			break;
		case 11:
			Instantiate_Obstacle(_vec3(0.f, 10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			Instantiate_Obstacle(_vec3(0.f, -10.f, 1000.f), 0.f, D3DX_PI*0.5f);
			break;
		default:

			break;
		}
		
		m_fSummonTick -= m_fSummonTime;
	}


	return 0;
}

void CVent::Render_Object(void)
{
	if (!m_bActive)
	{
		return;
	}
	Engine::CGameObject::Update_Object(float(0));
	//여기까지 레이트업데이트에 넣어줘야함
	
	m_pTex->Set_Texture();
	
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
	m_pTransformBeyond->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
	
	m_pObsTex->Set_Texture();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	for (auto& pObs : m_listActiveObs)
	{
		pObs->Render_Object();
	}
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	
}

void CVent::Free(void)
{
	Engine::CGameObject::Free();

	Release_Obstacles();
}


void CVent::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
	m_pTransformBeyond->Set_Trans(&_vec3(_vPos.x, _vPos.y, _vPos.z + m_fCaveLength*1.f));
}

float CVent::Get_EndPoint()
{
	return m_pTransform->Get_World()._43 > m_pTransformBeyond->Get_World()._43 ?
		   m_pTransform->Get_World()._43 : m_pTransformBeyond->Get_World()._43 ;
}

void CVent::Ready_Obstacles()
{
	// 30개정도의 장애물 준비
	m_vecObs.reserve(30);
	for (int i = 0; i < 30; ++i)
	{
		m_pObs = CObstacle::Create(m_pGraphicDev);
		m_vecObs.emplace_back(m_pObs);
		m_pObs->Set_Active(false);
	}
	m_iterHead = m_vecObs.begin();
	m_iterTail = m_vecObs.begin();
}

void CVent::Release_Obstacles()
{
	m_listActiveObs.clear();
	for (int i = 0; i < 30; ++i)
	{
		Safe_Release(m_vecObs[i]);
	}
	m_vecObs.clear();
	m_vecObs.shrink_to_fit();

}

void CVent::Instantiate_Obstacle(_vec3 & vPos, _float fRotX, _float fRotY)
{
	if (m_bFull)
	{
		return;
	}

	m_pObs = *m_iterTail;
	++m_iterTail;
	if (m_iterTail == m_vecObs.end())
	{
		m_iterTail = m_vecObs.begin();
	}
	if (m_iterTail == m_iterHead)
	{
		m_bFull = true;
	}
	m_pObs->Set_Active(true);
	m_pObs->Set_Trans(vPos);
	m_pObs->Set_RotationX(fRotX);
	m_pObs->Set_RotationY(fRotY);
	m_listActiveObs.emplace_back(m_pObs);
}

void CVent::Deactivate_Obstacle()
{
	if (m_bFull)
	{
		m_bFull = false;
	}
	m_pObs = *m_iterHead;
	++m_iterHead;
	if (m_iterHead == m_vecObs.end())
	{
		m_iterHead = m_vecObs.begin();
	}
	m_pObs->Set_Active(false);
	if (m_pObs != *(m_listActiveObs.begin()))
	{
		return;		// 치명적인 에러!
	}
	m_listActiveObs.pop_front();
}

HRESULT CVent::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK_RETURN(Clone_Component<CVentCube>(&m_pBufferCom, RESOURCE_STAGE, L"BUFFER_VENTCUBE", ID_STATIC, L"Com_Buffer"), E_FAIL);
	
	//Transform
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"), E_FAIL);
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransformBeyond, ID_DYNAMIC, L"Com_TransformBeyond"), E_FAIL);

	// tex
	FAILED_CHECK_RETURN(Clone_Component<CTexture>(&m_pTex, RESOURCE_STAGE, L"TEX_VENT", ID_STATIC, L"Com_Texture"), E_FAIL);
	FAILED_CHECK_RETURN(Clone_Component<CTexture>(&m_pObsTex, RESOURCE_STAGE, L"TEX_OBS", ID_STATIC, L"Com_Texture2"), E_FAIL);


	m_pTransform->m_vAngle.y = D3DX_PI;
	//m_pTransformBeyond->m_vScale.z = 1.1f;

	return S_OK;
}

CVent* CVent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVent*		pInstance = new CVent(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

