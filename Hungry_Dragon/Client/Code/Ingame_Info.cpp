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
	Safe_Release(m_pPolygon);
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
	m_tPlayerGoods.uGame_Point = 0;

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
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/polygon.png", &m_pPolygon);
	
	TCHAR str[64] = L"";
	for (int i = 0; i < 4; ++i)
	{
		wsprintf(str,L"../../Asset/HUD/BuffIcon%.2d.png", i);
		D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_pBuffFrame[i]);
	}
	
	m_vDestination[0] = _vec3(50.f, 720.f, 0.f);
	m_vDestination[1] = _vec3(50.f, 620.f, 0.f);
	m_vDestination[2] = _vec3(50.f, 470.f, 0.f);
	m_vDestination[3] = _vec3(50.f, 320.f, 0.f);
	m_vDestination[4] = _vec3(50.f, 170.f, 0.f);

}

void CIngame_Info::Update_Info(const Engine::_float & _fTimeDelta)
{
	m_fTimeTick += _fTimeDelta;
	for (_uint i = 0; i < Get_EventMgr()->Get_EventCount(); ++i)
	{
		ENGINE_EVENT tEvent = Get_EventMgr()->Pop_Event();
		Push_EngineEvent(tEvent);
	}

	Update_BuffPack(_fTimeDelta);
	Update_FontPack(_fTimeDelta);

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



	if (Get_KeyMgr()->Key_Down(KM_TAB))
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

	/*wsprintf(str, L"각도 : %d", (int)fAngle);
	Engine::Render_Font(L"Font_Light", str, &_vec2(800.f, 100.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));*/
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
	wsprintf(str, L"%d", m_tPlayerGoods.uGame_Point);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 210.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(5), 512, 512, 0.05f, 0.05f, 50.f, 240.f);
	wsprintf(str, L"%.2d : %.2d : %.2d", int(m_fTimeTick) / 60, int(m_fTimeTick) % 60, int(m_fTimeTick*100.f)%100);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 240.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));


	Draw_Tex(m_pBuffFrame[0], 256, 256, 0.5f, 0.5f, 50.f, 280.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[1], 256, 256, 0.5f, 0.5f, 50.f, 430.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[2], 256, 256, 0.5f, 0.5f, 50.f, 580.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBuffFrame[3], 256, 256, 0.5f, 0.5f, 50.f, 730.f, D3DCOLOR_ARGB(155, 255, 255, 255));



	for (auto& tPack : m_listBuffPack)
	{
		Draw_Tex(m_pPolygon, 128, 128, tPack.vScale.x, tPack.vScale.y, 0.f,0.f, tPack.vRot.z, tPack.vPos.x, tPack.vPos.y, tPack.dwColor);
		//Draw_Tex(m_pPolygon, 128, 128, tPack.vScale.x, tPack.vScale.y, tPack.vPos.x, tPack.vPos.y, tPack.dwColor);
	}

	for (auto& tPack : m_listFontPack)
	{
		wsprintf(str, L"+%d", (int)(tPack.tEvent.uDataNum));
		Engine::Render_Font(L"Font_Light", str, &_vec2(2.f * tPack.vPos.x, tPack.vPos.y), tPack.tColor);
		//Engine::Render_Font(L"Font_Light", str, &_vec2(400.f, 200.f), tPack.tColor);
	}


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
				++m_uSubFocus;
				if (5 < m_uSubFocus)
				{
					m_uSubFocus = 0;
				}
				break;
			case 1:

				break;
			case 2:
				++m_uSubFocus;
				if (4 < m_uSubFocus)
				{
					m_uSubFocus = 0;
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
				--m_uSubFocus;
				if (5 < m_uSubFocus)
				{
					m_uSubFocus = 4;
				}
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
				switch (m_uSubFocus)
				{
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

		wsprintf(str, L"업그레이드");
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
			wsprintf(str, L"업그레이드");
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
			wsprintf(str, L"업그레이드");

			m_pSprite->SetTransform(&matIdentity);

			wsprintf(sub_str, L"허기");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 300.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"폐활량");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 400.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"지구력");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 500.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"추진력");
			Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 600.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			wsprintf(sub_str, L"확인", 0);
			Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 700.f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
			switch (m_uSubFocus)
			{
			case 0:
				wsprintf(sub_str, L"◀ 허기 ▶");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 300.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				break;
			case 1:
				wsprintf(sub_str, L"◀ 폐활량 ▶");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 400.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				break;
			case 2:
				wsprintf(sub_str, L"◀ 지구력 ▶");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 500.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				break;
			case 3:
				wsprintf(sub_str, L"◀ 추진력 ▶");
				Engine::Draw_Font_Center(m_pSprite, L"Font_Bold", sub_str, &_vec2(1600.f, 600.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				break;
			case 4:
				wsprintf(sub_str, L"▶ 확인 ◀", 0);
				Engine::Draw_Font_Center(m_pSprite, L"Font_Light", sub_str, &_vec2(1600.f, 700.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				break;
			}
			break;
		case 1:
			wsprintf(str, L"스킬");
			m_pSprite->SetTransform(&matIdentity);
			

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
			wsprintf(str, L"업그레이드");
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

void CIngame_Info::Push_EngineEvent(ENGINE_EVENT _tEvent)
{
	BUFFPACK tPack;

	switch (_tEvent.uEventNum)	// 버프팩 생성
	{
	case 0:
		tPack.dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);
		break;
	case 1:
		tPack.dwColor = D3DCOLOR_ARGB(255, 0, 128, 255);
		break;
	case 2:
		tPack.dwColor = D3DCOLOR_ARGB(255, 128, 128, 0);
		break;
	case 3:
		tPack.dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);
		break;
	case 4:
		tPack.dwColor = D3DCOLOR_ARGB(255, 128 + (rand() % 128), 128 + (rand() % 128), 128 + (rand() % 128));
		break;
	}
	_uint uDataAccum = _tEvent.uDataNum;
	while (uDataAccum != 0)
	{
		_uint uDataCnt = min(uDataAccum, 10 + (rand() % 30));
		uDataAccum -= uDataCnt;
		tPack.tEvent.uDataNum = uDataCnt;
		tPack.tEvent.uEventNum = _tEvent.uEventNum;

		tPack.vDest = m_vDestination[_tEvent.uEventNum];
		tPack.vRot = _vec3(float(rand() % 628) * 0.01f, float(rand() % 628)* 0.01f, float(rand() % 628)* 0.01f);
		tPack.vPos = _vec3(700.f + float(rand() % 100) * 2.f, 400.f + float(rand() % 100), 0.f);
		tPack.vScale = _vec3(0.2f, 0.2f, 1.f);		// 거리에따라 감소
		tPack.fLerpSpeed = 3.f + float(rand() % 50)*0.1f;
		m_listBuffPack.emplace_back(tPack);
		if (uDataAccum == 0 || 9999 < uDataAccum)
		{
			break;
		}
	}
}

void CIngame_Info::Push_EventFont(ENGINE_EVENT _tEvent)
{
	FONTPACK tPack;

	switch (_tEvent.uEventNum)	// 폰트팩 생성
	{
	case 0:
		tPack.tColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
		break;
	case 1:
		tPack.tColor = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f);
		break;
	case 2:
		tPack.tColor = D3DXCOLOR(0.5f, 0.5f, 0.f, 1.f);
		break;
	case 3:
		tPack.tColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
		break;
	case 4:
		tPack.tColor = D3DXCOLOR(0.5f + float(rand() % 100)*0.005f, 0.5f + float(rand() % 100)*0.005f, 0.5f + float(rand() % 100)*0.005f, 1.f);
		break;
	}
	
	tPack.fLifeTime = 1.f;
	tPack.tEvent = _tEvent;
	tPack.vPos = m_vDestination[_tEvent.uEventNum] + _vec3((float)(rand() % 100), (float)(rand() % 100), 0.f);
	m_listFontPack.emplace_back(tPack);
}

void CIngame_Info::Occur_EngineEvent(ENGINE_EVENT _tEvent)
{
	switch (_tEvent.uEventNum)		// 밑에 버프 4개 적용하기
	{
	case 0:
		
		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		m_tPlayerGoods.uPolygons += _tEvent.uDataNum;
		break;
	}
	Push_EventFont(_tEvent);
	m_tPlayerGoods.uGame_Point += (50 + rand()%50);
}

void CIngame_Info::Update_BuffPack(const Engine::_float & _fTimeDelta)
{
	for (auto& iter = m_listBuffPack.begin(); iter != m_listBuffPack.end();)
	{
		D3DXVec3Lerp(&(iter->vPos), &(iter->vPos), &(iter->vDest), iter->fLerpSpeed*_fTimeDelta);
		_vec3 vDist = iter->vDest - iter->vPos;
		if (64.f > D3DXVec3Dot(&vDist, &vDist))
		{
			Occur_EngineEvent(iter->tEvent);
			iter = m_listBuffPack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CIngame_Info::Update_FontPack(const Engine::_float & _fTimeDelta)
{
	for (auto& iter = m_listFontPack.begin(); iter != m_listFontPack.end();)
	{
		iter->vPos += 10.f * _fTimeDelta * _vec3(0.f,1.f,0.f);
		iter->fLifeTime -= _fTimeDelta;
		if (0.f > iter->fLifeTime)
		{
			iter = m_listFontPack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
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

void CIngame_Info::Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fRotX, float _fRotY, float _fRotZ, float _fPosX, float _fPosY, DWORD _dwColor)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	RECT tRect = { 0,0,_iRectX,_iRectY };
	D3DXMatrixScaling(&matScale, _fScaleX, _fScaleY, 0.f);
	D3DXMatrixRotationYawPitchRoll(&matRot, _fRotY, _fRotX, _fRotZ);
	D3DXMatrixTranslation(&matTrans, _fPosX, _fPosY, 0.f);
	matWorld = matScale * matRot * matTrans;
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
