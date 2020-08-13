#include "stdafx.h"
#include "Tree_Locater.h"
#include "Tree_Object.h"
#include "Terrain_Locater.h"

#include "Export_Function.h"

CTree_Locater::CTree_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CTree_Locater::~CTree_Locater(void)
{

}

HRESULT CTree_Locater::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	Locate_Tree();
	return S_OK;
}

void CTree_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CTree_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	_float fPlayerX = m_pPlayerTrans->Get_World()._41;
	_float fPlayerZ = m_pPlayerTrans->Get_World()._43;
	
	for (int i = 0; i < 50; ++i)
	{
		for (auto& pAuto : m_arrRenderGroupIdx[i])
		{
			pAuto->Update_Object(fTimeDelta);
		}
	}

	return 0;
}

void CTree_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	
	//for (int i = 0; i < 50; ++i)
	//{
	//	m_pParts[i]->Render_Object();
	//}
	for (int i = 0; i < 50; ++i)
	{
		for (auto& pAuto : m_arrRenderGroupIdx[i])
		{
			pAuto->Render_Object();
		}
	}
}

void CTree_Locater::Locate_Tree()
{
	CTerrain_Locater* pTerrainLocater = static_cast<CTerrain_Locater*>(Engine::Get_Object(L"GameLogic",L"BackGround"));
	
	for (int i = 22; i < 23; ++i)
	{
		vector<int> vecHeight = pTerrainLocater->Get_PartsHeight(i);

		for (int j = 0; j < 128; ++j)
		{
			for (int k = 0; k < 128; ++k)
			{
				if (25 > (rand() % 100))
				{
					CTree_Object* pTree = CTree_Object::Create(m_pGraphicDev);
					// 인덱스 안맞음 고쳐야함
					pTree->Set_Trans(_vec3(100*k - 12800*(2-(i%5)),vecHeight[j*129 + k]*2560.f/255.f,100*j + 12800 * (4 - (i / 5))));
					pTree->Set_Scale(10);
					pTree->Update_Object(0);
					m_arrRenderGroupIdx[i].emplace_back(pTree);
				}
			}
		}
	}
}

void CTree_Locater::Free(void)
{
	for (int i = 0; i < 50; ++i)
	{
		for (auto& pAuto : m_arrRenderGroupIdx[i])
		{
			Safe_Release(pAuto);
		}
		m_arrRenderGroupIdx[i].clear();
	}



	Engine::CGameObject::Free();

}


HRESULT CTree_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CTree_Locater* CTree_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTree_Locater*		pInstance = new CTree_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

