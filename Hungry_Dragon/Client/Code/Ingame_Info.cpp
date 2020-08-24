#include "stdafx.h"
#include "Ingame_Info.h"
#include "Export_Function.h"
#include "BarCon.h"
#include "IconCon.h"
#include "CompassCon.h"
#include "Ingame_Flow.h"
#include "PlayerMain.h"

USING(Engine)

IMPLEMENT_SINGLETON(CIngame_Info)



CIngame_Info::CIngame_Info(void)
{
}


CIngame_Info::CIngame_Info(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
}

CIngame_Info::~CIngame_Info(void)
{
	Safe_Release(m_pSprite);
	Safe_Release(m_pBarCon);
	Safe_Release(m_pIconCon);
	Safe_Release(m_pCompass);
	Safe_Release(m_pTexBar);
	Safe_Release(m_pIndicator);
	Safe_Release(m_pMainFrame);
	Safe_Release(m_pBtnFrame);
	Safe_Release(m_pBtnFrameFocus);
	for (int i = 0; i < 4; ++i)
	{
		Safe_Release(m_pBuffFrame[i]);
	}
	Safe_Release(m_pBubble);
}

void CIngame_Info::Init_Info(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;

	D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	
	m_tPlayerStatus.fHp			= 100.f;
	m_tPlayerStatus.fDelay_Hp	= 100.f;
	m_tPlayerStatus.fMax_Hp		= 100.f;
				   
	m_tPlayerStatus.fStage		= 0.f;  
	m_tPlayerStatus.fMax_Stage	= 100.f;
				   
	m_tPlayerStatus.fSp			= 0.f;
	m_tPlayerStatus.fDelay_Sp	= 100.f;
	m_tPlayerStatus.fMax_Sp		= 100.f;
				   
	m_tPlayerStatus.fMp			= 50.f;
	m_tPlayerStatus.fDelay_Mp	= 100.f;
	m_tPlayerStatus.fMax_Mp		= 100.f;

	m_tPlayerGoods.uPolygons = 100;
	m_tPlayerGoods.uDelay_Polygons = 0;

	//FAILED_CHECK(Clone_Compon)
	m_pBarCon = CBarCon::Create(m_pGraphicDev);
	m_pIconCon = CIconCon::Create(m_pGraphicDev);
	m_pCompass = CCompassCon::Create(m_pGraphicDev);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/blankbar.png", &m_pTexBar);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/indicator.png", &m_pIndicator);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/UI_Frame.png", &m_pMainFrame);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/BtnFrame.png", &m_pBtnFrame);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/BtnFrameFocus.png", &m_pBtnFrameFocus);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/MainMark.png", &m_pBubble);
	
	TCHAR str[64] = L"";
	for (int i = 0; i < 4; ++i)
	{
		wsprintf(str,L"../../Asset/HUD/BuffIcon%.2d.png", i);
		D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_pBuffFrame[i]);
	}
	

}

