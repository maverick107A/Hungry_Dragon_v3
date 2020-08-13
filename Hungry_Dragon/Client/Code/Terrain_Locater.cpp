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

_int CTerrain_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);
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
	for (int i = 0; i < 50; ++i)
	{
		m_pParts[i]->Render_Object();
	}
	
}

void CTerrain_Locater::Free(void)
{
	for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}


	Engine::CGameObject::Free();

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

