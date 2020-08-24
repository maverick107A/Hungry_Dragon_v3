#include "stdafx.h"
#include "MainApp.h"

//-------------------------------------------------------
//스테이지 헤더******************************************
//-------------------------------------------------------
//여기에 스테이지 헤더파일 추가
#include "Logo.h"

#ifdef _DEBUG		// 테스트용입니다.
#include "Scene_Monster.h"

#endif // _DEBUG




//-------------------------------------------------------
//매니저 헤더********************************************
//-------------------------------------------------------
//여기에 매니저 헤더 추가
#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Ingame_Info.h"

//-------------------------------------------------------
//기타 헤더**********************************************
//-------------------------------------------------------
//여기에 기타 헤더 추가


//-------------------------------------------------------

CMainApp::CMainApp(void)
{

}

CMainApp::~CMainApp(void)
{

}

HRESULT CMainApp::Ready_MainApp(void)
{
	srand((unsigned int)time(NULL));
	Set_DefaultSetting(&m_pGraphicDev);
	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);
	Engine::Load_Particle(m_pGraphicDev);
	CIngame_Flow::GetInstance()->Init_Flow(m_pGraphicDev, m_pDeviceClass->GetSprite());

	

	return S_OK;
}

Engine::_int CMainApp::Update_MainApp(const Engine::_float& fTimeDelta)
{
	Engine::Get_FMOD()->Update();
	Engine::Set_InputDev();
	Engine::Get_KeyMgr()->Key_UpdateByDinput();
	CIngame_Flow::GetInstance()->Update_BeforeScene(fTimeDelta);

	
	if (CIngame_Flow::GetInstance()->Get_IngamePause())
	{
		CIngame_Info::GetInstance()->Update_Frame();
	}
	else
	{
		m_pManagementClass->Update_Scene(fTimeDelta);
	}
	
	CIngame_Flow::GetInstance()->Update_AfterScene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp(const Engine::_float & fTimeDelta) {
	CIngame_Flow::GetInstance()->LateUpdate_BeforeScene(fTimeDelta);

	
	if (CIngame_Flow::GetInstance()->Get_IngamePause())
	{
		
	}
	else
	{
		m_pManagementClass->LateUpdate_Scene(fTimeDelta);
	}

	CIngame_Flow::GetInstance()->LateUpdate_AfterScene(fTimeDelta);

}

void CMainApp::Render_MainApp(void)
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	CIngame_Flow::GetInstance()->Render_BeforeScene();
	m_pManagementClass->Render_Scene();
	CIngame_Flow::GetInstance()->Render_AfterScene();

	if (CIngame_Flow::GetInstance()->Get_IngamePause())
	{
		CIngame_Info::GetInstance()->Render_Frame();
	}

	Engine::Render_End();

	// 그릴거 다 그리고 맨 마지막에 이벤트 갱신
	CIngame_Flow::GetInstance()->Update_Event();
}

HRESULT CMainApp::Set_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd,
		Engine::MODE_WIN,
		WINCX,
		WINCY,
		&m_pDeviceClass),
		E_FAIL);

	m_pDeviceClass->AddRef();
		
	(*ppGraphicDev) = m_pDeviceClass->GetDevice();
	(*ppGraphicDev)->AddRef();

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 폰트 자동 설치
	int i = AddFontResource(L"../../Asset/Font/Maplestory Bold.ttf");
	AddFontResource(L"../../Asset/Font/Maplestory Light.ttf");
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Default", L"바탕", 60, 60, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Jinji", L"궁서", 30, 30, FW_THIN), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Bold", L"메이플스토리", 30, 30, FW_BOLD), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_BoldBig", L"메이플스토리", 50, 50, FW_BOLD), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Light", L"메이플스토리", 30, 30, FW_THIN), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);
	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, 
							Engine::CManagement ** ppManagementInstance)
{
	Engine::CScene*		pScene = nullptr;

	FAILED_CHECK_RETURN(Engine::Create_Management(ppManagementInstance), E_FAIL);
	(*ppManagementInstance)->AddRef();

	pScene = CLogo::Create(pGraphicDev);
	//pScene = CScene_PT::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	return S_OK;
}

CMainApp* CMainApp::Create(void)
{
	CMainApp*	pInstance = new CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
			Engine::Safe_Release(pInstance);
	
	return pInstance;
}

void CMainApp::Free(void)
{
	// 폰트 자동 삭제
	RemoveFontResource(L"../../Asset/Font/Maplestory Bold.ttf");
	RemoveFontResource(L"../../Asset/Font/Maplestory Light.ttf");
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	CIngame_Info::DestroyInstance();
	CIngame_Flow::GetInstance()->Release_AllResources();
	CIngame_Flow::DestroyInstance();

	Engine::Safe_Release(m_pGraphicDev);

	Engine::Safe_Release(m_pDeviceClass);
	Engine::Safe_Release(m_pManagementClass);

	Engine::Release_Utility();
	Engine::Release_Resources();
	Engine::Release_System();
}