void CIngame_Info::Update_Info(const Engine::_float & _fTimeDelta)
{
	if (m_tPlayerStatus.fHp < m_tPlayerStatus.fDelay_Hp)
	{
		m_tPlayerStatus.fDelay_Hp -= 20.f*_fTimeDelta;
	}
	else
	{
		m_tPlayerStatus.fDelay_Hp = m_tPlayerStatus.fHp;
	}

	if (100.f <= m_tPlayerStatus.fStage)
	{
		m_bStageClear = true;
	}

	if (m_tPlayerStatus.fMp < m_tPlayerStatus.fDelay_Mp)
	{
		m_tPlayerStatus.fDelay_Mp -= 20.f*_fTimeDelta;
	}
	else
	{
		m_tPlayerStatus.fDelay_Mp = m_tPlayerStatus.fMp;
	}
	
	if (m_bChargeReadySp)
	{
		if (m_tPlayerStatus.fSp < m_tPlayerStatus.fDelay_Sp)
		{
			m_tPlayerStatus.fDelay_Sp -= 20.f*_fTimeDelta;
		}
	}
	else
	{
		m_tPlayerStatus.fDelay_Sp = m_tPlayerStatus.fSp;
	}

	if (m_tPlayerGoods.uPolygons > m_tPlayerGoods.uDelay_Polygons)
	{
		++m_tPlayerGoods.uDelay_Polygons;
	}
	else
	{
		m_tPlayerGoods.uDelay_Polygons = m_tPlayerGoods.uPolygons;
	}



	m_tPlayerStatus.fHp = CIngame_Flow::GetInstance()->Get_PlayerObject()->Get_Hp();
	m_tPlayerStatus.fMp = CIngame_Flow::GetInstance()->Get_PlayerObject()->Get_Mana();
	m_tPlayerStatus.fSp = CIngame_Flow::GetInstance()->Get_PlayerObject()->Get_Stamina();



	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		CIngame_Flow::GetInstance()->Set_IngamePause(!CIngame_Flow::GetInstance()->Get_IngamePause());
		m_uFocusDepth = 0;
		m_uMainFocus = 0;
		m_uSubFocus = 0;
	}

}

