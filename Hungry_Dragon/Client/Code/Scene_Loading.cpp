#include "stdafx.h"
#include "Scene_Loading.h"
#include "Ingame_Flow.h"

USING(Engine)

CScene_Loading::CScene_Loading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	ZeroMemory(m_szFinish, sizeof(_tchar) * 256);
	m_pGraphicDev->AddRef();
}

CScene_Loading::~CScene_Loading(void)
{

}

HRESULT CScene_Loading::Ready_Loading(LOADINGID eLoadingID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);
	
	m_eLoadingID = eLoadingID;

	return S_OK;
}

_uint CScene_Loading::Loading_ForStage(void)
{
	lstrcpy(m_szFinish, L"Buffer Loading............");

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_CubeTex",
		Engine::BUFFER_TEXCUBE),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TerrainTex",
		Engine::BUFFER_TERRAINTEX,
		129,
		129,
		1),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_LandTex",
		Engine::BUFFER_LANDTEX,
		129,
		129,
		1000),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"Sprite_Bat",
		Engine::SPRITE_ANIM,
		9,
		6),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_TERRAIN",
		Engine::BUFFER_FOREST),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_KOREA",
		Engine::BUFFER_KOREA,
		129,
		129,
		100),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_SKYSPHERE",
		Engine::BUFFER_SKYSPHERE),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_CAVECYLINDER",
		Engine::BUFFER_CAVECYLINDER),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_CLIFFCYLINDER",
		Engine::BUFFER_RIFT),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_VENTCUBE",
		Engine::BUFFER_VENTCUBE),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_OBSTACLECUBE",
		Engine::BUFFER_OBSTACLECUBE),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_CUBEDRA",
		Engine::BUFFER_CUBEDRA),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_ROCKMESH",
		Engine::BUFFER_ROCKMESH),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_DIAMESH",
		Engine::BUFFER_DIAMESH),
		E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_CHRYSTAL",
		Engine::BUFFER_CHRYSTAL),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_TREEMESH",
		Engine::BUFFER_TREEMESH),
		E_FAIL);

	lstrcpy(m_szFinish, L"Texture Loading............");

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Terrain",
		Engine::TEX_NORMAL,
		L"../Bin/Resource/Texture/Terrain/Terrain0.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_SkySphere",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/TestSkybox.dds"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Bat",
		Engine::TEX_NORMAL,
		L"../../Asset/Monster/CaveBat/%d.png" , 8),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BoxHead",
		Engine::TEX_NORMAL,
		L"../../Asset/HeadPng/Head%d.png", 6),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Portal",
		Engine::TEX_NORMAL,
		L"../../Asset/Portal/%d.png", 10),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_OCEAN",
		Engine::TEX_NORMAL,
		L"../../Asset/Terrain/water.bmp"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_VENT",
		Engine::TEX_NORMAL,
		L"../../Asset/Environment/Passage.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_OBS",
		Engine::TEX_NORMAL,
		L"../../Asset/Environment/Passage_Through.png"),
		E_FAIL);

	// せせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせ

	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_BLACK",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Black.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_WHITE",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_White.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_EMERALD",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Emerald.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_ORANGE",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Orange.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_PURPLE",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Purple.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_DARKBLUE",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Darkblue.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_SKYBLUE",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Skyblue.png"),
		E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_RED",
		Engine::TEX_NORMAL,
		L"../../Asset/Mask/Mask_Red.png"),
		E_FAIL);

	// せせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせ



	CIngame_Flow::GetInstance()->Load_ForestTerrain();
	CIngame_Flow::GetInstance()->Load_TreeList();
	CIngame_Flow::GetInstance()->Init_Mask();

	lstrcpy(m_szFinish, L"Loading Complete");

	m_bFinish = true;

	return 0;
}

unsigned int CALLBACK CScene_Loading::Thread_Main(void* pArg)
{
	CScene_Loading*		pLoading = (CScene_Loading*)pArg;

	_uint iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());
	
	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;

	case LOADING_BOSS:
		
		break;

	default:
		break;
	}
	
	LeaveCriticalSection(pLoading->Get_Crt());
	_endthreadex(0);

	return iFlag;
}

CScene_Loading* CScene_Loading::Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::LOADINGID eLoading)
{
	CScene_Loading*	pInstance = new CScene_Loading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eLoading)))
		Safe_Release(pInstance);

	return pInstance;
}

void CScene_Loading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}

