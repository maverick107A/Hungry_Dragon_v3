#include "stdafx.h"
#include "Terrain_Locater.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"

CTerrain_Locater::CTerrain_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CTerrain_Locater::~CTerrain_Locater(void)
{

}

HRESULT CTerrain_Locater::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CTerrain_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CTerrain_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	_float fPlayerX = m_pPlayerTrans->Get_World()._41;
	_float fPlayerZ = m_pPlayerTrans->Get_World()._43;
	_bool bOutline = true;


	if (-25600.f > fPlayerX)	// 좌경계
	{
		m_lstRenderIdx.clear();
		if (76800.f < fPlayerZ)
		{
			m_lstRenderIdx.emplace_back(0);
		}
		else if(-51200.f > fPlayerZ)
		{
			m_lstRenderIdx.emplace_back(45);

		}
		else
		{
			_int iIdx = (9 - ((int)fPlayerZ + 51200) / 12800) * 5;	// 9~0
			if (0 < iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx - 5);
			}
			m_lstRenderIdx.emplace_back(iIdx);
			if (45 > iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx+5);
			}
		}
	}
	else if (38400.f < fPlayerX)	// 우경계
	{
		m_lstRenderIdx.clear();
		if (76800.f < fPlayerZ)
		{
			m_lstRenderIdx.emplace_back(4);
		}
		else if (-51200.f > fPlayerZ)
		{
			m_lstRenderIdx.emplace_back(49);

		}
		else
		{
			_int iIdx = (9 - ((int)fPlayerZ + 51200) / 12800) * 5;
			if (0 < iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx - 1);
			}
			m_lstRenderIdx.emplace_back(iIdx+4);
			if (45 > iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx + 9);
			}
		}
	}
	else
	{
		if (76800.f < fPlayerZ)
		{
			m_lstRenderIdx.clear();
			_int iIdx = ((int)fPlayerX + 25600) / 12800;	// 0~4
			if (0 < iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx - 1);
			}
			m_lstRenderIdx.emplace_back(iIdx);
			if (4 > iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx + 1);
			}
			
		} 
		else if (-51200.f > fPlayerZ)
		{
			m_lstRenderIdx.clear();
			_int iIdx = ((int)fPlayerX + 25600) / 12800;	// 0~4
			if (0 < iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx + 44);
			}
			m_lstRenderIdx.emplace_back(iIdx + 45);
			if (4 > iIdx)
			{
				m_lstRenderIdx.emplace_back(iIdx + 46);
			}
		}
		else
		{
			bOutline = false;
		}
	}
	if (bOutline)
	{
		m_uCurrSectorNum = -1;
		m_uOldSectorNum = -1;
		return 0;
	}

	
	m_uCurrSectorNum = ((int)fPlayerX+25600) / 12800 + (9-((int)fPlayerZ+51200)/12800)*5;

	if (m_uCurrSectorNum != m_uOldSectorNum)
	{
		m_uOldSectorNum = m_uCurrSectorNum;
		m_lstRenderIdx.clear();
		

		if (0 > m_uCurrSectorNum || 49 < m_uCurrSectorNum)
		{
			m_uOldSectorNum = -1;
			return 0;
		}
		_uint uRenderIdx = m_uCurrSectorNum;
		// 가장자리 검사
		if (uRenderIdx % 5 == 0)		// 왼쪽
		{
			if (uRenderIdx / 5 == 0)			// 좌상
			{

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 6);
			}
			else if (uRenderIdx / 5 == 9)		// 좌하
			{
	
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 4);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);
			}
			else
			{

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 4);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 6);
			}
		}
		else if (uRenderIdx % 5 == 4)	// 오른쪽
		{
			if (uRenderIdx / 5 == 0)			// 우상
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);

			}
			else if (uRenderIdx / 5 == 9)		// 우하
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 6);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);


			}
			else
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 6);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);

				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
	
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);


			}
		}
		else
		{
			if (uRenderIdx / 5 == 0)			// 상
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 6);
			}
			else if (uRenderIdx / 5 == 9)		// 하
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 6);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);
			}
			else
			{
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 6);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum - 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum );
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 1);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 4);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 5);
				m_lstRenderIdx.emplace_back(m_uCurrSectorNum + 6);

			}
		}


		
	}

	for (int iIdx : m_lstRenderIdx)
	{
		//m_pParts[iIdx]->Update_Object(fTimeDelta);
	}
	for (int i = 0; i < 50; ++i)
	{
		m_pParts[i]->Update_Object(fTimeDelta);
	}
	return 0;
}

void CTerrain_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	for (int iIdx : m_lstRenderIdx)
	{
		m_pParts[iIdx]->Render_Object();
	}
	//for (int i = 0; i < 50; ++i)
	//{
	//	m_pParts[i]->Render_Object();
	//}
	
}

void CTerrain_Locater::Free(void)
{
	for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}


	Engine::CGameObject::Free();

}


vector<int> CTerrain_Locater::Get_PartsHeight(_uint _uNum)
{
	if (0 > _uNum || 49 < _uNum)
	{
		abort();
	}
	return m_pParts[_uNum]->Get_HeightVector();
}

HRESULT CTerrain_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CHeightCol>(&m_pDummy, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));
	m_pDummy->Set_Height(L"../../Asset/Terrain/Korea/KoreaHeight_51.bmp");
	

	// buffer
	TCHAR szBuf[256] = L"";
	for (int i = 0; i < 50; ++i)
	{
		m_pParts[i] = CTerrain_Parts::Create(m_pGraphicDev);
		wsprintf(szBuf, L"../../Asset/Terrain/Korea/KoreaHeight_%.2d.bmp", i + 1);
		//wsprintf(szBuf, L"../../Asset/Terrain/Australia/Australia_%.2d.bmp", i + 1);
		m_pParts[i]->Set_HeightMap(szBuf);
		//m_pParts[i]->Set_HeightMap(L"../../Asset/Terrain/Korea/KoreaHeight_51.bmp");
		m_pParts[i]->Set_Trans(_vec3(12800.f*((i%5)-2),0.f, -12800.f*((i/5)-5)));
	}

	// 접합부 용접작업 ㅠㅠ
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_pParts[i*5+j]->Weld_Edge(m_pParts[i * 5 + j + 1], true);
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			m_pParts[i * 5 + j]->Weld_Edge(m_pParts[(i+1) * 5 + j], false);
		}
	}


	
	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CTerrain_Locater* CTerrain_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain_Locater*		pInstance = new CTerrain_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