void CIngame_Info::Render_UI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	TCHAR str[32];
	
	// 나침반
	_vec3 vLook;
	CIngame_Flow::GetInstance()->Get_PlayerObject()->Get_Transform()->Get_Info(INFO_LOOK, &vLook);
	vLook.y = 0.f;
	D3DXVec3Normalize(&vLook, &vLook);
	float fDotUp = D3DXVec3Dot(&vLook, &_vec3(0.f, 0.f, 1.f));
	float fDotRight = D3DXVec3Dot(&vLook, &_vec3(1.f, 0.f, 0.f));
	float fAngle = acosf(fDotUp) * 180.f / D3DX_PI;
	if (0.f > fDotRight)
	{
		fAngle = 360.f - fAngle;
	}
	fAngle /= 360.f;
	fAngle *= 4096.f;

	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (5696.f - fAngle)*0.5f, 0.f);
	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (1600.f - fAngle)*0.5f, 0.f);
	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (-2496.f - fAngle)*0.5f, 0.f);

	Draw_Tex(m_pIndicator, 128, 128, 0.1f, 0.1f, 793.6f, 0.f);

	wsprintf(str, L"각도 : %d", (int)fAngle);
	Engine::Render_Font(L"Font_Light", str, &_vec2(800.f, 100.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	// 좌상측 UI
	float _fRectY = 0.3f;


	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 160.f, 50.f);
	Draw_Tex(m_pBarCon->Get_Texture(0), 1024 * m_tPlayerStatus.fHp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 160.f, 50.f);
	Draw_Tex(m_pBarCon->Get_Texture(0), 1024* m_tPlayerStatus.fDelay_Hp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 160.f, 50.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	

	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 160.f, 80.f);
	Draw_Tex(m_pBarCon->Get_Texture(1), 1024 * m_tPlayerStatus.fMp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 160.f, 80.f);
	Draw_Tex(m_pBarCon->Get_Texture(1), 1024* m_tPlayerStatus.fDelay_Mp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 160.f, 80.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	

	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 160.f, 110.f);
	Draw_Tex(m_pBarCon->Get_Texture(2), 1024 * m_tPlayerStatus.fSp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 160.f, 110.f);
	Draw_Tex(m_pBarCon->Get_Texture(2), 1024 * m_tPlayerStatus.fDelay_Sp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 160.f, 110.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	

	Draw_Tex(m_pBubble, 512, 512, 0.4f, 0.4f, 20.f, 0.f);

	Draw_Tex(m_pIconCon->Get_Texture(0), 512, 512, 0.04f, 0.04f, 183.f, 58.f);
	Draw_Tex(m_pIconCon->Get_Texture(1), 512, 512, 0.04f, 0.04f, 188.f, 88.f);
	Draw_Tex(m_pIconCon->Get_Texture(2), 512, 512, 0.04f, 0.04f, 183.f, 120.f);

	

	Draw_Tex(m_pTexBar, 1024, 128, 1.f, _fRectY, 300.f, 850.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBarCon->Get_Texture(4), 1024* m_tPlayerStatus.fStage * 0.01f, 128, 1.f, _fRectY, 300.f, 850.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	Draw_Tex(m_pIconCon->Get_Texture(3), 512, 512, 0.05f, 0.05f, 50.f, 180.f);
	wsprintf(str, L"%d", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 180.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(4), 512, 512, 0.05f, 0.05f, 50.f, 210.f);
	wsprintf(str, L"포인트 자리", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 210.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(5), 512, 512, 0.05f, 0.05f, 50.f, 240.f);
	wsprintf(str, L"시간 자리", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 240.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));


	Draw_Tex(m_pBuffFrame[0], 256, 256, 0.5f, 0.5f, 50.f, 280.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[1], 256, 256, 0.5f, 0.5f, 50.f, 430.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[2], 256, 256, 0.5f, 0.5f, 50.f, 580.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[3], 256, 256, 0.5f, 0.5f, 50.f, 730.f, D3DCOLOR_ARGB(155, 255, 255, 255));


	m_pSprite->End();

}


void CIngame_Info::Update_Frame()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		switch (m_uFocusDepth)
		{
		case 0:
			++m_uMainFocus;
			if (3 < m_uMainFocus)
			{
				m_uMainFocus = 3;
			}
			break;
		case 1:
			switch (m_uMainFocus)
			{
			case 0:
				
				break;
			case 1:

				break;
			case 2:
				++m_uSubFocus;
				if (4 < m_uSubFocus)
				{
					m_uSubFocus = 4;
				}
				break;
			}
			break;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		switch (m_uFocusDepth)
		{
		case 0:
			--m_uMainFocus;
			if (3 < m_uMainFocus)
			{
				m_uMainFocus = 0;
			}

			break;
		case 1:
			switch (m_uMainFocus)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:
				--m_uSubFocus;
				if (4 < m_uSubFocus)
				{
					m_uSubFocus = 3;
				}
				break;
			}
			break;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		switch (m_uFocusDepth)
		{
		case 0:
			break;
		case 1:
			switch (m_uMainFocus)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:
				switch (m_uSubFocus)
				{
				case 0:
					Get_FMOD()->Add_BgmVolume(-0.1f);
					break;
				case 1:
					Get_FMOD()->Add_SfxVolume(-0.1f);
					break;
				case 2:

					break;
				}
				break;
			}
			break;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		switch (m_uFocusDepth)
		{
		case 0:
			break;
		case 1:
			switch (m_uMainFocus)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:
				switch (m_uSubFocus)
				{
				case 0:
					Get_FMOD()->Add_BgmVolume(0.1f);
					break;
				case 1:
					Get_FMOD()->Add_SfxVolume(0.1f);
					break;
				case 2:

					break;
				}
				break;
			}
			break;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		switch (m_uFocusDepth)
		{
		case 0:
			if (m_uMainFocus == 3)
			{
				m_uFocusDepth = 0;
				m_uMainFocus = 0;
				m_uSubFocus = 0;
				CIngame_Flow::GetInstance()->Set_IngamePause(false);
				return;
			}
			++m_uFocusDepth;
			break;
		case 1:
			switch (m_uMainFocus)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:
				switch (m_uSubFocus)
				{
				case 3:
					CIngame_Flow::GetInstance()->Change_SceneTo(SCENENUM::SCENE_MENU);
					m_uFocusDepth = 0;
					m_uMainFocus = 0;
					m_uSubFocus = 0;
					CIngame_Flow::GetInstance()->Set_IngamePause(false);
					break;
				case 4:
					--m_uFocusDepth;
					m_uSubFocus = 0;
					if (3 < m_uFocusDepth)
					{
						m_uFocusDepth = 0;
					}
					break;
				}
				
				break;
			case 3:
				
				break;
			}
			break;
		case 2:

			break;
		case 3:

			break;
		}
	}
	if (GetAsyncKeyState(VK_BACK) & 0x0001)
	{
		--m_uFocusDepth;
		if (3 < m_uFocusDepth)
		{
			m_uFocusDepth = 0;
		}
	}

}

