#include "stdafx.h"
#include "Meteor_Spawner.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "Meteor_Object.h"
#include "Meteor_Circular.h"
#include "Meteor_Linear.h"

CMeteor_Spawner::CMeteor_Spawner(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CMeteor_Spawner::~CMeteor_Spawner(void)
{

}

HRESULT CMeteor_Spawner::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fSummonTime = 0.25f;
	m_fSummonTick = 0.f;
	m_bActive = false;
	
	return S_OK;
}

void CMeteor_Spawner::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CMeteor_Spawner::Update_Object(const _float& fTimeDelta)
{
	if (!m_bActive)
	{
		return 0;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	if (fTimeDelta > 1.f)
	{
		return 0;
	}

	m_fSummonTick += fTimeDelta;
	m_fFireTick += fTimeDelta;
	if (m_fSummonTick >= m_fSummonTime)
	{
		m_fSummonTick -= m_fSummonTime;

		Instantiate_Meteor(_vec3((float)(rand() % 384000), 10000.f, (float)(rand() % 384000)));
		Instantiate_CircularMeteor(_vec3(4000.f,0.f,0.f),_vec3(19200.f, 2200.f + (rand()%10) * 500.f, 19200.f),_vec3(0.f, 1.f, 0.f), (rand()%50 +50) * 0.02f * ((rand()%2)-0.5f), (rand()%628) * 0.01f);

	}

	for (auto& pObj : m_vecObjectPool)
	{
		if (pObj->Get_Active())
			pObj->Update_Object(fTimeDelta);
	}
	for (auto& pObj : m_vecCircularPool)
	{
		if (pObj->Get_Active())
			pObj->Update_Object(fTimeDelta);
	}
	for (auto& iter = m_listLinearPool.begin(); iter != m_listLinearPool.end();)
	{
		if ((*iter)->Update_Object(fTimeDelta) == OBJ_DEAD)
		{
			Safe_Release(*iter);
			iter = m_listLinearPool.erase(iter);
		}
		else
		{
			++iter;
		}
	}


	return 0;
}

void CMeteor_Spawner::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pGraphicDev->SetTexture(0, 0);

	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0);
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto& pObj : m_vecObjectPool)
	{
		if (pObj->Get_Active())
			pObj->Render_Object();
	}
	for (auto& pObj : m_vecCircularPool)
	{
		if (pObj->Get_Active())
			pObj->Render_Object();
	}
	for (auto& pObj : m_listLinearPool)
	{
		if (pObj->Get_Active())
			pObj->Render_Object();
	}

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

void CMeteor_Spawner::Spawn_Meteor()
{
	if (m_bActive)
	{
		return;
	}
	m_bActive = true;
	m_vecObjectPool.reserve(50);
	m_vecCircularPool.reserve(10);
	for (int i = 0; i < 50; ++i)
	{
		m_pMeteor = CMeteor_Object::Create(m_pGraphicDev);
		m_vecObjectPool.emplace_back(m_pMeteor);
		m_pMeteor->Set_Active(false);
	}
	for (int i = 0; i < 10; ++i)
	{
		m_pCircular = CMeteor_Circular::Create(m_pGraphicDev);
		m_vecCircularPool.emplace_back(m_pCircular);
		m_pCircular->Set_Active(false);
	}
	m_iterFinder = m_vecObjectPool.begin();
	m_iterCircular = m_vecCircularPool.begin();
}

void CMeteor_Spawner::Fire_Meteor()
{
	if (m_fFireTime < m_fFireTick)
	{
		m_fFireTick = 0.f;
		for (auto& pObj : m_vecCircularPool)
		{
			if (pObj->Get_Active())
			{
				_vec3 vSrc, vDest;
				vSrc = pObj->Get_PosOrigin();
				m_pPlayerTrans->Get_Info(INFO_POS, &vDest);
				// 발싸!
				Instantiate_LinearMeteor(_vec3(500.f,0.f,0.f), vSrc, vDest, 3.f, 0.3f);
			}
		}
	}
}

void CMeteor_Spawner::Instantiate_Meteor(_vec3 & vPos)
{
	for (; m_iterFinder != m_vecObjectPool.end(); ++m_iterFinder)
	{
		if ((*m_iterFinder)->Get_Active())
		{
			continue;
		}
		break;
	}
	if (m_iterFinder == m_vecObjectPool.end())		// 풀 1프레임 지연 기준 전부 사용중
	{
		m_iterFinder = m_vecObjectPool.begin();
		return;
	}
	else
	{
		m_pMeteor = *m_iterFinder;
	}

	m_pMeteor->Set_Active(true);
	m_pMeteor->Set_Trans(vPos);
}

void CMeteor_Spawner::Instantiate_CircularMeteor(_vec3 _vRadius, _vec3 _vCenter, _vec3 _vAxis, float _fSpeed, float _fAngle)
{
	for (; m_iterCircular != m_vecCircularPool.end(); ++m_iterCircular)
	{
		if ((*m_iterCircular)->Get_Active())
		{
			continue;
		}
		break;
	}
	if (m_iterCircular == m_vecCircularPool.end())		// 풀 1프레임 지연 기준 전부 사용중
	{
		m_iterCircular = m_vecCircularPool.begin();
		return;
	}
	else
	{
		m_pCircular = *m_iterCircular;
	}

	m_pCircular->Set_Active(true);

	m_pCircular->Set_Radius(_vRadius);
	m_pCircular->Set_Center(_vCenter);
	m_pCircular->Set_Axis(_vAxis);
	m_pCircular->Set_RotateSpeed(_fSpeed);
	m_pCircular->Set_Angle(_fAngle);
}

void CMeteor_Spawner::Instantiate_LinearMeteor(_vec3 _vRadius, _vec3 _vSrc, _vec3 _vDest, float _fLimit, float _fAngle)
{
	if (m_listLinearPool.size() > 10)
	{
		return;
	}
	m_pLinear = CMeteor_Linear::Create(m_pGraphicDev);

	m_pLinear->Set_Radius(_vRadius);
	m_pLinear->Set_Trans(_vSrc);
	m_pLinear->Set_Dest(_vDest);
	m_pLinear->Set_Limit(_fLimit);
	m_pLinear->Set_Angle(_fAngle);
	_vec3 vDelta = _vSrc - _vec3(19200.f,_vSrc.y + float((rand()%38400) - 19200), 19200.f);
	D3DXVec3Normalize(&vDelta, &vDelta);
	m_pLinear->Set_Delta(vDelta);


	m_listLinearPool.emplace_back(m_pLinear);
}

void CMeteor_Spawner::Free(void)
{

	Engine::CGameObject::Free();

	for (auto& pObj : m_vecObjectPool)
	{
		Safe_Release(pObj);
	}
	for (auto& pObj : m_vecCircularPool)
	{
		Safe_Release(pObj);
	}
	for (auto& pObj : m_listLinearPool)
	{
		Safe_Release(pObj);
	}

}


HRESULT CMeteor_Spawner::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	// 메테오 세팅
	
	return S_OK;
}

CMeteor_Spawner* CMeteor_Spawner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMeteor_Spawner*		pInstance = new CMeteor_Spawner(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

