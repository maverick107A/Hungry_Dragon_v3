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
		Safe_Release(m_pBuffBar[i]);
	}
	Safe_Release(m_pBubble);
	Safe_Release(m_pPolygon);
	Safe_Release(m_pExpFrame);
	Safe_Release(m_pExpFrameCharge);
	Safe_Release(m_pPortraitFrame);
	for (int i = 0; i < 11; ++i)
	{
		Safe_Release(m_pPortrait[i]);
	}
	m_listBuffPack.clear();
	m_listFontPack.clear();
	m_listPreyInfo.clear();
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
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/ExpFrame.png", &m_pExpFrame);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/ExpFrameCharge.png", &m_pExpFrameCharge);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/portrait/portrait_frame.png", &m_pPortraitFrame);

	TCHAR str[64] = L"";

	for (int i = 0; i < 11; ++i)
	{
		wsprintf(str, L"../../Asset/HUD/portrait/portrait%.2d.png", i);
		D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_pPortrait[i]);
	}
	
	
	for (int i = 0; i < 4; ++i)
	{
		wsprintf(str,L"../../Asset/HUD/BuffIcon%.2d.png", i);
		D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_pBuffFrame[i]);
		wsprintf(str, L"../../Asset/HUD/BuffIconBar%.2d.png", i);
		D3DXCreateTextureFromFile(m_pGraphicDev, str, &m_pBuffBar[i]);
	}
	
	m_vDestination[4] = _vec3(60.f, 170.f, 0.f);
	m_vDestination[0] = _vec3(1060.f, 120.f, 0.f);
	m_vDestination[1] = _vec3(1210.f, 120.f, 0.f);
	m_vDestination[2] = _vec3(1360.f, 120.f, 0.f);
	m_vDestination[3] = _vec3(1510.f, 120.f, 0.f);

	for (int i = 0; i < 4; ++i)
	{
		m_fBuffGage[i] = 0.f;
	}
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
	Update_PreyPack(_fTimeDelta);

	for (int i = 0; i < 4; ++i)
	{
		m_fBuffGage[i] -= _fTimeDelta;
		if (m_fBuffGage[i] < 0.f)
		{
			m_fBuffGage[i] = 0.f;
		}
	}

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

	m_fAcquireAction -= _fTimeDelta;
	if (0.f > m_fAcquireAction)
	{
		m_fAcquireAction = 0.f;
	}
}

