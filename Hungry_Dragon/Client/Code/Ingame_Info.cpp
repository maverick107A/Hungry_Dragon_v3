#include "stdafx.h"
#include "Ingame_Info.h"
#include "Export_Function.h"
#include "BarCon.h"
#include "IconCon.h"
#include "Ingame_Flow.h"

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
	Safe_Release(m_pTexBar);
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
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/HUD/blankbar.png", &m_pTexBar);

	

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

	float _fRectY = 0.3f;

	Draw_Tex((LPDIRECT3DTEXTURE9)m_pIconCon->Get_Texture(0), 512, 512, 0.1f, 0.1f, 60.f, 50.f);
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 100.f, 50.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(0), 1024 * m_tPlayerStatus.fHp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 100.f, 50.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(0), 1024* m_tPlayerStatus.fDelay_Hp / m_tPlayerStatus.fMax_Hp, 128, 0.5f, _fRectY, 100.f, 50.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	Draw_Tex((LPDIRECT3DTEXTURE9)m_pIconCon->Get_Texture(1), 512, 512, 0.1f, 0.1f, 60.f, 110.f);
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 100.f, 110.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(1), 1024 * m_tPlayerStatus.fMp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 100.f, 110.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(1), 1024* m_tPlayerStatus.fDelay_Mp / m_tPlayerStatus.fMax_Mp, 128, 0.5f, _fRectY, 100.f, 110.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	Draw_Tex((LPDIRECT3DTEXTURE9)m_pIconCon->Get_Texture(2), 512, 512, 0.1f, 0.1f, 60.f, 170.f);
	Draw_Tex(m_pTexBar, 1024, 128, 0.5f, _fRectY, 100.f, 170.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(2), 1024 * m_tPlayerStatus.fSp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 100.f, 170.f);
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(2), 1024* m_tPlayerStatus.fDelay_Sp / m_tPlayerStatus.fMax_Sp, 128, 0.5f, _fRectY, 100.f, 170.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	Draw_Tex((LPDIRECT3DTEXTURE9)m_pIconCon->Get_Texture(3), 512, 512, 0.1f, 0.1f, 60.f, 230.f);

	Draw_Tex(m_pTexBar, 1024, 128, 1.f, _fRectY, 300.f, 680.f, D3DCOLOR_ARGB(155, 255, 255, 255));
	Draw_Tex((LPDIRECT3DTEXTURE9)m_pBarCon->Get_Texture(4), 1024* m_tPlayerStatus.fStage * 0.01f, 128, 1.f, _fRectY, 300.f, 680.f, D3DCOLOR_ARGB(155, 255, 255, 255));

	TCHAR str[32];
	wsprintf(str, L"%d", m_tPlayerGoods.uDelay_Polygons);
	Engine::Render_Font(L"Font_BoldBig", str, &_vec2(130.f, 230.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));


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
