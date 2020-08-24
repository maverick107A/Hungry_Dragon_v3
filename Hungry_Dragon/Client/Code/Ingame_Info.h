#ifndef Ingame_Info_h__
#define Ingame_Info_h__

#include "Define.h"
#include "Engine_Define.h"
#include "Transform.h"
#include "Texture.h"

class CBarCon;
class CIconCon;
class CCompassCon;

USING(Engine)

class CIngame_Info
{
	DECLARE_SINGLETON(CIngame_Info)
public:
	enum STAGEID { STAGE_FOREST , STAGE_CAVE_ONE, STAGE_CAVE_TWO, STAGE_CAVE_FINAL, STAGE_SKY , STAGE_LAVA , STAGE_END };

private:
	explicit CIngame_Info(void);
	explicit CIngame_Info(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIngame_Info(void);

public:			
	void Init_Info(LPDIRECT3DDEVICE9 pGraphicDev);
	void Update_Info(const Engine::_float& _fTimeDelta);
	void Render_UI();

	void Update_Frame();
	void Render_Frame();

public:
	void Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, float _fCenterX, float _fCenterY, float _fScaleX, float _fCenterZ, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_Tex(IDirect3DBaseTexture9* _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_TexPart(IDirect3DBaseTexture9* _pTex, int _iPivotX, int _iPivotY, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));


public:
	Engine::STATUS * Get_PlayerInfo() { return &m_tPlayerStatus; }
	Engine::GOODS * Get_PlayerGoods() { return &m_tPlayerGoods; }

private:
	// 출력할 글디바.
	LPDIRECT3DDEVICE9	m_pGraphicDev;
private:
	Engine::STATUS 		m_tPlayerStatus;
	Engine::GOODS 		m_tPlayerGoods;
	Engine::_bool		m_bStageClear = false;
	Engine::_bool		m_bChargeReadySp = true;

	IDirect3DTexture9*	m_pTexBar = nullptr;
	IDirect3DTexture9*	m_pIndicator = nullptr;
	IDirect3DTexture9*	m_pMainFrame = nullptr;
	IDirect3DTexture9*	m_pBtnFrame = nullptr;
	IDirect3DTexture9*	m_pBtnFrameFocus = nullptr;
	IDirect3DTexture9*	m_pBubble = nullptr;

	IDirect3DTexture9*	m_pBuffFrame[4];

	CBarCon*			m_pBarCon = nullptr;
	CIconCon*			m_pIconCon = nullptr;
	CCompassCon*		m_pCompass = nullptr;
	LPD3DXSPRITE		m_pSprite = nullptr;

	_uint				m_uFocusDepth = 0;
	_uint				m_uMainFocus = 0;
	_uint				m_uSubFocus = 0;

};


#endif // GameMgr_h__