void CIngame_Info::Render_UI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	TCHAR str[32];
	_matrix matScale;
	_matrix matIdentity;
	D3DXMatrixIdentity(&matIdentity);

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
	

	Draw_Tex(m_pExpFrame, 2048, 64, 0.78125f, 0.3f, 0.f, 880.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pExpFrameCharge, int(2048 * m_tPlayerStatus.fStage * 0.01f), 64, 0.78125f, 0.3f, 0.f, 880.f, D3DCOLOR_ARGB(155, int(255* m_tPlayerStatus.fStage * 0.01f), 255, int(255*(1.f - m_tPlayerStatus.fStage * 0.01f))));
	wsprintf(str, L"진행도 (%d%%)", (int)m_tPlayerStatus.fStage);

	m_pSprite->SetTransform(&matIdentity);
	Engine::Draw_Font_Center(m_pSprite, L"Font_LightSmall", str, &_vec2(1600.f, 850.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(3), 512, 512, 0.05f * (1.f + m_fAcquireAction), 0.05f * (1.f + m_fAcquireAction), 50.f-12.f*m_fAcquireAction, 180.f - 12.f*m_fAcquireAction);
	wsprintf(str, L"%d", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 180.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(4), 512, 512, 0.05f, 0.05f, 200.f, 150.f);
	wsprintf(str, L"%d", m_tPlayerGoods.uGame_Point);
	Engine::Render_Font(L"Font_Light", str, &_vec2(230.f, 150.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(5), 512, 512, 0.05f, 0.05f, 400.f, 150.f);
	wsprintf(str, L"%.2d : %.2d : %.2d", int(m_fTimeTick) / 60, int(m_fTimeTick) % 60, int(m_fTimeTick*100.f)%100);
	Engine::Render_Font(L"Font_Light", str, &_vec2(430.f, 150.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	for (int i = 0; i < 4; ++i)
	{
		if (0 < m_fBuffGage[i])
		{
			Draw_Tex(m_pBuffFrame[i], 256, 256, 0.5f, 0.5f, 1000.f + 150.f*i, 50.f, D3DCOLOR_ARGB(155, 255, 255, 255));
			Draw_Tex(m_pBuffBar[i], int(2.56f*m_fBuffGage[i]), 256, 0.5f, 0.5f, 1000.f + 150.f*i, 50.f, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			Draw_Tex(m_pBuffFrame[i], 256, 256, 0.5f, 0.5f, 1000.f + 150.f*i, 50.f, D3DCOLOR_ARGB(55, 255, 255, 255));
		}
		
	}


	for (auto& tPack : m_listBuffPack)
	{
		Draw_Tex(m_pPolygon, 128, 128, tPack.vScale.x, tPack.vScale.y, 0.f, 0.f, tPack.vRot.z, tPack.vPos.x, tPack.vPos.y, tPack.dwColor);
		//Draw_Tex(m_pPolygon, 128, 128, tPack.vScale.x, tPack.vScale.y, tPack.vPos.x, tPack.vPos.y, tPack.dwColor);
	}

	_uint uSize = m_listPreyInfo.size();
	_uint uIdx = 0;
	for (auto& tInfo : m_listPreyInfo)
	{
		if (tInfo.uType == 11)
		{
			tInfo.uType = 10;
		}
		if (10 < tInfo.uType)
		{
			tInfo.fLifeTime = 0.f;
		}
		Draw_Tex(m_pPortraitFrame, 1024, 512, 0.2f, 0.2f, 1350.f, 800.f - 130.f*float(uSize - uIdx), D3DCOLOR_ARGB(int(tInfo.fLifeTime * 127.f), 255, 255, 255));
		Draw_Tex(m_pPortrait[tInfo.uType], 512, 512, 0.1f, 0.1f, 1376.f, 826.f - 130.f*float(uSize - uIdx), D3DCOLOR_ARGB(int(tInfo.fLifeTime * 127.f), 255, 255, 255));
		switch (tInfo.uType)
		{
		case 0:
			wsprintf(str, L"토끼 소화 완료");
			break;
		case 1:
			wsprintf(str, L"돼지 소화 완료");

			break;
		case 2:
			wsprintf(str, L"박쥐 소화 완료");
			break;
		case 3:
			wsprintf(str, L"?? 소화 완료");

			break;
		case 4:
			wsprintf(str, L"광석 소화 완료");

			break;
		case 5:
			wsprintf(str, L"박쥐 소화 완료");
			break;
		case 6:
			wsprintf(str, L"광석 소화 완료");
			break;
		case 7:
			wsprintf(str, L"광석 소화 완료");
			break;
		case 8:
			wsprintf(str, L"?? 소화 완료");
			break;
		case 9:
			wsprintf(str, L"보스 격파");
			break;
		case 10:
			wsprintf(str, L"박쥐 소화 완료");
			break;
		}
		
		D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 1.f);
		m_pSprite->SetTransform(&matScale);
		Draw_Font_Center(m_pSprite, L"Font_Light", str, &_vec2(1478.f * 4.f, (818.f - 130.f*float(uSize - uIdx))*2.f), D3DXCOLOR(0.6f, 0.8f, 0.f, tInfo.fLifeTime*0.5f));
		wsprintf(str, L"+%d 폴리곤", tInfo.uPoly);
		Draw_Font_Center(m_pSprite, L"Font_LightSmall", str, &_vec2(1478.f * 4.f, (838.f - 130.f*float(uSize - uIdx))*2.f), D3DXCOLOR(0.6f, 0.8f, 0.f, tInfo.fLifeTime*0.5f));
		wsprintf(str, L"+%d 점수", tInfo.uPoint);
		Draw_Font_Center(m_pSprite, L"Font_LightSmall", str, &_vec2(1478.f * 4.f, (848.f - 130.f*float(uSize - uIdx))*2.f), D3DXCOLOR(0.6f, 0.8f, 0.f, tInfo.fLifeTime*0.5f));
		wsprintf(str, L"+%d 진행도", tInfo.uStage);
		Draw_Font_Center(m_pSprite, L"Font_LightSmall", str, &_vec2(1478.f * 4.f, (858.f - 130.f*float(uSize - uIdx))*2.f), D3DXCOLOR(0.6f, 0.8f, 0.f, tInfo.fLifeTime*0.5f));

		D3DXCOLOR tColor;
		switch (tInfo.uBuff)
		{
		case 0:
			wsprintf(str, L"체력 버프 획득");
			tColor = D3DXCOLOR(0.2f, 0.8f, 0.2f, tInfo.fLifeTime*0.5f);
			break;
		case 1:
			wsprintf(str, L"마력 버프 획득");
			tColor = D3DXCOLOR(0.2f, 0.2f, 0.8f, tInfo.fLifeTime*0.5f);
			break;
		case 2:
			wsprintf(str, L"기력 버프 획득");
			tColor = D3DXCOLOR(0.8f, 0.8f, 0.2f, tInfo.fLifeTime*0.5f);
			break;
		case 3:
			wsprintf(str, L"화력 버프 획득");
			tColor = D3DXCOLOR(0.8f, 0.2f, 0.2f, tInfo.fLifeTime*0.5f);
			break;
		case 4:

			break;
		}
		if (tInfo.uBuff != 4)
		{
			Draw_Font_Center(m_pSprite, L"Font_LightSmall", str, &_vec2(1478.f * 4.f, (868.f - 130.f*float(uSize - uIdx))*2.f), tColor);

		}
		
		//Draw_Tex(m_pPolygon, 128, 128, tPack.vScale.x, tPack.vScale.y, tPack.vPos.x, tPack.vPos.y, tPack.dwColor);
		++uIdx;
	}



	

	m_pSprite->End();

	for (auto& tPack : m_listFontPack)
	{
		wsprintf(str, L"+%d", (int)(tPack.tEvent.uDataNum));
		Engine::Render_Font(L"Font_Light", str, &_vec2(tPack.vPos.x-50.f, tPack.vPos.y - 50.f), tPack.tColor);
		//Engine::Render_Font(L"Font_Light", str, &_vec2(400.f, 200.f), tPack.tColor);
	}

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
	PREYINFO tInfo;

	tInfo.uPoly = _tEvent.uDataNum;
	tInfo.uBuff = _tEvent.uEventNum;
	tInfo.uType = _tEvent.uTypeNum;

	switch (_tEvent.uEventNum)	// 버프팩 생성
	{
	case 0:
		tPack.dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);
		break;
	case 1:
		tPack.dwColor = D3DCOLOR_ARGB(255, 0, 128, 255);
		break;
	case 2:
		tPack.dwColor = D3DCOLOR_ARGB(255, 192, 192, 0);
		break;
	case 3:
		tPack.dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);
		break;
	case 4:
		tPack.dwColor = D3DCOLOR_ARGB(255, 128 + (rand() % 128), 128 + (rand() % 128), 128 + (rand() % 128));
		break;
	}
	_uint uDataAccum = _tEvent.uDataNum;
	_uint uPointAccum = 0;
	_uint uStageAccum = 0;
	while (uDataAccum != 0)
	{
		_uint uDataCnt = min(uDataAccum, 10 + (rand() % 30));
		uDataAccum -= uDataCnt;
		tPack.tEvent.uDataNum = uDataCnt;
		tPack.tEvent.uEventNum = _tEvent.uEventNum;
		tPack.tEvent.uTypeNum = (50 + rand() % 50);
		uPointAccum += tPack.tEvent.uTypeNum;

		tPack.vDest = m_vDestination[_tEvent.uEventNum];
		tPack.vRot = _vec3(float(rand() % 628) * 0.01f, float(rand() % 628)* 0.01f, float(rand() % 628)* 0.01f);
		tPack.vPos = _vec3(700.f + float(rand() % 100) * 2.f, 400.f + float(rand() % 100), 0.f);
		tPack.vScale = _vec3(0.2f, 0.2f, 1.f);		// 거리에따라 감소
		tPack.fLerpSpeed = 3.f + float(rand() % 50)*0.1f;
		m_listBuffPack.emplace_back(tPack);
		++uStageAccum;
		if (uDataAccum == 0 || 9999 < uDataAccum)
		{
			break;
		}
	}
	tInfo.uPoint = uPointAccum;
	tInfo.uStage = uStageAccum;
	tInfo.fLifeTime = 2.f;

	switch (tInfo.uType)
	{
	case 0:
		Get_FMOD()->PlayEffect(L"rabbit_die");
		break;
	case 1:
		Get_FMOD()->PlayEffect(L"pig_die");

		break;
	case 2:
		switch (rand() % 3)
		{
		case 0:
			Get_FMOD()->PlayEffect(L"bat_die1");
			break;
		case 1:
			Get_FMOD()->PlayEffect(L"bat_die2");
			break;
		case 2:
			Get_FMOD()->PlayEffect(L"bat_die3");
			break;
		}
		break;
	case 3:

		break;
	case 4:
		Get_FMOD()->PlayEffect(L"break");

		break;
	case 5:
		switch (rand() % 3)
		{
		case 0:
			Get_FMOD()->PlayEffect(L"bat_die1");
			break;
		case 1:
			Get_FMOD()->PlayEffect(L"bat_die2");
			break;
		case 2:
			Get_FMOD()->PlayEffect(L"bat_die3");
			break;
		}
		break;
	case 6:
		Get_FMOD()->PlayEffect(L"break");
		break;
	case 7:
		Get_FMOD()->PlayEffect(L"break");
		break;
	case 8:
		//wsprintf(str, L"?? 소화 완료");
		break;
	case 9:
		//wsprintf(str, L"보스 격파");
		break;
	case 10:
		switch (rand() % 3)
		{
		case 0:
			Get_FMOD()->PlayEffect(L"bat_die1");
			break;
		case 1:
			Get_FMOD()->PlayEffect(L"bat_die2");
			break;
		case 2:
			Get_FMOD()->PlayEffect(L"bat_die3");
			break;
		}
		break;
	}

	// ui 푸쉬
	m_listPreyInfo.emplace_back(tInfo);
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
		m_fBuffGage[_tEvent.uEventNum] += _tEvent.uDataNum;
		if (100.f < m_fBuffGage[_tEvent.uEventNum])
		{
			m_fBuffGage[_tEvent.uEventNum] = 100.f;
		}
		break;
	case 1:
		m_fBuffGage[_tEvent.uEventNum] += _tEvent.uDataNum;
		if (100.f < m_fBuffGage[_tEvent.uEventNum])
		{
			m_fBuffGage[_tEvent.uEventNum] = 100.f;
		}
		break;
	case 2:
		m_fBuffGage[_tEvent.uEventNum] += _tEvent.uDataNum;
		if (100.f < m_fBuffGage[_tEvent.uEventNum])
		{
			m_fBuffGage[_tEvent.uEventNum] = 100.f;
		}
		break;
	case 3:
		m_fBuffGage[_tEvent.uEventNum] += _tEvent.uDataNum;
		if (100.f < m_fBuffGage[_tEvent.uEventNum])
		{
			m_fBuffGage[_tEvent.uEventNum] = 100.f;
		}
		break;
	case 4:
		m_tPlayerGoods.uPolygons += _tEvent.uDataNum;
		m_fAcquireAction = 1.f;
		break;
	}
	switch (rand() % 4)
	{
	case 0:
		Get_FMOD()->PlayEffect(L"Fragile0");
		break;
	case 1:
		Get_FMOD()->PlayEffect(L"Fragile1");
		break;
	case 2:
		Get_FMOD()->PlayEffect(L"Fragile2");
		break;
	case 3:
		Get_FMOD()->PlayEffect(L"Fragile3");
		break;
	}
	Push_EventFont(_tEvent);
	m_tPlayerGoods.uGame_Point += _tEvent.uTypeNum;
	m_tPlayerStatus.fStage += 1.f;
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

void CIngame_Info::Update_PreyPack(const Engine::_float & _fTimeDelta)
{
	for (auto& iter = m_listPreyInfo.begin(); iter != m_listPreyInfo.end();)
	{
		iter->fLifeTime -= _fTimeDelta;
		if (0.f > iter->fLifeTime)
		{
			iter = m_listPreyInfo.erase(iter);
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