void CIngame_Info::Render_Frame()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	TCHAR str[32] = L"";
	TCHAR sub_str[128] = L"";

	D3DXMATRIX matScale, matWorld, matIdentity;
	D3DXMatrixIdentity(&matIdentity);

	Draw_Tex(m_pMainFrame, 800.f, 450.f, 0.f, 0.7f, 0.7f, 650.f, 400.f);

	switch (m_uFocusDepth)
	{
	case 0:

		wsprintf(str, L"메뉴");
		D3DXMatrixScaling(&matScale, 1.6f, 1.6f, 1.f);
		m_pSprite->SetTransform(&matScale);
		Engine::Draw_Font_Center(m_pSprite, L"Font_BoldBig", str, &_vec2(1000.f, 100.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

		Draw_Tex(m_pBtnFrame, 256, 64, 1.f, 1.f, 670.f, 320.f);
		Draw_Tex(m_pBtnFrame, 256, 64, 1.f, 1.f, 670.f, 440.f);
		Draw_Tex(m_pBtnFrame, 256, 64, 1.f, 1.f, 670.f, 560.f);
		Draw_Tex(m_pBtnFrame, 256, 64, 1.f, 1.f, 670.f, 680.f);

		wsprintf(str, L"캐릭터");
		m_pSprite->SetTransform(&matIdentity);
		Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 340.f), D3DXCOLOR(1.f, 1.f, 1.f, 0.6f));
		wsprintf(str, L"스킬");
		m_pSprite->SetTransform(&matIdentity);
		Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 460.f), D3DXCOLOR(1.f, 1.f, 1.f, 0.6f));
		wsprintf(str, L"옵션");
		m_pSprite->SetTransform(&matIdentity);
		Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 580.f), D3DXCOLOR(1.f, 1.f, 1.f, 0.6f));
		wsprintf(str, L"나가기");
		m_pSprite->SetTransform(&matIdentity);
		Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 700.f), D3DXCOLOR(1.f, 1.f, 1.f, 0.6f));

		switch (m_uMainFocus)
		{
		case 0:
			Draw_Tex(m_pBtnFrameFocus, 256, 64, 1.f, 1.f, 670.f, 320.f);
			wsprintf(str, L"캐릭터");
			m_pSprite->SetTransform(&matIdentity);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 340.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		case 1:
			Draw_Tex(m_pBtnFrameFocus, 256, 64, 1.f, 1.f, 670.f, 440.f);
			wsprintf(str, L"스킬");
			m_pSprite->SetTransform(&matIdentity);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 460.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		case 2:
			Draw_Tex(m_pBtnFrameFocus, 256, 64, 1.f, 1.f, 670.f, 560.f);
			wsprintf(str, L"옵션");
			m_pSprite->SetTransform(&matIdentity);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 580.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		case 3:
			Draw_Tex(m_pBtnFrameFocus, 256, 64, 1.f, 1.f, 670.f, 680.f);
			wsprintf(str, L"나가기");
			m_pSprite->SetTransform(&matIdentity);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1600.f, 700.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		}


		


		break;
	case 1:
		switch (m_uMainFocus)
		{
		case 0:
			wsprintf(str, L"캐릭터");

			break;
		case 1:
			wsprintf(str, L"스킬");

			break;
		case 2:
			wsprintf(str, L"옵션");
			m_pSprite->SetTransform(&matIdentity);

			wsprintf(sub_str, L"사운드");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 300.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"배경음 : %.2d", (int)(Get_FMOD()->Get_BgmVolume()*10.f));
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 350.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"효과음 : %.2d", (int)(Get_FMOD()->Get_SfxVolume()*10.f));
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 400.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"조작");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 500.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"마우스 감도 : %d", 0);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 550.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

			wsprintf(sub_str, L"종료", 0);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 650.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

			wsprintf(sub_str, L"확인", 0);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 700.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

			switch (m_uSubFocus)
			{
			case 0:
				wsprintf(sub_str, L"사운드");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 300.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				wsprintf(sub_str, L"◀ 배경음 : %.2d ▶", (int)(Get_FMOD()->Get_BgmVolume()*10.f));
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 350.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				break;
			case 1:
				wsprintf(sub_str, L"사운드");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 300.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				wsprintf(sub_str, L"◀ 효과음 : %.2d ▶", (int)(Get_FMOD()->Get_SfxVolume()*10.f));
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 400.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				break;
			case 2:
				wsprintf(sub_str, L"조작");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 500.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				wsprintf(sub_str, L"◀ 마우스 감도 : %d ▶", 0);
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 550.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				break;
			case 3:
				wsprintf(sub_str, L"▶ 종료 ◀", 0);
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 650.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				break;
			case 4:
				wsprintf(sub_str, L"▶ 확인 ◀", 0);
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 700.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				break;
			}


			break;
		}
		D3DXMatrixScaling(&matScale, 1.6f, 1.6f, 1.f);
		m_pSprite->SetTransform(&matScale);
		Engine::Draw_Font_Center(m_pSprite, L"Font_BoldBig", str, &_vec2(1000.f, 100.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		break;
	case 2:
		switch (m_uMainFocus)
		{
		case 0:
			wsprintf(str, L"캐릭터");
			Engine::Draw_Font_Center(m_pSprite, L"Font_BoldBig", str, &_vec2(400.f, -350.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		case 1:
			wsprintf(str, L"스킬");
			Engine::Draw_Font_Center(m_pSprite, L"Font_BoldBig", str, &_vec2(400.f, -350.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		case 2:
			wsprintf(str, L"옵션");
			Engine::Draw_Font_Center(m_pSprite, L"Font_BoldBig", str, &_vec2(400.f, -350.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			break;
		}
		break;
	case 3:

		break;
	}

	m_pSprite->End();

	
}

void CIngame_Info::Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, float _fCenterX, float _fCenterY, float _fCenterZ, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	D3DXMatrixScaling(&matScale, _fScaleX, _fScaleY, 0.f);
	D3DXMatrixTranslation(&matTrans, _fPosX, _fPosY, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(_pTex, nullptr, &_vec3(_fCenterX, _fCenterY, _fCenterZ), nullptr, _dwColor);
}

void CIngame_Info::Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	RECT tRect = { 0,0,_iRectX,_iRectY };
	D3DXMatrixScaling(&matScale, _fScaleX, _fScaleY, 0.f);
	D3DXMatrixTranslation(&matTrans, _fPosX, _fPosY, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(_pTex, &tRect, nullptr, nullptr, _dwColor);
}

void CIngame_Info::Draw_Tex(IDirect3DBaseTexture9* _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	RECT tRect = { 0,0,_iRectX,_iRectY };
	D3DXMatrixScaling(&matScale, _fScaleX, _fScaleY, 0.f);
	D3DXMatrixTranslation(&matTrans, _fPosX, _fPosY, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw((LPDIRECT3DTEXTURE9)_pTex, &tRect, nullptr, nullptr, _dwColor);
}

void CIngame_Info::Draw_TexPart(IDirect3DBaseTexture9 * _pTex, int _iPivotX, int _iPivotY, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	RECT tRect = { _iPivotX,_iPivotY,_iRectX,_iRectY };
	D3DXMatrixScaling(&matScale, _fScaleX, _fScaleY, 0.f);
	D3DXMatrixTranslation(&matTrans, _fPosX, _fPosY, 0.f);
	matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw((LPDIRECT3DTEXTURE9)_pTex, &tRect, nullptr, nullptr, _dwColor);
}
