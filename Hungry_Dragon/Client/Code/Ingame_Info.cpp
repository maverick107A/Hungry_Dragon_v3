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

	

}

void CIngame_Info::Update_Info(const Engine::_float & _fTimeDelta)
{
	if (m_tPlayerStatus.fHp < m_tPlayerStatus.fDelay_Hp)
	{
		m_tPlayerStatus.fDelay_Hp -= 20.f*_fTimeDelta;
	}

	if (100.f <= m_tPlayerStatus.fStage)
	{
		m_bStageClear = true;
	}

	if (m_tPlayerStatus.fMp < m_tPlayerStatus.fDelay_Mp)
	{
		m_tPlayerStatus.fDelay_Mp -= 20.f*_fTimeDelta;
	}
	
	if (m_bChargeReadySp)
	{
		if (m_tPlayerStatus.fSp < m_tPlayerStatus.fDelay_Sp)
		{
			m_tPlayerStatus.fDelay_Sp -= 20.f*_fTimeDelta;
		}
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

}

void CIngame_Info::Render_UI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	TCHAR str[32];
	
	// 나침반
	_vec3 vLook;
	CIngame_Flow::GetInstance()->Get_PlayerTransform()->Get_Info(INFO_LOOK, &vLook);
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

	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (1600.f - fAngle)*0.5f, 0.f);
	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (5696.f - fAngle)*0.5f, 0.f);
	Draw_TexPart(m_pCompass->Get_Texture(0), 0, 0, 4096, 128, 0.5f, 0.5f, (-2496.f - fAngle)*0.5f, 0.f);

	Draw_Tex(m_pIndicator, 128, 128, 0.1f, 0.1f, 793.6f, 0.f);

	wsprintf(str, L"각도 : %d", (int)fAngle);
	Engine::Render_Font(L"Font_Light", str, &_vec2(800.f, 100.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	// 좌상측 UI
	float _fRectY = 0.2f;

	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 40.f, 50.f);
	Draw_Tex(m_pBarCon->Get_Texture(0), 1024 * m_tPlayerStatus.fHp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 40.f, 50.f);
	Draw_Tex(m_pBarCon->Get_Texture(0), 1024* m_tPlayerStatus.fDelay_Hp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 40.f, 50.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pIconCon->Get_Texture(0), 512, 512, 0.05f, 0.05f, 60.f, 50.f);

	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 40.f, 80.f);
	Draw_Tex(m_pBarCon->Get_Texture(1), 1024 * m_tPlayerStatus.fMp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 40.f, 80.f);
	Draw_Tex(m_pBarCon->Get_Texture(1), 1024* m_tPlayerStatus.fDelay_Mp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 40.f, 80.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pIconCon->Get_Texture(1), 512, 512, 0.05f, 0.05f, 60.f, 80.f);

	
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 40.f, 110.f);
	Draw_Tex(m_pBarCon->Get_Texture(2), 1024 * m_tPlayerStatus.fSp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 40.f, 110.f);
	Draw_Tex(m_pBarCon->Get_Texture(2), 1024* m_tPlayerStatus.fDelay_Sp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 40.f, 110.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pIconCon->Get_Texture(2), 512, 512, 0.05f, 0.05f, 60.f, 110.f);

	

	Draw_Tex(m_pTexBar, 1024, 128, 1.f, _fRectY, 300.f, 850.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex(m_pBarCon->Get_Texture(4), 1024* m_tPlayerStatus.fStage * 0.01f, 128, 1.f, _fRectY, 300.f, 850.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	Draw_Tex(m_pIconCon->Get_Texture(3), 512, 512, 0.05f, 0.05f, 50.f, 140.f);
	
	
	wsprintf(str, L"%d", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 140.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(4), 512, 512, 0.05f, 0.05f, 50.f, 170.f);
	wsprintf(str, L"포인트 자리", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 170.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Draw_Tex(m_pIconCon->Get_Texture(5), 512, 512, 0.05f, 0.05f, 50.f, 200.f);
	wsprintf(str, L"시간 자리", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_Light", str, &_vec2(80.f, 200.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));


	m_pSprite->End();

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
