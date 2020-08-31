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
	lstrcpy(m_szFinish, L"버텍스 찍는 중...");

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
		L"BUFFER_TORUS",
		Engine::BUFFER_TORUS),
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

	//플레이어 이미지
	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_FACE",
		Engine::BUFFER_FACE),
		E_FAIL);

	//FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
	//	RESOURCE_STATIC,
	//	L"BUFFER_FACE",
	//	Engine::BUFFER_TWINFACE),
	//	E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_JAW",
		Engine::BUFFER_JAW),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_BODY",
		Engine::BUFFER_BODY),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_WING",
		Engine::BUFFER_WING),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_LWING",
		Engine::BUFFER_LWING),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEXTURE_OUTLINE",
		Engine::TEX_NORMAL,
		L"../../Asset/PlayerOutLine/OutLine.png", 1),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_OUTLINE",
		Engine::BUFFER_OUTLINE,
		9,
		6),
		E_FAIL);
	//

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

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STAGE,
		L"BUFFER_STUMPMESH",
		Engine::BUFFER_STUMPMESH),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_DIAMOB_UPPER",
		Engine::BUFFER_DIAMOB_UPPER),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_DIAMOB_UNDER",
		Engine::BUFFER_DIAMOB_UNDER),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_GOLEMBODY",
		Engine::BUFFER_GOLEMBODY),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_LEFTHAND",
		Engine::BUFFER_LEFTHAND),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_RIGHTHAND",
		Engine::BUFFER_RIGHTHAND),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"FLYMOB_BODY",
		Engine::FLYMOB_BODY),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"FLYMOB_WL",
		Engine::FLYMOB_WL),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"FLYMOB_WR",
		Engine::FLYMOB_WR),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_RABBIT",
		Engine::BUFFER_RABBIT),
		E_FAIL);
	

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_PIG",
		Engine::BUFFER_PIG),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_BOMB",
		Engine::BUFFER_BOMB),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(m_pGraphicDev,
		RESOURCE_STATIC,
		L"BUFFER_TREASURE",
		Engine::BUFFER_TREASURE),
		E_FAIL);
	

	lstrcpy(m_szFinish, L"이미지 읽는 중...");

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_SkySphere",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/TestSkybox.dds"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_RedSkySphere",
		Engine::TEX_CUBE,
		L"../../Asset/Skybox/RedSkybox.dds"),
		E_FAIL);

	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_MonsterBeam",
		Engine::TEX_NORMAL,
		L"../../Asset/MonsterBeam/%d.png" , 3),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Bat",
		Engine::TEX_NORMAL,
		L"../../Asset/Monster/CaveBat/%d.png", 8),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_HrizonBat",
		Engine::TEX_NORMAL,
		L"../../Asset/Monster/CaveHrizonBat/%d.png", 26),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Test_Aura",
		Engine::TEX_NORMAL,
		L"../../Asset/Aura/%d.png", 60),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Posion",
		Engine::TEX_NORMAL,
		L"../../Asset/Monster/Poison/%d.png", 13),
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
		L"Texture_Blur",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Blur/TestBlur00%.2d.png", 30),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Boom",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Boom/Boom00%.2d.png", 6),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Meteor",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Meteor/Meteor00%.2d.png", 16),
		E_FAIL);

	

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_LOGO,
		L"Texture_Breath",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Breath/Breath00%.2d.png", 24),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Erupt",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Erupt/erupt00%.2d.png", 44),
		E_FAIL);

	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_FireEmblem",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/FireEmblem/Fireemblem00%.2d.png", 72),
		E_FAIL);*/

	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_FireRing",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Firering/firering00%.2d.png", 38),
		E_FAIL);*/

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_FireWall",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Firewall/Firewall00%.2d.png", 38),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_SceneChange",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/SceneChange/SceneChange00%.2d.png", 76),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BillCloud",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Cloud/billcloud%.2d.png", 3),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BillDot",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/Dot/dot.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_GageBar",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/gagebar%.2d.png", 6),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_DelayBar",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/delaybar%.2d.png", 6),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_BlankBar",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/blankbar.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_HudIcon",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/hudicon%.2d.png", 6),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Compass",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/compass.png"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"Texture_Indicator",
		Engine::TEX_NORMAL,
		L"../../Asset/HUD/indicator.png"),
		E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_OCEAN",
		Engine::TEX_NORMAL,
		L"../../Asset/Terrain/water.bmp"),
		E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_STAGE,
		L"TEX_LAVA",
		Engine::TEX_NORMAL,
		L"../../Asset/Terrain/lava.png"),
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


	


	FAILED_CHECK_RETURN(Engine::Ready_Texture(m_pGraphicDev,
		RESOURCE_LOGO,
		L"Texture_SelectMap",
		Engine::TEX_NORMAL,
		L"../../Asset/Billboard/SelectedMap/select_map%.2d.png", 10),
		E_FAIL);



	
	// 마스크
	{

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
	}
	// 마스크


	lstrcpy(m_szFinish, L"사운드 추가 중...");
	// 사운드
	// 배경음악
	Engine::Get_FMOD()->Initialize();
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Red_Dragon.mp3", L"MenuBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Dragon_Rises.mp3", L"SelectBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Sunshine_Coastline.mp3", L"ForestBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Night_Survivor.mp3", L"CaveBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Flower_Valley.mp3", L"CloudBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Scrap_Valley_Entry.mp3", L"VolcanoBgm");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Devil's Pit.mp3", L"Devil's Pit");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/Infinite Azure.mp3", L"Infinite Azure");
	Engine::Get_FMOD()->Insert_Bgm("../../Asset/Sound/Bgm/VACANT INTERFERENCE.mp3", L"VACANT INTERFERENCE");
	// 효과음
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/mouse_on.mp3", L"MouseOn");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/breath_test.mp3", L"BreathTest");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/long_breath.mp3", L"long_breath");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Fragile0.mp3", L"Fragile0");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Fragile1.mp3", L"Fragile1");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Fragile2.mp3", L"Fragile2");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Fragile3.mp3", L"Fragile3");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/flight_once.mp3", L"FlightOnce");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/break.mp3", L"break");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/die1.mp3", L"rabbit_die");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/die2.mp3", L"pig_die");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/die3.mp3", L"bat_die1");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/die4.mp3", L"bat_die2");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/die5.mp3", L"bat_die3");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/bite.mp3", L"bite");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/tree_crash.mp3", L"tree_crash");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/earthquake.mp3", L"earthquake");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/RingThrough.wav", L"RingThrough");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Breath2.wav", L"Breath");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Treasure.wav", L"Treasure");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Bound.wav", L"Bound");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Kick.wav", L"Kick");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/LavaBurn.wav", L"LavaBurn");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/LavaBurnLong.mp3", L"LavaBurnLong");
	Engine::Get_FMOD()->Insert_Sfx("../../Asset/Sound/Sfx/Takeon.wav", L"Takeon");




	lstrcpy(m_szFinish, L"지형 찍는 중...");

	CIngame_Flow::GetInstance()->Load_ForestTerrain();

	lstrcpy(m_szFinish, L"나무 까는 중...");

	CIngame_Flow::GetInstance()->Load_TreeList();
	CIngame_Flow::GetInstance()->Init_Mask();

	lstrcpy(m_szFinish, L"게임이 시작됩니다!");

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

