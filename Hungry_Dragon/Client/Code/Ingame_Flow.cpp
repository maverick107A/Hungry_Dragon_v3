#include "stdafx.h"
#include "Ingame_Flow.h"
#include "Export_Function.h"

// 씬들
#include "Logo.h"
#include "Scene_Proto.h"
#include "Scene_Forest.h"
#include "Scene_Cave.h"
#include "Scene_Cloud.h"
#include "Scene_Volcano.h"
//#include "Scene_Iceland.h"
#include "Scene_Select.h"
#include "Scene_Menu.h"

// 리소스들
#include "Terrain_Parts.h"
#include "Tree_Object.h"
#include "Color_Mask.h"

USING(Engine)

IMPLEMENT_SINGLETON(CIngame_Flow)



CIngame_Flow::CIngame_Flow(void)
{
}


CIngame_Flow::CIngame_Flow(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
}

CIngame_Flow::~CIngame_Flow(void)
{
}

void CIngame_Flow::Init_Flow(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXSPRITE pSprite)
{
	m_pGraphicDev = pGraphicDev;
	m_pSprite = pSprite;
}

void CIngame_Flow::Update_BeforeScene(const Engine::_float & _fTimeDelta)
{
}

void CIngame_Flow::Update_AfterScene(const Engine::_float & _fTimeDelta)
{
}

void CIngame_Flow::LateUpdate_BeforeScene(const Engine::_float & _fTimeDelta)
{
}

void CIngame_Flow::LateUpdate_AfterScene(const Engine::_float & _fTimeDelta)
{

}

void CIngame_Flow::Render_BeforeScene()
{
}

void CIngame_Flow::Render_AfterScene()
{
}

void CIngame_Flow::Update_Event()
{
	for (auto iIdx : m_listEvent)
	{
		Occur_Event(iIdx);
	}
	m_listEvent.clear();
}

void CIngame_Flow::Init_Mask()
{
	for (int i = 0; i < 8; ++i)
	{
		m_pMaskTexObj[i] = CColor_Mask::Create(m_pGraphicDev);
		m_pMaskTexObj[i]->Init_MaskTex(i);
	}
}

void CIngame_Flow::Occur_Event(int _iEvent)
{


	switch (_iEvent)
	{
	case EVENT_SCENECHANGE:
		switch (m_eReservedScene)
		{
		case SCENENUM::SCENE_LOGO:
			CLogo::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_MENU:
			CScene_Menu::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_OPTION:
			//CScene_Option::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_SELECT:
			CScene_Select::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_FOREST:
			CScene_Forest::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_CAVE:
			CScene_Cave::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_CLOUD:
			CScene_Cloud::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_VOLCANO:
			CScene_Volcano::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_ICELAND:
			//CScene_Iceland::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_PROTO:
			CScene_Proto::Create(m_pGraphicDev);
			break;
		case SCENENUM::SCENE_END:
			break;
		default:
			break;
		}
		break;
	}
}

void CIngame_Flow::Set_MaskColor(int _iIdx)
{
	m_pMaskTexObj[_iIdx]->Set_ColorMask();
}

void CIngame_Flow::Set_DefaultTex()
{
	m_pGraphicDev->SetTexture(0, 0);
}

void CIngame_Flow::Load_ForestTerrain()
{
	TCHAR szBuf[256] = L"";
	for (int i = 0; i < 50; ++i)
	{
		m_pParts[i] = CTerrain_Parts::Create(m_pGraphicDev);
		wsprintf(szBuf, L"../../Asset/Terrain/Korea/KoreaHeight_%.2d.bmp", i + 1);
		//wsprintf(szBuf, L"../../Asset/Terrain/Australia/Australia_%.2d.bmp", i + 1);
		m_pParts[i]->Set_HeightMap(szBuf);
		//m_pParts[i]->Set_HeightMap(L"../../Asset/Terrain/Korea/KoreaHeight_51.bmp");
		m_pParts[i]->Set_Trans(_vec3(12800.f*((i % 5) - 2), 0.f, -12800.f*((i / 5) - 5)));
	}

	// 접합부 용접작업 ㅠㅠ
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_pParts[i * 5 + j]->Weld_Edge(m_pParts[i * 5 + j + 1], true);
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			m_pParts[i * 5 + j]->Weld_Edge(m_pParts[(i + 1) * 5 + j], false);
		}
	}
}

void CIngame_Flow::Release_ForestTerrain()
{
	for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}
	for (int i = 0; i < 8; ++i)
	{
		Safe_Release(m_pMaskTexObj[i]);
	}
	m_listEvent.clear();
}

void CIngame_Flow::Load_TreeList()
{
	if (DEBUG_WITHOUT_TREE)
	{
		return;
	}
	for (int i = 0; i < 50; ++i)
	{
		vector<int> vecHeight = m_pParts[i]->Get_HeightVector();

		for (int j = 0; j < 128; ++j)
		{
			for (int k = 0; k < 128; ++k)
			{
				if (5 >(rand() % 100))
				{
					CTree_Object* pTree = CTree_Object::Create(m_pGraphicDev);
					// 인덱스 안맞음 고쳐야함
					pTree->Set_Trans(_vec3((float)(100 * k - 12800 * (2 - (i % 5))), vecHeight[j * 129 + k] / 255.f*2560.f, (float)(100 * j + 12800 * (5 - (i / 5)))));
					pTree->Set_Scale(10);
					pTree->Update_Object(0);
					m_arrRenderGroupIdx[i].emplace_back(pTree);
				}
			}
		}
	}
}

void CIngame_Flow::Release_TreeList()
{
	if (DEBUG_WITHOUT_TREE)
	{
		return;
	}
	for (int i = 0; i < 50; ++i)
	{
		for (auto& pTreeObj : m_arrRenderGroupIdx[i])
		{
			Safe_Release(pTreeObj);
		}
		m_arrRenderGroupIdx[i].clear();
	}
}

void CIngame_Flow::Release_AllResources()
{
	Release_ForestTerrain();
	Release_TreeList();
}




